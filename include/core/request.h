#ifndef SNOWFALL_CORE_REQUEST_H
#define SNOWFALL_CORE_REQUEST_H

#include <unordered_map>
#include <string>
#include <variant>

namespace snowfall
{
namespace core
{
class Request
{
 public:
  Request();
  void set_body(
      std::variant<std::string, int, double, std::unordered_map<std::string, std::variant<std::string, int, double>>> v)
  {
    m_body = v;
  }
  void set_connection(std::string v) { m_connection = v; }
  void set_headers(std::unordered_map<std::string, std::string> v) { m_headers = v; }
  void set_host(std::string v) { m_host = v; }
  void set_method(std::string v) { m_method = v; }
  void set_path(std::string v) { m_path = v; }
  void set_user_agent(std::string v) { m_userAgent = v; }

  const std::string get_connection() { return m_connection; }
  const std::unordered_map<std::string, std::string> get_headers() { return m_headers; }
  const std::string get_host() { return m_host; }
  const std::string get_method() { return m_method; }
  const std::string get_path() { return m_path; }
  const std::string get_user_agent() { return m_userAgent; }

 private:
  std::variant<std::string, int, double, std::unordered_map<std::string, std::variant<std::string, int, double>>> m_body;
  std::string m_connection;
  std::unordered_map<std::string, std::string> m_headers;
  std::string m_host;
  std::string m_method;
  std::string m_path;
  std::string m_userAgent;
};
}  // namespace core
}  // namespace snowfall

#endif