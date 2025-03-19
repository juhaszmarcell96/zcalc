#pragma once

#include <variant>
#include <optional>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

namespace zcalc {
namespace json {

// forward declaration
class Element;

// alias definitions
using Null   = std::monostate;
using Bool   = bool;
using Number = double;
using String = std::string;
using Array  = std::vector<Element>;
using Object = std::unordered_map<std::string, Element>;

using Value = std::variant<Null, Bool, Number, String, Array, Object>;

struct Element {
    Value value;

    // constructors for different types
    Element() : value(Null{}) {}
    Element(bool b) : value(b) {}
    Element(double n) : value(n) {}
    Element(int n) : value(static_cast<double>(n)) {}
    Element(const std::string& s) : value(s) {}
    Element(const char* s) : value(std::string(s)) {}
    Element(const Array& arr) : value(arr) {}
    Element(const Object& obj) : value(obj) {}

    // Overloaded getter functions
    bool is_null() const { return std::holds_alternative<Null>(value); }
    bool is_bool() const { return std::holds_alternative<Bool>(value); }
    bool is_number() const { return std::holds_alternative<Number>(value); }
    bool is_string() const { return std::holds_alternative<String>(value); }
    bool is_array() const { return std::holds_alternative<Array>(value); }
    bool is_object() const { return std::holds_alternative<Object>(value); }

    Bool as_bool() const { return std::get<Bool>(value); }
    Number as_number() const { return std::get<Number>(value); }
    const String& as_string() const { return std::get<String>(value); }
    const Array& as_array() const { return std::get<Array>(value); }
    const Object& as_object() const { return std::get<Object>(value); }

    friend std::ostream& operator<<(std::ostream& os, const Element& e) {
        std::visit(
            [&os](const auto& v) {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, Null>) {
                os << "null";
            }
            else if constexpr (std::is_same_v<T, Bool>) {
                os << (v ? "true" : "false");
            }
            else if constexpr (std::is_same_v<T, Number>) {
                os << v;
            }
            else if constexpr (std::is_same_v<T, String>) {
                os << '"' << v << '"';
            }
            else if constexpr (std::is_same_v<T, Array>) {
                os << "[";
                for (size_t i = 0; i < v.size(); ++i) {
                    os << v[i];
                    if (i + 1 < v.size()) {
                        os << ",";
                    }
                }
                os << "]";
            }
            else if constexpr (std::is_same_v<T, Object>) {
                os << "{";
                size_t count = 0;
                for (const auto& [key, value] : v) {
                    os << '"' << key << "\":" << value;
                    if (++count < v.size()) { os << ","; }
                }
                os << "}";
            }
        }, e.value);
        return os;
    }
};

} /* namespace json */
} /* namespace zcalc */