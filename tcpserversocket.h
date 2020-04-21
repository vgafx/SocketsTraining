#pragma once
#include "socket.h"
#include "tcpsocket.h"

class TCPServerSocket : public Socket
{
private:
    void setListen(int length);

public:
    TCPServerSocket(unsigned short local_port, int queue_length = 10);
    TCPServerSocket(const std::string& local_add, unsigned short local_port, int queue_length = 10);

    TCPSocket *accept();
};
