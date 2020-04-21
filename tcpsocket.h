#pragma once

#include "socket.h"

class TCPSocket : public Socket
{
public:
    TCPSocket();

    TCPSocket(const std::string& remote_addr, unsigned short remote_port);

private:
    TCPSocket(int fresh_connection);
    friend class TCPServerSocket;
};

