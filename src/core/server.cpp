#include <core/server.h>

#include <iostream>     // Standard IO Operations
#include <sys/socket.h> // For Socket functions
#include <netinet/in.h> // For sockaddr_in structure
#include <unistd.h>     // For close function
#include <cstring>      // For memset function
#include <arpa/inet.h>  // For inet_addr function

#include <core/response.h>
#include <core/router.h>

namespace snowfall
{
namespace core
{
Server::Server(const std::string address, const int port) : m_address(address), m_port(port), m_serverFd(-1) {}

Server::~Server()
{
  if (m_serverFd != -1) {
    close(m_serverFd);
    std::cout << "[*][Snowfall::Server::~Server] Server socket closed" << std::endl;
  }
}

void Server::run() {
  struct sockaddr_in server_addr;

  m_serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (m_serverFd == -1) {
    std::cerr << "[*][Snowfall::Server::run] Failed to create socket" << std::endl;
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(m_address.c_str());
  server_addr.sin_port = htons(m_port);

  if (bind(m_serverFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    std::cerr << "[*][Snowfall::Server::run] Failed to bind socket" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (listen(m_serverFd, 10) < 0) {
    std::cerr << "[*][Snowfall::Server::run] Failed to listen on socket" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "[*][Snowfall::Server::run] Server listening on " << m_address << ":" << std::to_string(m_port) << std::endl;

  while (true) {
    int client_fd = accept(m_serverFd, nullptr, nullptr);
    if (client_fd < 0) {
      std::cerr << "[*][Snowfall::Server::run] Failed to accept client connection" << std::endl;
      continue;
    }
    handle_client_request(client_fd);
  }
}

void Server::handle_client_request(int client_fd) {
  char buffer[1024] = {0};
  read(client_fd, buffer, sizeof(buffer));

  std::string r(buffer);
  ::snowfall::core::Request request = ::snowfall::helper::parse_request(r);
  ::snowfall::core::Response response;

  ::snowfall::core::Router& router = ::snowfall::core::Router::instance();
  router.handle(request.get_path().c_str(), request, response);

  send(client_fd, response.build().c_str(), response.build().length(), 0);
  close(client_fd);
}

}  // namespace core
}  // namespace snowfall
