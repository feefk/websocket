// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/message_pump_auranox.h"

#include <fcntl.h>                 // open()
#include "base/basictypes.h"
#include "base/message_loop.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <glib.h>


static bool IsQtInput()
{
    const char* input_system = getenv("INPUT_SYSTEM");
    return (input_system && (std::string("qt") == input_system));
}
GPollFD _x_poll_;//mouse fd ,The poll attached to |x_source_|
int mouseFd;
const char* FIFO_PATH = "/tmp/qt_input_fifo";

//namespace
//{
    gboolean NOXSourcePrepare(GSource* source, gint* timeout_ms)
    {
        *timeout_ms = -1;
        return FALSE;
    }
    gboolean NOXSourceCheck(GSource* source)
    {
        if(IsQtInput())
        {
            if(_x_poll_.revents != _x_poll_.events)
            {
                return FALSE;
            }
        }else
        {

        }
        return TRUE;
    }

    gboolean NOXSourceDispatch(GSource* source, GSourceFunc unused_func,
        gpointer data)
    {
        base::MessagePumpAuraNox* pump =
                static_cast<base::MessagePumpAuraNox*>(data);
        return pump->DispatchNOXEvents();
    }

    GSourceFuncs NOXSourceFuncs = { NOXSourcePrepare, NOXSourceCheck,
                                    NOXSourceDispatch, NULL };

// The default dispatcher to process native events when no dispatcher
// is specified.
    base::MessagePumpDispatcher* g_default_dispatcher = NULL;

//} // namespace

namespace base
{
    MessagePumpAuraNox::MessagePumpAuraNox()
            : MessagePumpGlib(),
              nox_source_(NULL)
    {
        InitNOXSource();
    }

// static
    void MessagePumpAuraNox::SetDefaultDispatcher(
        MessagePumpDispatcher* dispatcher)
    {
        DCHECK(!g_default_dispatcher || !dispatcher);
        g_default_dispatcher = dispatcher;
    }

    bool MessagePumpAuraNox::DispatchNOXEvents()
    {
        MessagePumpDispatcher* dispatcher =
                GetDispatcher() ? GetDispatcher() : g_default_dispatcher;

        NOXButtonEvent noxButtonEvent;
        int readlen = 0;
        readlen = read(mouseFd, &noxButtonEvent, sizeof(NOXButtonEvent));

        if (readlen > 0) {
            /*printf("readlen = %d \n", readlen);
            printf("mouse type -> %d; mouse Press -> %d; mouse -> x = %d , y = %d \n",\
                        noxButtonEvent.type, noxButtonEvent.button, \
                        noxButtonEvent.x, noxButtonEvent.y);*/

            ProcessNOXEvent(dispatcher, (NoxEvents *) (&noxButtonEvent));
        }
        return true;
    }

    MessagePumpAuraNox::~MessagePumpAuraNox()
    {
        g_source_destroy(nox_source_);
        g_source_unref(nox_source_);
        close(mouseFd);
    }

    void MessagePumpAuraNox::InitNOXSource()
    {
        CHECK(!nox_source_);


        if(IsQtInput())
        {
            //GIOChannel *channel_;
            //channel_ = g_io_channel_new_file(FIFO_PATH,"r",NULL);
            _x_poll_.fd = 0;
            mouseFd = _x_poll_.fd;
        }else
        {
            unlink(FIFO_PATH);
            if ((mkfifo(FIFO_PATH, 0777) < 0)) {
                printf("不能创建FIFO\n");
                return ;
            }
            printf("创建FIFO成功 : \n");

            mouseFd = open(FIFO_PATH, (O_RDONLY | O_NONBLOCK));
            printf("打开FIFO 22 成功：\n");

            if (mouseFd == -1) {
                //printf("open DEV failed,maybe u should run it in root(sudo)!!!\n");
                return;
            }
            _x_poll_.fd = mouseFd;
            //printf("打开FIFO 成功：\n");
        }
        _x_poll_.events = G_IO_IN;

        nox_source_ = g_source_new(&NOXSourceFuncs, sizeof(GSource));
        g_source_add_poll(nox_source_, &_x_poll_);
        g_source_set_can_recurse(nox_source_, TRUE);
        g_source_set_callback(nox_source_, NULL, this, NULL);
        g_source_set_priority(nox_source_, G_PRIORITY_DEFAULT_IDLE);
        g_source_attach(nox_source_, g_main_context_default());
    }

    bool MessagePumpAuraNox::ProcessNOXEvent(MessagePumpDispatcher* dispatcher,
        NoxEvents* ev)
    {
        bool should_quit = false;

        if (!WillProcessNOXEvent(ev)) {
            if (!dispatcher->Dispatch(ev)) {
                should_quit = true;
                Quit();
            }
            DidProcessNOXEvent(ev);
        }
        return !should_quit;
    }

    bool MessagePumpAuraNox::WillProcessNOXEvent(NoxEvents* xevent)
    {
        if (!observers().might_have_observers())
            return false;
        ObserverListBase<MessagePumpObserver>::Iterator it(observers());
        MessagePumpObserver* obs;
        while ((obs = it.GetNext()) != NULL) {
            if (obs->WillProcessEvent(xevent))
                return true;
        }
        return false;
    }

    void MessagePumpAuraNox::DidProcessNOXEvent(NoxEvents* xevent)
    {
        FOR_EACH_OBSERVER(MessagePumpObserver, observers(),
                DidProcessEvent(xevent));
    }

} // namespace base
