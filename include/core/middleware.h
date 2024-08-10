#ifndef SNOWFALL_CORE_MIDDLEWARE_H
#define SNOWFALL_CORE_MIDDLEWARE_H

#include <iostream>
#include <string>

#include "request.h"
#include "response.h"

namespace snowfall
{
namespace core
{

class Middleware
{
 public:
  virtual void execute(::snowfall::core::Request& request, ::snowfall::core::Response& response)
  {
    std::cout << "Middleware not implemented." << std::endl;
  };

 private:
};

}  // namespace core
}  // namespace snowfall

#endif