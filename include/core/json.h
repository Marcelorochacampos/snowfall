#ifndef SNOWFALL_CORE_JSON_H
#define SNOWFALL_CORE_JSON_H

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "../enum/json_type.h"

namespace snowfall
{
namespace core
{
class JsonValue;

using JsonObject = std::map<std::string, JsonValue>;
using JsonArray = std::vector<JsonValue>;

class JsonValue
{
 public:
  JsonValue() : type(JsonType::Null), value(nullptr) {}
  JsonValue(int b) : type(JsonType::Int), value(b) {}
  JsonValue(bool b) : type(JsonType::Boolean), value(b) {}
  JsonValue(float b) : type(JsonType::Float), value(b) {}
  JsonValue(double n) : type(JsonType::Double), value(n) {}
  JsonValue(const std::string& s) : type(JsonType::String), value(s) {}
  JsonValue(const char* s) : type(JsonType::String), value(std::string(s)) {}
  JsonValue(const JsonObject& obj) : type(JsonType::Object), value(obj) {}
  JsonValue(const JsonArray& arr) : type(JsonType::Array), value(arr) {}

  std::string toString() const;

 private:
  JsonType type;
  std::variant<std::nullptr_t, int, bool, float, double, std::string, JsonObject, JsonArray> value;
};
}
}

#endif