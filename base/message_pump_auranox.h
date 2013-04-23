// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MESSAGE_PUMP_AURANOX_H
#define BASE_MESSAGE_PUMP_AURANOX_H

#include <stdio.h>
#include "base/message_pump.h"
#include "base/message_pump_glib.h"
#include "base/message_pump_dispatcher.h"
#include "base/message_pump_observer.h"
#include "base/NoxEvent.h"   // keyboard & mouse
#include "base/memory/scoped_ptr.h"

typedef struct _GSource GSource;
typedef struct _GPollFD GPollFD;

namespace base
{
// This class implements a message-pump for dispatching mouse & keyboard events.
    class BASE_EXPORT MessagePumpAuraNox: public MessagePumpGlib
    {
    public:
        MessagePumpAuraNox();
        // Internal function. Called by the glib source dispatch function. Processes
        // all available NOX events.
        bool DispatchNOXEvents();

        // Sets the default dispatcher to process native events.
        static void SetDefaultDispatcher(MessagePumpDispatcher* dispatcher);

    protected:
        virtual ~MessagePumpAuraNox();

    private:
        typedef int (*filterHandler)(struct input_event *, int);
        int filterFunc(filterHandler filter, struct input_event * pevent,
            int type)
        {
            return filter(pevent, type);
        }

        //Initializes the glib event source for NOX.
        void InitNOXSource();

        // Dispatches the NOXEvent and returns true if we should exit the current loop
        // of message processing.
        bool ProcessNOXEvent(MessagePumpDispatcher* dispatcher, NoxEvents* ev);

        // Sends the event to the observers. If an observer returns true, then it does
        // not send the event to any other observers and returns true. Returns false
        // if no observer returns true.
        bool WillProcessNOXEvent(NoxEvents* event);
        void DidProcessNOXEvent(NoxEvents* event);

        // The event source for NOX events.
        GSource* nox_source_;

        // The poll attached to |x_source_|.
        //scoped_ptr<GPollFD> x_poll_; // for mouse
        DISALLOW_COPY_AND_ASSIGN(MessagePumpAuraNox);
    };

    typedef MessagePumpAuraNox MessagePumpForUI;

} // namespace base

#endif  // BASE_MESSAGE_PUMP_AURAX11_H
