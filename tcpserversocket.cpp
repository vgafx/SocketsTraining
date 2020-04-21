#include "tcpserversocket.h"


void TCPServerSocket::setListen(int length)
{
    if(::listen(m_sock_fdesc, length) < 0){
        throw SocketException("TCPServerSocket:Failed to set socket to listening: listen()", true);
    }
}

TCPServerSocket::TCPServerSocket(unsigned short local_port, int queue_length)
    : Socket(SOCK_STREAM, IPPROTO_TCP)
{
    setLocalPort(local_port);
    this->setListen(queue_length);
}

TCPServerSocket::TCPServerSocket(const std::string &local_add, unsigned short local_port, int queue_length)
    : Socket(SOCK_STREAM, IPPROTO_TCP)
{
    setLocalAddressAndPort(local_add, local_port);
    this->setListen(queue_length);
}

TCPSocket *TCPServerSocket::accept()
{
    int new_connection;
    if((new_connection = ::accept(m_sock_fdesc, nullptr, nullptr)) < 0){
        throw SocketException("TCPServerSocket:Failed to accept connection: accept()", true);
    }

    return new TCPSocket(new_connection);
}
