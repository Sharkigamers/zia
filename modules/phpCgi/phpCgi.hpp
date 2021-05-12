/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** phpCgi
*/

#pragma once

#include <map>
#include <iostream>

#include <boost/process.hpp>
#include "../../Zia-Docs/include/zia/Zia.hpp"

namespace Zia {
    class phpCgi : public Zia::Module::IHandler {
        public:
            explicit phpCgi(Zia::IConf &conf) {

            };
            ~phpCgi() = default;

            void handle(const IRequest &req, IResponse &res, IContext &ctx, ILogger &log) final;

            std::map<std::string, std::string> buildHeadersFromVector(const std::vector<std::string> &vector) {
                std::map<std::string, std::string> res;

                for (const auto &x : vector) {
                    std::size_t pos = x.find(':');
                    if (pos != std::string::npos) {
                        const std::string headerKey = x.substr(0, pos);
                        const std::string headerValue = x.substr(pos, x.length() - 1);

                        res[headerKey] = headerValue;
                    }
                }
                return res;
            }

            std::string getExtension(const std::string &URL) const noexcept {
                std::string s = URL;
                std::string firstDelimiter = "/";
                size_t pos = 0;
                std::string token;
                std::string res;
                std::string secondDelimiter = ".";
                size_t secondPos = 0;
                std::string secondToken;
                
                while ((pos = s.find(firstDelimiter)) != std::string::npos) {
                    token = s.substr(0, pos);
                    s.erase(0, pos + firstDelimiter.length());
                }
                // s = index.html
                res = s;

                while ((secondPos = res.find(secondDelimiter)) != std::string::npos) {
                    secondToken = res.substr(0, secondPos);
                    res.erase(0, secondPos + secondDelimiter.length());
                }

                return (res);
            }

            boost::process::environment getEnv(const IRequest &req) {
                boost::process::environment env = boost::this_process::environment();
                std::string query;
                std::string uri(req.getURL());
                std::string home(getenv("HOME"));
                std::string path(getenv("PATH"));

                std::string fullPath = boost::filesystem::path(
                        boost::filesystem::canonical(boost::filesystem::current_path().native()).string() + "/" +
                        uri).lexically_normal().string();

                std::string pathInfo = fullPath.substr(0, fullPath.find_last_of('/'));

                env["DOCUMENT_ROOT"] = pathInfo;
                env["GATEWAY_INTERFACE"] = "CGI/1.1";
                env["HOME"] = home;
                env["PATH"] = path;
                env["PATH_INFO"] = pathInfo;
                env["PATH_TRANSLATED"] = pathInfo;
                env["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
                env["QUERY_STRING"] = "";
                env["REQUEST_METHOD"] = req.getMethod();
                env["SCRIPT_FILENAME"] = fullPath;
                env["SCRIPT_NAME"] = uri;
                env["SYSTEMROOT"] = "/";
                env["REDIRECT_STATUS"] = "true";
                return env;
            };
    };
}