#include <snowfall/core/server.h>
#include <snowfall/core/router.h>

#include "my_controller.h"

int main()
{
  ::snowfall::core::Server server{"0.0.0.0", 50056};

  MyController my_controller;

  ::snowfall::core::Router& router = ::snowfall::core::Router::instance();

  router.route("/api/hello", &MyController::Hello, &my_controller, HttpMethods::POST);
  router.route("/api/users", &MyController::List, &my_controller, HttpMethods::GET);

  server.run();
}