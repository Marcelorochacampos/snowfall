#include <core/response.h>

#include <iostream>
#include <sstream>
#include <variant>

namespace snowfall
{
namespace core
{

Response::Response() {}

std::string parse_body(::snowfall::core::BodyType v)
{
  if (std::holds_alternative<std::string>(v))
  {
    return std::get<std::string>(v);
  }
  if (std::holds_alternative<bool>(v))
  {
    return std::to_string(std::get<bool>(v));
  }
  if (std::holds_alternative<int>(v))
  {
    return std::to_string(std::get<int>(v));
  }
  if (std::holds_alternative<double>(v))
  {
    return std::to_string(std::get<double>(v));
  }
  if (std::holds_alternative<char *>(v))
  {
    return std::get<char *>(v);
  }
  if (std::holds_alternative<::snowfall::core::JsonObject>(v))
  {
    return ::snowfall::core::JsonValue(std::get<::snowfall::core::JsonObject>(v)).toString();
  }
  return "";
}

std::string Response::build()
{
  
  std::string body = parse_body(m_body);
  std::size_t content_length = body.size();
  std::string response = "HTTP/1.1 " + std::to_string(m_status) + " OK\r\n";
  response += "Content-Type: text/plain\r\n";
  response += "Content-Length: " + std::to_string(content_length) + "\r\n";
  response += "\r\n";
  response += body;

  return response;
}

}  // namespace core
}  // namespace snowfall