/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** Request
*/

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <regex>

#include <map>
#include <vector>

#include "../../../Zia-Docs/include/zia/Zia.hpp"

namespace Zia {

    std::vector<std::string> methodToString = {
        "GET",
        "HEAD",
        "POST",
        "PUT",
        "DELETE",
        "TRACE",
        "OPTIONS",
        "CONNECT",
        "PATCH"
    };

    std::vector<std::string> versionToString = {
        "HTTP/1.0",
        "HTTP/1.1",
        "HTTP/2.0"
    };

    class Request : public Zia::IRequest {
        public:
            Request() = default;
            ~Request() = default;

            void setRequestHttp(std::string const &request) {
                _httpRequest = request;
            };
            std::string getRequestHttp() const {
                return _httpRequest;
            };

            //\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

            void setClientIP(std::string const &clientIp) {
                _clientIp = clientIp;
            }
            const std::string& getClientIP(void) const {
                return _clientIp;
            }

            void setProtocol(std::string const &protocol) {
                _protocol = protocol;
            }
            const std::string& getProtocol(void) const {
                return _protocol;
            }

            void setFilename(std::string const &filename) {
                _filename = filename;
            }
            const std::string& getFilename(void) const {
                return _filename;
            }

            void setUrl(std::string const &url) {
                _url = url;
            }
            const std::string& getURL(void) const {
                return _url;
            }

            //\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

            void setMethod(std::string const &requestMethod) {
                _method = requestMethod;
            };
            const std::string& getMethod(void) const {
                return _method;
            };


            void setArgument(const std::map<std::string, std::string> &argument) {
                _argument = argument;
            }
            void setArgument(const std::string &name, const std::string &value) {
                _argument.insert({name, value});
            }
            const std::string* getArgument(const std::string &name) const {
                auto it = _argument.find(name);
                if (it != _argument.end())
                    return (&it->second);
            }
            std::vector<std::string> getArgumentsKeys(void) const {
                std::vector<std::string> keys;
                for (auto const &key : _argument)
                    keys.push_back(key.first);
                return keys;
            }

            //\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

            void setHeader(const std::map<std::string, std::string> &header) {
                _header = header;
            }
            void setHeader(const std::string &key, const std::string &value) {
                _header.insert({key, value});
            }
            const std::string* getHeader(const std::string &key) const {
                auto it = _header.find(key);
                if (it != _header.end())
                    return (&it->second);
            }
            std::vector<std::string> getHeaderKeys(void) const {
                std::vector<std::string> keys;
                for (auto const &key : _header)
                    keys.push_back(key.first);
                return keys;
            }

            void setBody(std::vector<char> const &body) {
                _body = body;
            }
            const std::vector<char>* getBody(void) const {
                return (&_body);
            }

        protected:
        private:
            std::string _httpRequest;

            std::string _clientIp;
            std::string _protocol;
            std::string _filename;
            std::string _url;

            std::string _method;
            std::map<std::string, std::string> _argument;
            
            std::map<std::string, std::string> _header;
            std::vector<char> _body;
    };
}

#endif /* !REQUEST_HPP */
