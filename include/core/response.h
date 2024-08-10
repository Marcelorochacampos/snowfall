#ifndef SNOWFALL_CORE_RESPONSE_H
#define SNOWFALL_CORE_RESPONSE_H

#include <string>
#include <unordered_map>
#include <variant>

#include "json.h"

namespace snowfall
{
namespace core
{

using BodyType = std::variant<bool, int, double, std::string, char*, ::snowfall::core::JsonObject>;
class Response
{
 public:
  Response();
  Response& body(BodyType v)
  {
    m_body = v;
    return *this;
  }
  Response& content_type(std::string v)
  {
    m_contentType = v;
    return *this;
  };
  Response& status(int v)
  {
    m_status = v;
    return *this;
  }

  BodyType get_body() { return m_body; }
  std::string get_content_type() { return m_contentType; }
  int get_status() { return m_status; }

  std::string build();

 private:
  BodyType m_body;
  std::string m_contentType{"text/plain"};
  int m_status{200};
};
}  // namespace core
}  // namespace snowfall

#endif