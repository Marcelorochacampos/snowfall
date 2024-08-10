#include <snowfall/core/router.h>
#include <snowfall/core/server.h>

#include <iostream>

#include "my_controller.h"
#include "my_middleware.h"

int main()
{
  ::snowfall::core::Server server{"0.0.0.0", 50056};

  MyController my_controller;
  MyMiddleware my_middleware;

  ::snowfall::core::Router& router = ::snowfall::core::Router::instance();

  router.route("/api/users", &MyController::List, &my_controller, HttpMethods::GET);

  std::vector<std::shared_ptr<::snowfall::core::Middleware>> middlewares;
  middlewares.push_back(std::make_shared<MyMiddleware>());
  std::unordered_map<std::string, HttpMethods> for_routes = {{"/api/users", HttpMethods::GET}};
  router.middlewares(middlewares).for_routes(for_routes);

  server.run();
}