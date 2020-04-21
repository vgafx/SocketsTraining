#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include <string>
#include <iostream>
#include <cstring>

#include "socketexception.h"

class Socket
{
protected:
    int m_sock_fdesc;
    unsigned short m_port;
    sockaddr_in m_local_addr;
    sockaddr_in m_remote_addr;
    unsigned int m_addr_size;


    /**
     * @brief Socket : Construct based on an existing socket
     * @param socket_fdesc : An existing socket file descriptor
     */
    Socket(int socket_fdesc);

    /**
     * @brief Socket : Defaults to IPv4
     * @param s_type SOCK_STREAM / SOCK_DGRAM
     * @param t_protocol tcp / udp, set to 0 for choice to depend on s_type
     **/
    Socket(int s_type, int t_protocol);

public:
    /*No Copy constructor or assignment operator*/
    Socket(const Socket& socket) = delete;
    Socket& operator=(const Socket& socket) = delete;

    ~Socket();

    /*Setters & Getters for the Address / Port of this socket*/
    std::string getLocalAddress();

    unsigned short getLocalPort();

    void setLocalPort(unsigned short port);

    void setLocalAddressAndPort(const std::string& l_add, unsigned short l_port);

    std::string getRemoteAddress();

    unsigned short getRemotePort();

    /*Methods for basic socket functionality*/
    void connect(const std::string& remote_add, unsigned short remote_port);

    void send(const void* buffer, size_t buffer_length);

    ssize_t recv(void* buffer, size_t buffer_length);

};
