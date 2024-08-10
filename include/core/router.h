#ifndef SNOWFALL_CORE_ROUTER_H
#define SNOWFALL_CORE_ROUTER_H

#include <exception>
#include <iostream>
#include <string>
#include <unordered_map>

#include "http_methods.h"
#include "request.h"
#include "response.h"
#include "middleware.h"

namespace snowfall
{
namespace core
{

class Router
{
 public:
  Router(const Router&) = delete;
  Router& operator=(const Router&) = delete;

  static Router& instance()
  {
    static Router instance;
    return instance;
  }

  template <typename ClassType>
  void route(const std::string& path, void (ClassType::*handler)(Request&, Response&), ClassType* instance,
             HttpMethods http_method)
  {
    if (path.empty())
    {
      throw std::runtime_error("Path cannot be empty");
    }
    std::string k = (path + ":" + readable_http_method(http_method)).c_str();
    m_routes[k] = [instance, handler](Request& req, Response& res) { (instance->*handler)(req, res); };
  }
  void handle(const std::string& path, Request& req, Response& res);

  Router& middlewares(std::vector<std::shared_ptr<::snowfall::core::Middleware>> middlewares);
  void for_routes(std::unordered_map<std::string, HttpMethods>& routes);

 private:
  Router() {}
  std::unordered_map<std::string, std::function<void(Request&, Response&)>> m_routes;
  std::vector<std::shared_ptr<Middleware>> m_tmpMiddlewares;
  std::unordered_map<std::string, std::vector<std::shared_ptr<Middleware>>> m_middlewares;
};

}  // namespace core
}  // namespace snowfall

#endif