#ifndef SNOWFALL_CORE_HTTP_METHODS_H
#define SNOWFALL_CORE_HTTP_METHODS_H

#include <string>

enum class HttpMethods {
  GET, POST, PUT, PATCH, DELETE, OPTIONS
};

inline std::string readable_http_method(HttpMethods v)
{
  switch(v) {
    case HttpMethods::GET: return "GET";
    case HttpMethods::POST: return "POST";
    case HttpMethods::PUT: return "PUT";
    case HttpMethods::PATCH: return "PATCH";
    case HttpMethods::DELETE: return "DELETE";
    case HttpMethods::OPTIONS: return "DELETE";
    default: return "[[unknown]]";
  }
}

#endif