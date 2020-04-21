#include "socketexception.h"

SocketException::SocketException(const std::string& message, bool sys_msg) noexcept
    : m_message(message)
{
    if(sys_msg){
        m_message.append(": ");
        m_message.append(strerror(errno));
    }
}

SocketException::~SocketException() noexcept
{

}

const char* SocketException::what() const noexcept
{
    return m_message.c_str();
}
