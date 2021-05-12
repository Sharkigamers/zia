/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** Parser
*/

#pragma once


#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/opensslv.h>

#include "../../Zia-Docs/include/zia/Zia.hpp"

#include <iostream>
#include <array>

#if defined (__linux__)
    #include <unistd.h>
    #include <fcntl.h>
#endif

namespace Zia {
    class SSLConnection : public Zia::IConnection {
        public:
            SSLConnection(Zia::IConnection& base, const std::string &certPath, const std::string &keyPath) : _baseConnection(base)
                , _certPath(certPath), _keyPath(keyPath)
            {
                if (setupSSL() == true) {
                    _isValid = false;
                    return;
                }

                _ssl = SSL_new(_ctx);
                SSL_set_accept_state(_ssl);

                if (SSL_set_fd(_ssl, base.getNativeSocket()) <= 0) {
                    log("Error: SSL set fd");
                }
                int ret = SSL_accept(_ssl);
                if (!ret) {
                    log("Error: SSL accept");
                } else if (ret < 0) {
                    char msg[1024];
                    switch (SSL_get_error(_ssl, ret)) {
                        case SSL_ERROR_WANT_WRITE:
                            log("Error in init_SSL: SSL_ERROR_WANT_WRITE");
                            break;
                        case SSL_ERROR_WANT_READ:
                            log("Error in init_SSL: SSL_ERROR_WANT_READ");
                            break;
                        case SSL_ERROR_ZERO_RETURN:
                            log("Error in init_SSL: SSL_ERROR_ZERO_RETURN");
                            break;
                        case SSL_ERROR_SSL:
                            ERR_error_string_n(ERR_get_error(), msg, sizeof(msg));
                            log("Error in init_SSL: SSL_ERROR_SSL: " + std::string(msg));
                            break;
                        default:
                            log("Error in init_SSL: SSL Connect fatal error: ");
                            break;
                        }
                }
                int flags = fcntl(SSL_get_fd(_ssl), F_GETFL, 0);
                fcntl(SSL_get_fd(_ssl), F_SETFL, flags | O_NONBLOCK);
                _isValid = true;
            };

            bool setupSSL()
            {
                _ctx = SSL_CTX_new(SSLv23_server_method());
                if (!_ctx) {
                    log("Error SSL: SSL_CTX_new");
                    return true;
                }

                int err = SSL_CTX_set_cipher_list(_ctx, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
                if(err != 1) {
                    log("Error SSL CTX: cannot set the cipher list");
                    return true;
                }

                /* enable srtp */
                err = SSL_CTX_set_tlsext_use_srtp(_ctx, "SRTP_AES128_CM_SHA1_80");
                if(err != 0) {
                    log("Error SSL CTX: cannot setup srtp");
                    return true;
                }
                err = SSL_CTX_use_certificate_file(_ctx, _certPath.c_str(), SSL_FILETYPE_PEM);
                if(err != 1) {
                    log("Error SSL CTX: cannot load certificate file: " + _certPath);
                    return true;
                }
                err = SSL_CTX_use_PrivateKey_file(_ctx, _keyPath.c_str(), SSL_FILETYPE_PEM);
                if(err != 1) {
                    log("Error SSL CTX: cannot load certificate-key file: " + _keyPath);
                    return true;
                }
                err = SSL_CTX_check_private_key(_ctx);
                if(err != 1) {
                    log("Error SSL CTX: checking the private key failed");
                    return true;
                }
                return false;
            }

            ~SSLConnection() {
                log("Destroying ssl connection");
                if (_ssl) {
                    SSL_shutdown(_ssl);
                    SSL_free(_ssl);
                    _ssl = nullptr;
                }
                if (_ctx) {
                    SSL_CTX_free(_ctx);
                    _ctx = nullptr;
                }
            };

            const std::string& getRemoteIP(void) const final
            {
                return _baseConnection.getRemoteIP();
            };

            int getNativeSocket(void) const final
            {
                return _baseConnection.getNativeSocket();
            };

            size_t read(size_t buf_size, char* buf) {
                int size = SSL_read(_ssl, buf, buf_size);

                log("Size read: " + std::to_string(size));
                if (_nbTry >= 2) {
                    throw std::runtime_error("NbTry");
                }
                if (size <= 0) {
                    int err = SSL_get_error(_ssl, size);
                    switch (err) {
                    case SSL_ERROR_WANT_READ:
                        _nbTry += 1;
                        return 0;
                    case SSL_ERROR_ZERO_RETURN:
                    case SSL_ERROR_SYSCALL:
                    case SSL_ERROR_SSL:
                    default:
                        throw std::exception();
                    }
                }
                return size;
            };

            size_t write(size_t buf_size, const char* buf) {
                int ec = 0;

                ec = SSL_write(_ssl, buf, buf_size);
                log("Wrote: " + std::to_string(ec) + " bytes");
                return buf_size;
            };

            void log(const std::string& str) final
            {
                std::cout << "[SSL]: " << str << std::endl;
            };

            bool isValid() const { return _isValid; }

        private:
            Zia::IConnection& _baseConnection;
            SSL* _ssl;
            bool _active = true;
            int _newFd;
            SSL_CTX* _ctx;
            bool _error = false;
            int _nbTry = 0;

        private:
            std::string _certPath;
            std::string _keyPath;
            bool _isValid;

    };

    class SSLConnectionWrapper : public Zia::Module::IConnectionWrapper {
        public:
            SSLConnectionWrapper() = delete;
            explicit SSLConnectionWrapper(Zia::IConf &conf);
            ~SSLConnectionWrapper() {
                
            };

            std::unique_ptr<Zia::IConnection> create(Zia::IConnection& connection) final;
        protected:
        private:
            std::string _certPath;
            std::string _keyPath;
    };
}
