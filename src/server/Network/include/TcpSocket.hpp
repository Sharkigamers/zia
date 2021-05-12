/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** TcpSocket
*/

#pragma once

#include <boost/asio.hpp>
#include <memory>

#include "../../../../Zia-Docs/include/zia/Zia.hpp"

namespace Zia {
    namespace Network {
        class TcpSocket : public Zia::IInputOutput {
        public:
            explicit TcpSocket(boost::asio::io_service& ioService) : _socket(std::make_unique<boost::asio::ip::tcp::socket>(ioService)) {

            };

            ~TcpSocket() = default;

            std::unique_ptr<boost::asio::ip::tcp::socket>& getSocket() { return _socket; };

            const std::string& getRemoteIP(void) const {
                const std::string &ip = _socket->remote_endpoint().address().to_string();
                return ip;
            }

            size_t read(size_t buf_size, char* buf) final {
                return _socket->read_some(boost::asio::buffer(buf, buf_size));
            };

            size_t write(size_t buf_size, const char* buf) final {
                return _socket->write_some(boost::asio::buffer(buf, buf_size));
            }

            int getNativeSocket(void) const {
                return _socket->native_handle();
            }

        protected:
        private:
            std::unique_ptr<boost::asio::ip::tcp::socket> _socket;
        };
    }
}