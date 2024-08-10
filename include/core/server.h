#ifndef SNOWFALL_CORE_SERVER_H
#define SNOWFALL_CORE_SERVER_H

#include <string>

#include "../helper/request_parser.h"

namespace snowfall
{
namespace core
{
class Server
{
 public:
  Server(const std::string address, const int port);
  ~Server();
  void run();

 private:
  const std::string m_address;
  const int m_port;
  int m_serverFd;

  void handle_client_request(int client_fd);
};
}  // namespace core
}  // namespace snowfall

#endif