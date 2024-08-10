#include <core/json.h>

namespace snowfall
{
namespace core
{
std::string JsonValue::toString() const
{
  switch (type) {
    case JsonType::Null:
        return "null";
    case JsonType::Boolean:
        return std::get<bool>(value) ? "true" : "false";
    case JsonType::Int: {
        std::ostringstream oss;
        oss << std::get<int>(value);
        return oss.str();
    }
    case JsonType::Double: {
        std::ostringstream oss;
        oss << std::get<double>(value);
        return oss.str();
    }
    case JsonType::Float: {
        std::ostringstream oss;
        oss << std::get<float>(value);
        return oss.str();
    }
    case JsonType::String:
        return "\"" + std::get<std::string>(value) + "\"";
    case JsonType::Object: {
        const auto& obj = std::get<JsonObject>(value);
        std::ostringstream oss;
        oss << "{";
        for (auto it = obj.begin(); it != obj.end(); ++it) {
            if (it != obj.begin()) {
                oss << ", ";
            }
            oss << "\"" << it->first << "\": " << it->second.toString();
        }
        oss << "}";
        return oss.str();
    }
    case JsonType::Array: {
        const auto& arr = std::get<JsonArray>(value);
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < arr.size(); ++i) {
            if (i > 0) {
                oss << ", ";
            }
            oss << arr[i].toString();
        }
        oss << "]";
        return oss.str();
    }
    default: return "";
  }
}
}
}
