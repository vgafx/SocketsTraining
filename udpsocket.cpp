#include "udpsocket.h"

UDPSocket::UDPSocket()
    :Socket (SOCK_DGRAM, IPPROTO_UDP)
{
}

UDPSocket::UDPSocket(unsigned short local_port)
    :Socket (SOCK_DGRAM, IPPROTO_UDP)
{
    setLocalPort(local_port);
}

UDPSocket::UDPSocket(const std::string &local_addr, unsigned short local_port)
    :Socket (SOCK_DGRAM, IPPROTO_UDP)
{
    setLocalAddressAndPort(local_addr, local_port);
}

void UDPSocket::sendTo(const void *buffer, size_t buffer_length, const std::string &remote_addr, unsigned short remote_port)
{
    memset(&m_remote_addr, 0, m_addr_size);
    m_remote_addr.sin_family = AF_INET;

    hostent *host;
    if ((host = gethostbyname(remote_addr.c_str())) == nullptr){
        throw SocketException("UDP:Failed to setup sendTo : gethostbyname()", true);

    }

   // m_remote_addr.sin_addr.s_addr = *((unsigned int *) host->h_addr_list[0]);
    m_remote_addr.sin_addr.s_addr = *(reinterpret_cast<unsigned int *>(host->h_addr_list[0]));
    m_remote_addr.sin_port = htons(remote_port);

    if(::sendto(m_sock_fdesc, buffer, buffer_length, 0, reinterpret_cast<sockaddr*>(&m_remote_addr), m_addr_size) < 0){
        throw SocketException("Failed to sendTo remote host : sendto()", true);
    }
}

ssize_t UDPSocket::recvFrom(void *buffer, size_t buffer_length, std::string &source_addr, unsigned short& source_port)
{
    ssize_t ret_bytes;

    if((ret_bytes = ::recvfrom(m_sock_fdesc, buffer, buffer_length, 0, reinterpret_cast<sockaddr*>(&m_remote_addr), &m_addr_size)) < 0){
        throw SocketException("Failed to recvFrom remote host : recvfrom()", true);
    }
    source_addr = inet_ntoa(m_remote_addr.sin_addr);
    source_port = ntohs(m_remote_addr.sin_port);

    return ret_bytes;
}
