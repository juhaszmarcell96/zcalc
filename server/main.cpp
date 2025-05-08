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

#include <boost/asio/io_context.hpp>

#include <iostream>

#include "server.hpp"

int main() {
    try {
        boost::asio::io_context io_context;
        zcalc::Server server(io_context, 1111);
        std::cout << "websocket server listening on port 1111..." << std::endl;
        io_context.run();
    }
    catch (const std::exception& e) {
        std::cerr << "fatal error: " << e.what() << std::endl;
    }

    return 0;
}