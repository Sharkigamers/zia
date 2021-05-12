/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** TcpConnection
*/

#pragma once

#include <boost/asio.hpp>
#include <memory>

#include <iostream>

#include "TcpSocket.hpp"

namespace Zia {
    namespace Network {
        class TcpConnection : public Zia::IConnection {
            public:
                explicit TcpConnection(boost::asio::io_context& ctx) : _socket(ctx) {
                    //_socket.getSocket()->non_blocking(true);
                };

                std::unique_ptr<boost::asio::ip::tcp::socket>& getSocket() { return _socket.getSocket(); };

                void setNonBlocking(bool state) { _socket.getSocket()->non_blocking(state); }

                int getNativeSocket(void) const final {
                    return _socket.getNativeSocket();
                }

                const std::string& getRemoteIP(void) const final {
                    return _socket.getRemoteIP();
                }

                size_t read(size_t buf_size, char* buf) {
                    log("Reading message of length " + std::to_string(buf_size));
                    return _socket.read(buf_size, buf);
                };

                size_t write(size_t buf_size, const char* buf) {
                    log("Writing message of length " + std::to_string(buf_size));
                    return _socket.write(buf_size, buf);
                }

                void log(const std::string& str) final {
                    std::cout << "[TcpConnection]: " << str << std::endl;
                };

                ~TcpConnection() = default;
            private:
                Zia::Network::TcpSocket _socket;
        };
    }
}