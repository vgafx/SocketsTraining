#pragma once

#include "socket.h"

class UDPSocket : public Socket
{
public:
    UDPSocket();

    UDPSocket(unsigned short local_port);

    UDPSocket(const std::string& local_addr, unsigned short local_port);

    void sendTo(const void* buffer, size_t buffer_length, const std::string& remote_addr, unsigned short remote_port);

    ssize_t recvFrom(void* buffer, size_t buffer_length, std::string& source_addr, unsigned short& source_port);

};

