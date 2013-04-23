
#include "base/at_exit.h"
#include "base/message_loop.h"
#include "base/memory/ref_counted.h"

#include "net/server/http_server.h"
#include "net/base/tcp_listen_socket.h"

#include <stdio.h>


using namespace net;

int main(){

	base::AtExitManager atExit;
	MessageLoop message_loop_;

	TCPListenSocketFactory *tcp_factory = new TCPListenSocketFactory("127.0.0.1", 8888);
	//tcp_factory->CreateAndListen()



	printf("test\n");

	message_loop_.Run();
	usleep(500);

	return 0;
}
