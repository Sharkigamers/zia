/*
** EPITECH PROJECT, 2021
** Response.hpp
** File description:
** Response
*/

#ifndef RESPONSE_HPP_
#define RESPONSE_HPP_
#include "../../../Zia-Docs/include/zia/Zia.hpp"
#include <map>

enum RFC {
    CONTINUE = 100,
    OK = 200,
    MOVED = 301,
    FOUND = 302,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,    
    NOT_FOUND = 404,
    SERVER_ERROR = 500,
    UNAVAILABLE = 503,
    TIME_OUT = 504,
};

namespace Zia::Response {
   class Response : public Zia::IResponse {
        public:
            explicit Response(void) = default;
            ~Response() = default;

            void setCode(size_t code) final {
                _code = code;
            }
            
            size_t getCode(void) const final {
                return _code;
            };

            void setHeader(const std::string &key, const std::string &value) final {
                _header[key] = value;
            }

            void setBody(const std::vector<char> &body) final  {
                _body = body;
            }

            std::map<std::string, std::string> getMapHeader() {
                return _header;
            };

            const std::string *getHeader(const std::string &key) const final {
                std::map<std::string, std::string>::const_iterator it = _header.find(key);
                if (it != _header.end())
                    return (&it->second);
                return nullptr;
            }

            const std::vector<char> *getBody() const final {
                return (&_body);
            }

            void abortPipeline(void) final {
                _stop = true;
            };

            bool mustStopPipeline() const noexcept {
                return _stop;
            }

            std::string getHeaderToWrite() const
            {
                std::string header = "";

                header = "HTTP/1.1 " + std::to_string(_code) + "\r\n";
                header += "Server: ZiaServer\r\nConnection: close\r\n";
                for (auto &x : _header) {
                    header += x.first + ": " + x.second + "\r\n";
                }
                header += "\r\n";
                return header;
            }

            void setErrorResponse() {
                _code = RFC::SERVER_ERROR;
                const std::string errorMessage = "<!DOCTYPE html>\r\n<html lang=\"fr\">\r\n<head>\r\n<meta charset=\"UTF-8\">\r\n<title></title>\r\n<meta name=\"description\">\r\n</head>\r\n<body>\r\n<h1>500</h1>\r\n<p>Internal server error: No module could handle the request</p>\r\n</body>\r\n</html>";

                _body.insert(_body.end(), errorMessage.begin(), errorMessage.end());
                setHeader("content-length", std::to_string(_body.size()));
            }

        protected:
        private:
            size_t _code;
            bool _stop = false;
            std::map<std::string, std::string> _header;
            std::vector<char> _body;
    };
}
#endif /* !RESPONSE_HPP_ */
