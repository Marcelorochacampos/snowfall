#ifndef MY_CONTROLLER_H
#define MY_CONTROLLER_H

#include <snowfall/core/request.h>
#include <snowfall/core/response.h>

class MyController
{
  public:
    MyController();
    void List(::snowfall::core::Request& req, ::snowfall::core::Response& res);
};

#endif