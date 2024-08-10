#include "my_middleware.h"

#include <iostream>

void MyMiddleware::execute(::snowfall::core::Request& request, ::snowfall::core::Response& response)
{
  std::cout << "Handling session on middleware." << std::endl;
  auto headers = request.get_headers();
  headers["session"] = "my_generated_session";
  request.set_headers(headers);
  return;
}