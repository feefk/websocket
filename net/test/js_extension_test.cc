#include "net/server/js_extension_handler.h"
#include "base/at_exit.h"
#include "base/message_loop.h"
#include "base/memory/ref_counted.h"
#include "base/bind.h"

class TestDelegate: public js::JSExtensionHandler::Delegate
{
    scoped_refptr<js::JSExtensionHandler> handler_;
public:
    TestDelegate():handler_(0)
    {}
    virtual void OnLinkConnected(int link_id)
    {
        VLOG(0)<<"TestDelegate::OnLinkConnected link_id = " << link_id ;
    }
    virtual void OnJsonRequest(int link_id, const std::string& json)
    {
        VLOG(0)<<"TestDelegate::OnJsonRequest link_id = " << link_id
                        <<" json = " << json ;
        handler_->SendJsonResponse(link_id, std::string("JSON Reqest ") + json + " JSON RESPONSE { " + json + " }");
    }
    virtual void OnFileRequest(int link_id, const std::string& path)
    {
        VLOG(0)<<"TestDelegate::OnFileRequest link_id = " << link_id
                <<" path = " << path ;
        if(path.substr(0,6) == "/root/")
        {
            handler_->SendFileErrorCode(link_id, js::JSExtensionHandler::eFileAccessDenied);
            return;
        }
        if(path.substr(0,strlen("/neverplace/")) == "/neverplace/")
        {
            handler_->SendFileErrorCode(link_id, js::JSExtensionHandler::eFileAccessNotExisted);
            return;
        }
        handler_->SendFile(link_id, path + " this is the content of the file(dummy)","text/html");
    }
    virtual void OnLinkClosed(int link_id)
    {
        VLOG(0)<<"TestDelegate::OnLinkClosed link_id = " << link_id;
    }
    virtual void OnStart(js::JSExtensionHandler* handler)
    {
        VLOG(0)<<"TestDelegate::OnStart " << handler;
        handler_ = handler;
    }
    virtual void OnStop(js::JSExtensionHandler* handler)
    {
        VLOG(0)<<"TestDelegate::OnStop " << handler;
        handler_ = NULL;
        delete this;
    }
    virtual ~TestDelegate(){}
};


int main()
{
    base::AtExitManager atExitMngr;
    MessageLoop loop_;
    scoped_refptr<js::JSExtensionHandler>  handler = js::JSExtensionHandler::Start(8088, new TestDelegate());
    //loop_.PostDelayedTask(FROM_HERE, base::Bind(&js::JSExtensionHandler::Stop, handler.get()), base::TimeDelta::FromSeconds(30));
    sleep(30);
    handler->Stop();

    handler = NULL;

    return 0;
};
