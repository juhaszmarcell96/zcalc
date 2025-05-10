/*
 * Copyright (C) 2025 Marcell Juhasz
 *
 * This software is licensed under a non-commercial license.
 * Non-commercial use (personal, academic, research) is allowed for free.
 * Commercial use requires a paid license.
 * Hosting as a service is prohibited without explicit permission.
 *
 * See LICENSE for details or contact marcell.juhasz96@gmail.com.
 */

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>
#include <sstream>

#include "session.hpp"

#include <zcalc/network.hpp>
#include <zcalc/network_calculator.hpp>
#include <zcalc/network_builder.hpp>
#include <zcalc/json/parser.hpp>

namespace zcalc {

void Session::start() {
    m_websocket.async_accept(
        [self = shared_from_this()](boost::beast::error_code ec) {
            if (!ec) {
                self->read_message();
            }
            else {
                std::cerr << "websocket handshake failed: " << ec.message() << std::endl;
            }
        }
    );
}

void Session::read_message() {
    m_websocket.async_read(
        m_buffer,
        [self = shared_from_this()](boost::beast::error_code ec, std::size_t bytes_transferred) {
            boost::ignore_unused(bytes_transferred);
            if (!ec) {
                std::string received = boost::beast::buffers_to_string(self->m_buffer.data());
                self->m_buffer.consume(self->m_buffer.size()); // Clear buffer
                std::string response = self->process_message(received);
                self->m_send_buffer = std::make_shared<std::string>(std::move(response));
                self->write_message();
            }
            else if (ec == boost::beast::websocket::error::closed) {
                // client closed the connection
                std::cout << "client closed the connection" << std::endl;
            }
            else {
                std::cerr << "read error: " << ec.message() << std::endl;
            }
        }
    );
}

void Session::write_message() {
    m_websocket.text(m_websocket.got_text());
    m_websocket.async_write(
        boost::asio::buffer(*m_send_buffer),
        [self = shared_from_this()](boost::beast::error_code ec, std::size_t bytes_transferred) {
            boost::ignore_unused(bytes_transferred);
            if (!ec) {
                self->read_message(); // Wait for next message
            }
            else {
                std::cerr << "write error: " << ec.message() << std::endl;
            }
        }
    );
}

// send from client: {"n":3,"c":[{"i":0,"t":0,"r":10,"u":7,"n0":2,"n1":0},{"i":1,"t":0,"r":10,"u":7,"n0":1,"n1":2},{"i":2,"t":4,"v":1,"u":7,"f":0,"p":1,"n0":1,"n1":0}]}
std::string Session::process_message(const std::string& msg) {
    zcalc::json::JsonParser parser { msg };
    try {
        const auto json = parser.parse();
        auto network = zcalc::NetworkBuilder::from_json(json);
        if (!network.has_value()) {
            return "failed to parse network";
        }
        const auto results = zcalc::NetworkCalculator::compute(network.value());
        zcalc::json::Array responses;
        for (const auto& [key, val] : results) {
            zcalc::json::Array phasors;
            for (const auto& phasor : val) {
                phasors.push_back(
                    zcalc::json::Object{
                        {"m", phasor.get_magnitude()},
                        {"p", phasor.get_phase().as_radians()},
                        {"f", phasor.get_frequency().as_rad_per_sec()}
                    }
                );
            }
            responses.push_back(
                zcalc::json::Object{
                    {"n", key},
                    {"r", std::move(phasors)}
                }
            );
        }
        std::stringstream ss;
        ss << responses;
        return ss.str();
    }
    catch (const std::runtime_error& e) {
        return e.what();
    }
    catch (...) {
        return "unknown error";
    }
}

} /* namespace zcalc */