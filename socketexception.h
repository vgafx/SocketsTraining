#pragma once
#include <stdexcept>
#include <string>
#include <errno.h> //Linux
#include <string.h>

class SocketException : public std::exception
{
private:
  std::string m_message;
public:
  SocketException(const std::string &message, bool sys_msg = false) noexcept;
  ~SocketException() noexcept;

  const char *what() const noexcept;
};
