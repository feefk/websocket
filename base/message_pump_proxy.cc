// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if !defined(BUILD_IN_CHROME)
#include "base/message_pump_proxy.h"
#include "base/lazy_instance.h"
#include "base/logging.h"
#include "base/run_loop.h"

namespace base {

MessagePumpProxy::MessagePumpProxy()
    : run_loop_(NULL) {
}

MessagePumpProxy::~MessagePumpProxy() {
}

void MessagePumpProxy::Run(Delegate* delegate) {
  NOTREACHED() << "UnitTests should rely on MessagePumpProxyStub in"
      " test_stub_android.h";
}

bool MessagePumpProxy::DoRunLoopOnce() {
  base::MessagePump::Delegate* delegate =
          this->delegate_;
  DCHECK(delegate);
  // This is based on MessagePumpProxy::DoRunLoop() from desktop.
  // Note however that our system queue is handled in the java side.
  // In desktop we inspect and process a single system message and then
  // we call DoWork() / DoDelayedWork().
  // On Android, the java message queue may contain messages for other handlers
  // that will be processed before calling here again.
  bool more_work_is_plausible = delegate->DoWork();

  // This is the time when we need to do delayed work.
  base::TimeTicks delayed_work_time;
  more_work_is_plausible |= delegate->DoDelayedWork(&delayed_work_time);

  // This is a major difference between android and other platforms: since we
  // can't inspect it and process just one single message, instead we'll yeld
  // the callstack, and post a message to call us back soon.
  if (more_work_is_plausible)
    return true;

  more_work_is_plausible = delegate->DoIdleWork();
  if (!more_work_is_plausible && !delayed_work_time.is_null()) {
    // We only set the timer here as returning true would post a message.
    int64 millis =
        (delayed_work_time - base::TimeTicks::Now()).InMillisecondsRoundedUp();
//    Java_SystemMessageHandler_setDelayedTimer(env, obj, millis);
    stub_->ScheduleDelayedWork(millis);
  }
  return more_work_is_plausible;
}

void MessagePumpProxy::Attach(Delegate* delegate) {
  run_loop_ = new base::RunLoop();
  // Since the RunLoop was just created above, BeforeRun should be guaranteed to
  // return true (it only returns false if the RunLoop has been Quit already).
  if (!run_loop_->BeforeRun())
    NOTREACHED();
  delegate_ = delegate;

}

void MessagePumpProxy::Quit() {
  if (run_loop_) {
    run_loop_->AfterRun();
    delete run_loop_;
    run_loop_ = NULL;
  }
  stub_->Quit();
}

void MessagePumpProxy::ScheduleWork() {
    if(!stub_)
    {
        return;
    }

    stub_->ScheduleWork();
}

void MessagePumpProxy::ScheduleDelayedWork(const TimeTicks& delayed_work_time) {

  if(!stub_)
  {
      return;
  }
  int64 millis =
      (delayed_work_time - base::TimeTicks::Now()).InMillisecondsRoundedUp();
  // Note that we're truncating to milliseconds as required by the java side,
  // even though delayed_work_time is microseconds resolution.
  stub_->ScheduleDelayedWork(millis);
}

// static
bool MessagePumpProxy::RegisterStub(MessagePumpStub* stub) {
  stub_ = stub;
  stub_->Attach(this);
  return true;
}

}  // namespace base
#endif //#if !defined(BUILD_IN_CHROME)