#include <core/router.h>

namespace snowfall
{
namespace core
{

void Router::handle(const std::string& path, Request& req, Response& res)
{
  if (path.empty())
  {
    res.status(204);
    return;
  }
  std::string transformed_method = req.get_method();
  std::transform(transformed_method.begin(), transformed_method.end(), transformed_method.begin(),
                  [](unsigned char c) { return std::toupper(c); });
  std::string k = (path + ":" + transformed_method).c_str();
  auto it = m_routes.find(k);
  if (it == m_routes.end())
  {
    res.status(204);
    return;
  }

  auto it_route_middlewares = m_middlewares.find(k);
  if (it_route_middlewares != m_middlewares.end())
  {
    std::vector<std::shared_ptr<Middleware>> middlewares = it_route_middlewares->second;
    std::cout << "Middleware size dentro if " << middlewares.size() << std::endl;
    for (auto &middleware : middlewares)
    {
      middleware.get()->execute(req, res);
    }  
  }

  it->second(req, res);
  return;
}

Router& Router::middlewares(std::vector<std::shared_ptr<::snowfall::core::Middleware>> middlewares)
{
  m_tmpMiddlewares = middlewares;
  return Router::instance();
}
void Router::for_routes(std::unordered_map<std::string, HttpMethods>& routes)
{
  for (auto curr : routes)
  {
    std::string k = (curr.first + ":" + readable_http_method(curr.second)).c_str();
    std::vector<std::shared_ptr<Middleware>> curr_middlewares = m_middlewares[k];
    for (auto &curr_middleware : m_tmpMiddlewares)
    {
      curr_middlewares.emplace_back(curr_middleware);
    }
    m_middlewares[k] = curr_middlewares;
  }
  std::vector<std::shared_ptr<Middleware>> fresh;
  m_tmpMiddlewares = fresh;
}

}  // namespace core
}  // namespace snowfall