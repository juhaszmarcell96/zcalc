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

#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>

namespace zcalc {

class Session : public std::enable_shared_from_this<Session> {
private:
    boost::beast::websocket::stream<boost::asio::ip::tcp::socket> m_websocket;
    boost::beast::flat_buffer m_buffer;
    void read_message();
    void write_message();
public:
    explicit Session(boost::asio::ip::tcp::socket socket) : m_websocket(std::move(socket)) {}
    void start();
};

} /* namespace zcalc */