#include "net/server/http_server.h"
#include "net/server/http_server_request_info.h"

#include "js_extension_handler.h"
#include "base/at_exit.h"
#include "base/threading/thread.h"
#include "net/base/tcp_listen_socket.h"
class JSExtensionHandlerImpl: private  net::HttpServer::Delegate, public js::JSExtensionHandler, public base::RefCountedThreadSafe<JSExtensionHandlerImpl>
{

private:
    int port_;
    js::JSExtensionHandler::Delegate* delegate_;
    scoped_refptr<net::HttpServer> server_;
    base::Thread* io_thread_;
    base::Thread* delegate_thread_;
    scoped_ptr<net::TCPListenSocketFactory> tcp_listen_socket_factory_;
    bool is_running_;
    friend struct base::RefCountedThreadSafe<JSExtensionHandlerImpl>;
    virtual ~JSExtensionHandlerImpl() {
        VLOG(0)<<"~JSExtensionHandlerImpl";
    }
public:

    JSExtensionHandlerImpl(int port, js::JSExtensionHandler::Delegate* delegate):
        port_(port),
        delegate_(delegate),
        server_(NULL),
        io_thread_(new base::Thread("io_thread_")),
        delegate_thread_(new base::Thread("delegate_thread_")),
        tcp_listen_socket_factory_(0),
        is_running_(false)
    {
    }

    void Start()
    {
        if(!is_running_)
        {
            base::Thread::Options opt;
            opt.message_loop_type = MessageLoop::TYPE_IO;
            io_thread_->StartWithOptions(opt);
            opt.message_loop_type = MessageLoop::TYPE_DEFAULT;
            delegate_thread_->StartWithOptions(opt);
            is_running_ = true;
            AddRef();
            io_thread_->message_loop_proxy()->PostTask(FROM_HERE, base::Bind(&JSExtensionHandlerImpl::StartOnIO, this));
        }
    }


    virtual void AddRef() const {
        base::RefCountedThreadSafe<JSExtensionHandlerImpl>::AddRef();
    }
    virtual void Release() const {
        base::RefCountedThreadSafe<JSExtensionHandlerImpl>::Release();
    }

private:

    void StartOnDelegate()
    {
        delegate_->OnStart(this);
    }

    void StartOnIO(){
        VLOG(0) << port_ ;
        tcp_listen_socket_factory_.reset(new net::TCPListenSocketFactory("127.0.0.1", port_));
        server_ = new net::HttpServer(*tcp_listen_socket_factory_.get(), this);
        delegate_thread_->message_loop_proxy()->PostTask(FROM_HERE,
                base::Bind(&JSExtensionHandlerImpl::StartOnDelegate, this));
    }



    void StopOnIO()
    {
        server_ = NULL;
    }

    void StopOnDelegate()
    {
        delegate_->OnStop(this);
    }

    virtual void Stop()
    {
        if(is_running_)
        {
            is_running_ = false;
            io_thread_->message_loop_proxy()->PostTask(FROM_HERE, base::Bind(&JSExtensionHandlerImpl::StopOnIO, this));
            delegate_thread_->message_loop_proxy()->PostTask(FROM_HERE, base::Bind(&JSExtensionHandlerImpl::StopOnDelegate, this));
            delegate_thread_->Stop();
            io_thread_->Stop();
            delete io_thread_;
            io_thread_ = NULL;
            delete delegate_thread_;
            delegate_thread_ = NULL;
            delegate_ = NULL;
            Release();
        }
    }


    void SendJsonResponseOnIO(int link_id, const std::string& data)
    {
        server_->SendOverWebSocket(link_id,data);
    }
    virtual void SendJsonResponse(int link_id, const std::string& data)
    {
        if(is_running_)
        {
            io_thread_->message_loop_proxy()->PostTask(FROM_HERE,
                    base::Bind(&JSExtensionHandlerImpl::SendJsonResponseOnIO, this, link_id, data));
        }
    }
    virtual void SendFile(int link_id,
                 const std::string& data,
                 const std::string& mime_type)
    {
        if(is_running_)
        {
            io_thread_->message_loop_proxy()->PostTask(FROM_HERE,
                    base::Bind(&net::HttpServer::Send200, server_.get(), link_id, data,mime_type));
        }
    }
    virtual void SendFileErrorCode(int link_id, eFileAccessError err)
    {
        if(is_running_)
        {
            switch(err)
            {
            case eFileAccessDenied:
                io_thread_->message_loop_proxy()->PostTask(FROM_HERE,
                    base::Bind(&net::HttpServer::Send500, server_.get(), link_id, "Denied"));
                break;
            case eFileAccessNotExisted:
                io_thread_->message_loop_proxy()->PostTask(FROM_HERE,
                    base::Bind(&net::HttpServer::Send404, server_.get(), link_id));
                break;
            default:
                io_thread_->message_loop_proxy()->PostTask(FROM_HERE,
                                    base::Bind(&net::HttpServer::Send200, server_.get(),
                                        link_id, "", "text/html"));
                                break;
            }
        }
    }

    void OnHttpRequestUI(int connection_id,
        const net::HttpServerRequestInfo& info)
    {
        if(is_running_)
        {
            delegate_->OnFileRequest(connection_id,info.path);
        }
    }
    virtual void OnHttpRequest(int connection_id,
        const net::HttpServerRequestInfo& info)
    {
        if(is_running_)
        {
            delegate_thread_->message_loop_proxy()->PostTask(FROM_HERE,
                    base::Bind(&JSExtensionHandlerImpl::OnHttpRequestUI, this, connection_id, info));
        }
    }

    void OnWebSocketRequestUI(int connection_id,
            const net::HttpServerRequestInfo& info)
    {
        if(is_running_)
        {
            delegate_->OnLinkConnected(connection_id);
        }
    }

    virtual void OnWebSocketRequest(int connection_id,
        const net::HttpServerRequestInfo& info)
    {
        server_->AcceptWebSocket(connection_id, info);
        if(is_running_)
        {
            delegate_thread_->message_loop_proxy()->PostTask(FROM_HERE,
                    base::Bind(&JSExtensionHandlerImpl::OnWebSocketRequestUI, this, connection_id, info));
        }
    }

    void OnWebSocketMessageUI(int connection_id,
        const std::string& data)
    {
        if(is_running_)
        {
            delegate_->OnJsonRequest(connection_id, data);
        }
    }

    virtual void OnWebSocketMessage(int connection_id,
        const std::string& data)
    {
        if(is_running_)
        {
            delegate_thread_->message_loop_proxy()->PostTask(FROM_HERE,
                    base::Bind(&JSExtensionHandlerImpl::OnWebSocketMessageUI, this, connection_id, data));
        }
    }

    void OnCloseUI(int connection_id)
    {
        if(is_running_)
        {
            delegate_->OnLinkClosed(connection_id);
        }
    }

    virtual void OnClose(int connection_id)
    {
        if(is_running_)
        {
            delegate_thread_->message_loop_proxy()->PostTask(FROM_HERE,
                    base::Bind(&JSExtensionHandlerImpl::OnCloseUI, this, connection_id));
        }
    }

};

namespace js
{
    JSExtensionHandler* JSExtensionHandler::Start(int port, JSExtensionHandler::Delegate* delegate)
    {
        JSExtensionHandlerImpl* new_handler = new JSExtensionHandlerImpl(port, delegate);
        new_handler->Start();
        return new_handler;
    }
};

