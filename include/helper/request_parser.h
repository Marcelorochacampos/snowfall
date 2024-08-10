#ifndef SNOWFALL_HELPER_REQUEST_PARSER_H
#define SNOWFALL_HELPER_REQUEST_PARSER_H

#include <string>
#include <vector>

#include "../core/request.h"

namespace snowfall
{
namespace helper
{
  ::snowfall::core::Request parse_request(const std::string &request);
  std::vector<std::string> vectorize_request(const std::string &request);
  std::string parse_method(const std::string &line);
  std::string parse_path(const std::string &line);
}  // namespace helper
}  // namespace snowfall

#endif