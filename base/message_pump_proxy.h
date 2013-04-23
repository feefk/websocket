#if !defined(BUILD_IN_CHROME)
#ifndef BASE_MESSAGE_PUMP_PROXY_H_
#define BASE_MESSAGE_PUMP_PROXY_H_

#include "base/compiler_specific.h"
#include "base/message_pump.h"
#include "base/time.h"

namespace base {
class RunLoop;

// This class implements a MessagePump needed for TYPE_UI MessageLoops on
// Anytype task platform.

class MessagePumpStub
{
public:
    class Client
    {
    public:
        //Return true if more works are left
        virtual bool DoRunLoopOnce() = 0;
    protected:
        virtual ~Client(){}
    };
    virtual void Attach(Client* client) = 0;
    virtual void ScheduleWork() = 0;
    virtual void ScheduleDelayedWork(int64 millis) = 0;
    virtual void Quit() = 0;
protected:
    virtual ~MessagePumpStub(){}
};

class MessagePumpProxy : public MessagePump , public MessagePumpStub::Client{
 public:

  MessagePumpProxy();

  virtual void Run(Delegate* delegate) OVERRIDE;
  virtual void Quit() OVERRIDE;
  virtual void ScheduleWork() OVERRIDE;
  virtual void ScheduleDelayedWork(const TimeTicks& delayed_work_time) OVERRIDE;
  virtual void Attach(Delegate* delegate) OVERRIDE;
  virtual bool RegisterStub(MessagePumpStub* stub) OVERRIDE;
  virtual bool DoRunLoopOnce() OVERRIDE;
 protected:
  virtual ~MessagePumpProxy();

 private:
  base::RunLoop* run_loop_;
  Delegate* delegate_;
  MessagePumpStub* stub_;
  DISALLOW_COPY_AND_ASSIGN(MessagePumpProxy);
};

}  // namespace base

#endif  // BASE_MESSAGE_PUMP_PROXY_H_
#endif //#if !defined(BUILD_IN_CHROME)
