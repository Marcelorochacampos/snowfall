#ifndef MY_MIDDLEWARE_H
#define MY_MIDDLEWARE_H

#include <snowfall/core/request.h>
#include <snowfall/core/response.h>
#include <snowfall/core/middleware.h>

class MyMiddleware : public ::snowfall::core::Middleware
{
  public:
    void execute(::snowfall::core::Request& request, ::snowfall::core::Response& response);
};

#endif