#include "my_controller.h"

#include <iostream>

#include <snowfall/core/json.h>

MyController::MyController() {}

void MyController::Hello(::snowfall::core::Request& req, ::snowfall::core::Response& res)
{
  res.body("Hello world!").status(200);
  return;
}

void MyController::List(::snowfall::core::Request& req, ::snowfall::core::Response& res)
{
  std::cout << "Listing records " << std::endl;
  ::snowfall::core::JsonObject body;
  body["name"] = ::snowfall::core::JsonValue("Foo");
  body["surname"] = ::snowfall::core::JsonValue("Bar");
  body["age"] = ::snowfall::core::JsonValue(35);
  body["number_of_things"] = ::snowfall::core::JsonValue(22.2f);
  res.body(body).status(200);
  return;
}