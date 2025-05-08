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

#include "session.hpp"

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
                // echo the received message back
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
        m_buffer.data(),
        [self = shared_from_this()](boost::beast::error_code ec, std::size_t bytes_transferred) {
            boost::ignore_unused(bytes_transferred);
            if (!ec) {
                self->m_buffer.consume(self->m_buffer.size()); // Clear buffer
                self->read_message(); // Wait for next message
            }
            else {
                std::cerr << "write error: " << ec.message() << std::endl;
            }
        }
    );
}

} /* namespace zcalc */