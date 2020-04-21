#include "socket.h"

/*Ctors & Dtors*/
Socket::Socket(int socket_fdesc)
{
    m_sock_fdesc = socket_fdesc;
    m_addr_size = sizeof(m_local_addr);
}

Socket::Socket(int s_type, int t_protocol)
{
    m_sock_fdesc = socket(PF_INET, s_type, t_protocol);
    m_addr_size = sizeof(m_local_addr);
    if (m_sock_fdesc < 0){
        throw SocketException("Failed to create a Socket : Constructor called socket()", true);
    }
}

Socket::~Socket()
{
    ::close(m_sock_fdesc);
}

/*Getters & Setters*/
std::string Socket::getLocalAddress()
{
    unsigned int addr_len = sizeof(m_local_addr);

    if (getsockname(m_sock_fdesc, reinterpret_cast<sockaddr*>(&m_local_addr), reinterpret_cast<socklen_t*>(&addr_len)) < 0) {
        throw SocketException("Failed to get local address : getsockname()", true);
    }

    return inet_ntoa(m_local_addr.sin_addr);
}

unsigned short Socket::getLocalPort()
{
    unsigned int addr_len = sizeof(m_local_addr);

    if (getsockname(m_sock_fdesc, reinterpret_cast<sockaddr*>(&m_local_addr), reinterpret_cast<socklen_t*>(&addr_len)) < 0) {
        throw SocketException("Failed to get local port : getsockname()", true);
    }

    return ntohs(m_local_addr.sin_port);
}

void Socket::setLocalPort(unsigned short port)
{
    std::memset(&m_local_addr, 0, sizeof(m_local_addr));

    m_local_addr.sin_family = AF_INET;
    m_local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_local_addr.sin_port = htons(port);

    if (::bind(m_sock_fdesc, reinterpret_cast<sockaddr*>(&m_local_addr), m_addr_size) < 0){
        throw SocketException("Failed to set local port : bind()", true);
    }
}

void Socket::setLocalAddressAndPort(const std::string& l_add, unsigned short l_port)
{
    std::memset(&m_local_addr, 0, sizeof(m_local_addr));
    m_local_addr.sin_family = AF_INET;
    hostent *host;

    if ((host = gethostbyname(l_add.c_str())) == nullptr){
        throw SocketException("Failed to set local address & port : gethostbyname()", true);
    }
    //check this conversion -Maybe use getaddrinfo()
    //m_local_addr.sin_addr.s_addr = *((unsigned int *) host->h_addr_list[0]);
    m_local_addr.sin_addr.s_addr = *(reinterpret_cast<unsigned int *>(host->h_addr_list[0]));

    m_local_addr.sin_port = htons(l_port);

    if (::bind(m_sock_fdesc, reinterpret_cast<sockaddr*>(&m_local_addr), m_addr_size) < 0){
        throw SocketException("Failed to set local address & port : bind()", true);
    }
}

std::string Socket::getRemoteAddress()
{
    unsigned int addr_len = sizeof(m_local_addr);

    if (getpeername(m_sock_fdesc, reinterpret_cast<sockaddr*>(&m_local_addr), reinterpret_cast<socklen_t*>(&addr_len)) < 0) {
        throw SocketException("Failed to get remote address : getpeername()", true);
    }

    return inet_ntoa(m_local_addr.sin_addr);
}

unsigned short Socket::getRemotePort()
{
    unsigned int addr_len = sizeof(m_local_addr);

    if (getpeername(m_sock_fdesc, reinterpret_cast<sockaddr*>(&m_local_addr), reinterpret_cast<socklen_t*>(&addr_len)) < 0) {
        throw SocketException("Failed to get remote port : getpeername()", true);
    }

    return ntohs(m_local_addr.sin_port);
}

/*Basic functionality*/
void Socket::connect(const std::string& remote_add, unsigned short remote_port)
{
    std::memset(&m_remote_addr, 0, m_addr_size);
    m_remote_addr.sin_family = AF_INET;

    hostent *host;

    if ((host = gethostbyname(remote_add.c_str())) == nullptr){
        throw SocketException("Failed to set up connect : gethostbyname()", true);
    }

   // m_remote_addr.sin_addr.s_addr = *((unsigned int *) host->h_addr_list[0]);
    m_remote_addr.sin_addr.s_addr = *(reinterpret_cast<unsigned int *>(host->h_addr_list[0]));

    m_remote_addr.sin_port = htons(remote_port);

    if(::connect(m_sock_fdesc, reinterpret_cast<sockaddr*>(&m_remote_addr), m_addr_size) < 0){
        throw SocketException("Failed to Connect to remote address : connect()", true);
    }
}

void Socket::send(const void *buffer, size_t buffer_length)
{
    if(::send(m_sock_fdesc, buffer, buffer_length, 0) < 0){
        throw SocketException("Failed to Send to remote address : send()", true);
    }
}


ssize_t Socket::recv(void *buffer, size_t buffer_length)
{
    ssize_t ret_bytes;
    //if ret_bytes = 0, remote has closed the connection
    if((ret_bytes = ::recv(m_sock_fdesc, buffer, buffer_length, 0)) < 0){
        throw SocketException("Failed to Receive from remote address : recv()", true);
    }
    return ret_bytes;
}
