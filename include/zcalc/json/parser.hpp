#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

#include "zcalc/json/element.hpp"

namespace zcalc {
namespace json {

class JsonParser {
private:

    std::string m_input;
    size_t m_pos;

    void report_error (const std::string& message) {
        report_error(message + " at position " + std::to_string(m_pos));
    }

    char peek () {
        if (m_pos >= m_input.size()) {
            report_error("unexpected end of JSON");
        }
        return m_input[m_pos];
    }

    char consume () {
        if (m_pos >= m_input.size()) {
            report_error("unexpected end of JSON");
        }
        return m_input[m_pos++];
    }

    void consume (char c) {
        char ch = consume();
        if (c != ch) {
            report_error("expected '" + std::to_string(c) + "'");
        }
    }

    bool try_consume (char c) {
        char ch = peek();
        if (c == ch) {
            m_pos++;
            return true;
        }
        return false;
    }

    void skip_whitespace() {
        while (m_pos < m_input.size() && std::isspace(m_input[m_pos])) { m_pos++; }
    }

    Element parse_value() {
        skip_whitespace();
        if (m_pos >= m_input.size()) { report_error("unexpected end of JSON"); }

        char c = m_input[m_pos];
        if (c == '{') { return parse_object(); }
        if (c == '[') { return parse_array(); }
        if (c == '"') { return parse_string(); }
        if (std::isdigit(c) || c == '-') { return parse_number(); }
        if (c == 't' || c == 'f') { return parse_boolean(); }
        if (c == 'n') { return parse_null(); }
        
        report_error("invalid JSON value");
        return {};
    }

    Element parse_object() {
        Object obj;
        consume('{');
        while (true) {
            skip_whitespace();
            if (try_consume('}')) { break; }
            std::string key = parse_string().as_string();
            skip_whitespace();
            consume(':');
            skip_whitespace();
            obj[key] = parse_value();
            skip_whitespace();
            if (try_consume(',')) { continue; }
            if (try_consume('}')) { break; }
            report_error("expected ',' or '}' in object");
        }
        return obj;
    }

    Element parse_array() {
        Array arr;
        consume('[');
        while (true) {
            skip_whitespace();
            if (try_consume(']')) { break; }
            arr.push_back(parse_value());
            skip_whitespace();
            if (try_consume(',')) { continue; }
            if (try_consume(']')) { break; }
            report_error("expected ',' or ']' in array");
        }
        return arr;
    }

    Element parse_string() {
        consume('"');
        std::string str;
        
        while (true) {
            if (try_consume('"')) { break; }
            str.push_back(consume());
        }
        return str;
    }

    Element parse_number() {
        size_t start = m_pos;
        while (m_pos < m_input.size() && (std::isdigit(m_input[m_pos]) || m_input[m_pos] == '.' || m_input[m_pos] == '-')) { m_pos++; }
        return std::stod(m_input.substr(start, m_pos - start));
    }

    Element parse_boolean() {
        if (m_input.compare(m_pos, 4, "true") == 0) {
            m_pos += 4;
            return true;
        }
        else if (m_input.compare(m_pos, 5, "false") == 0) {
            m_pos += 5;
            return false;
        }
        report_error("invalid boolean value");
        return {};
    }

    Element parse_null() {
        if (m_input.compare(m_pos, 4, "null") == 0) {
            m_pos += 4;
            return Element();
        }
        report_error("invalid null value");
        return {};
    }
public:
    explicit JsonParser(const std::string& json_text) : m_input(json_text), m_pos(0) {}
    
    Element parse() {
        return parse_value();
    }
};

} /* namespace json */
} /* namespace zcalc */