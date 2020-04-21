#include "tcpsocket.h"

TCPSocket::TCPSocket()
    :Socket(SOCK_STREAM, IPPROTO_TCP)
{

}

TCPSocket::TCPSocket(const std::string &remote_addr, unsigned short remote_port)
    :Socket(SOCK_STREAM, IPPROTO_TCP)
{
    connect(remote_addr, remote_port);
}

TCPSocket::TCPSocket(int fresh_connection)
    :Socket (fresh_connection)
{

}
