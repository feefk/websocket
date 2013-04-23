/** 
 * Copyright @ 2013 Pioneer Suntec Electronic Technology Co.,LTD (PSET) 
 * All Rights Reserved.
 *
 * filename :     ExtertionHandler.h
 * create date :  Apr 16, 2013
 * description :
 *
 */

#ifndef JS_EXTERTION_HANDLER_H_
#define JS_EXTERTION_HANDLER_H_
#include <string>
namespace js
{
    //JSExtension Handler is create in UI thread and work in IOThread
    class JSExtensionHandler
    {
    public:
        enum eFileAccessError
        {
            eFileAccessSuccess = 200,
            eFileAccessDenied = 500,
            eFileAccessNotExisted = 404,
        };

        //This delegate must maintain itself's life circle, live in ui thread
        class Delegate
        {
        public:
            virtual void OnLinkConnected(int link_id) = 0;
            virtual void OnJsonRequest(int link_id, const std::string& json) = 0;
            virtual void OnFileRequest(int link_id, const std::string& path) = 0;
            virtual void OnLinkClosed(int link_id) = 0;
            virtual void OnStart(JSExtensionHandler* handler) = 0;
            virtual void OnStop(JSExtensionHandler* handler) = 0;
        protected:
            virtual ~Delegate() { }
        };


        static JSExtensionHandler* Start(int port, Delegate* delegate) ;
        virtual void Stop() = 0;
        virtual ~JSExtensionHandler();
        virtual void SendJsonResponse(int link_id, const std::string& data) = 0;
        virtual void SendFile(int link_id,
                     const std::string& data,
                     const std::string& mime_type) = 0;
        virtual void SendFileErrorCode(int link_id, eFileAccessError err) = 0;

        virtual void AddRef() const = 0;
        virtual void Release() const = 0;
    };

} /* namespace js */
#endif /* JS_EXTERTION_HANDLER_H_ */
