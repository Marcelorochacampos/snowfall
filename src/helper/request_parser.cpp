#include <helper/request_parser.h>

#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <functional>

// Parsed request line GET /favicon.ico HTTP/1.1
// Parsed request line Host: localhost:50056
// Parsed request line Connection: keep-alive
// Parsed request line sec-ch-ua: "Not/A)Brand";v="8", "Chromium";v="126", "Google Chrome";v="126"
// Parsed request line sec-ch-ua-mobile: ?0
// Parsed request line User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36
// Parsed request line sec-ch-ua-platform: "macOS"
// Parsed request line Accept: image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8
// Parsed request line Sec-Fetch-Site: same-origin
// Parsed request line Sec-Fetch-Mode: no-cors
// Parsed request line Sec-Fetch-Dest: image
// Parsed request line Referer: http://localhost:50056/api/users/code
// Parsed request line Accept-Encoding: gzip, deflate, br, zstd
// Parsed request line Accept-Language: pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7
// Parsed request line

namespace snowfall
{
namespace helper
{
using HeaderSetter = std::function<void(core::Request &, const std::string &)>;

::snowfall::core::Request parse_request(const std::string &r)
{
    core::Request request;
    std::unordered_map<std::string, HeaderSetter> header_map = {
        {"Host", [](core::Request &req, const std::string &value) { req.set_host(value); }},
        {"Connection", [](core::Request &req, const std::string &value) { req.set_connection(value); }},
        {"User-Agent", [](core::Request &req, const std::string &value) { req.set_user_agent(value); }},
        //...
    };

    std::vector<std::string> lines = vectorize_request(r);

    if (!lines.empty()) {
        request.set_method(parse_method(lines[0]));
        request.set_path(parse_path(lines[0]));
    }

    for (const auto &line : lines) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string header = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            auto it = header_map.find(header);
            if (it != header_map.end()) {
                it->second(request, value);
            }
        }
    }
  
    return request;
}

std::vector<std::string> vectorize_request(const std::string &r)
{
  std::vector<std::string> parts;
  size_t pos = 0, end;

  while ((end = r.find("\r\n", pos)) != std::string::npos) {
    parts.push_back(r.substr(pos, end - pos));
    pos = end + 2;
  }

  return parts;
}

std::string parse_method(const std::string &line)
{
  size_t pos = line.find(' ');
  if (pos == std::string::npos) {
    throw std::runtime_error("Invalid HTTP request line");
  }
  return line.substr(0, pos);
}

std::string parse_path(const std::string &line)
{
  size_t first_whitespace = line.find(' ');
  size_t pos = line.find(' ', first_whitespace + 1);
  if (pos == std::string::npos) {
    throw std::runtime_error("Invalid HTTP request line");
  }
  return line.substr(first_whitespace + 1, pos - first_whitespace - 1); 
}
}  // namespace helper
}  // namespace snowfall