#include "build/build_config.h"

#if defined(OS_WIN)
#include <windows.h>
#include <winsock2.h>
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")
#elif defined(OS_POSIX)
#include <fcntl.h>
#if !defined(OS_ANDROID)
#include <ifaddrs.h>
#endif
#include <netdb.h>
#include <net/if.h>
#include <netinet/in.h>
#endif
namespace net
{
    int SetNonBlocking(int fd) {
    #if defined(OS_WIN)
      unsigned long no_block = 1;
      return ioctlsocket(fd, FIONBIO, &no_block);
    #elif defined(OS_POSIX)
      int flags = fcntl(fd, F_GETFL, 0);
      if (-1 == flags)
        return flags;
      return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    #endif
    }
};
