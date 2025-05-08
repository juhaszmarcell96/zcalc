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
#include <iostream>
#include <memory>

#include "server.hpp"
#include "session.hpp"

namespace zcalc {

Server::Server(boost::asio::io_context& io_context, std::uint16_t port)
    : m_acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    accept_connection();
}

void Server::accept_connection() {
    m_acceptor.async_accept(
        [this](boost::beast::error_code ec, boost::asio::ip::tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket))->start();
            }
            else {
                std::cerr << "accept error: " << ec.message() << std::endl;
            }
            accept_connection();
        }
    );
}

} /* namespace zcalc */