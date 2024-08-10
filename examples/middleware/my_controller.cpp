#include "my_controller.h"

#include <iostream>

MyController::MyController() {}

void MyController::List(::snowfall::core::Request& req, ::snowfall::core::Response& res)
{
  std::cout << "Listing records" << std::endl;
  res.body("Listed records!").status(200);
  return;
}