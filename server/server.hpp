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

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>

namespace zcalc {

class Server {
private:
    boost::asio::ip::tcp::acceptor m_acceptor;
    void accept_connection();
public:
    Server(boost::asio::io_context& io_context, std::uint16_t port);
};

} /* namespace zcalc */