/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "../../Zia-Docs/include/zia/Zia.hpp"
#include "Request.hpp"

#include <iostream>
#include <regex>
#include <array>

namespace Zia {

    static const int buff_size = 2048;

    static const std::string hostFlag = "Host: ";
    static const std::string filenameFlag = "filename=";

    static const std::string headerSeparator = ": ";

    static const std::array<std::string, 3> httpProtocol = {
        "HTTP/1.0",
        "HTTP/1.1",
        "HTTP/2.0"
    };

    static const std::array<std::string, 9> httpMethod = {
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

    class Parser : public Zia::Module::IParser {

        class Instance : public Zia::Module::IParser::IInstance {
            public:
                Instance(IInput &input, ILogger &log, IRequest::IEmitter &requestEmitter);
                ~Instance() {
                };

                void parse(void) final;

                void parseClientIp();
                void parseFilename();
                void parseProtocol();
                void parseUrl();

                void parseMethod();
                void argumentParseKeyValue(std::string &arguments);
                void parseArgument();

                bool headerParseKeyValue(std::string &header);
                void parseHeader();
                void parseBody();

            protected:
            private:
                IInput &_input;
                ILogger &_log;
                IRequest::IEmitter &_requestEmitter;

                Request *_request;
        };

        public:
            Parser() = delete;
            explicit Parser(Zia::IConf &conf);
            ~Parser() = default;

            std::unique_ptr<IInstance> create(IInput &input, ILogger &log, IRequest::IEmitter &requestEmitter) final;

        protected:
        private:
            Zia::IConf &_conf;

            std::unique_ptr<IInstance> _instance;
    };
}

#endif /* !PARSER_HPP_ */
