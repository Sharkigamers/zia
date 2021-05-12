/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** Parser
*/

#include "Parser.hpp"

Zia::Parser::Parser(Zia::IConf &conf)
: _conf(conf)
{
}

std::unique_ptr<Zia::Module::IParser::IInstance> Zia::Parser::create(IInput &input, ILogger &log, IRequest::IEmitter &requestEmitter)
{   
    return std::make_unique<Zia::Parser::Instance>(input, log, requestEmitter);
}

extern "C" {
    ZIA_EXPORT_SYMBOL Zia::Module::IParser* createParser(Zia::IConf &conf) {
        return (new Zia::Parser(conf));
    }
}

Zia::Parser::Instance::Instance(IInput &input, ILogger &log, IRequest::IEmitter &requestEmitter)
: _input(input), _log(log), _requestEmitter(requestEmitter)
{
    _request = new Request();
}

void Zia::Parser::Instance::parse()
{
    std::array<char, buff_size> buff;
    size_t readBytes;

    try
    {
        readBytes = _input.read(buff_size, buff.data());
    }
    catch (const std::exception &ex)
    {
        throw ex;
    }

    _log.log("Read request of size : " + std::to_string(readBytes));

    std::string http_request(buff.data(), readBytes);
    _request->setRequestHttp(http_request);

    parseClientIp();
    parseFilename();
    parseProtocol();
    parseUrl();
    parseMethod();
    parseArgument();
    parseHeader();
    parseBody();

    if (_request->getURL() != "")
        _requestEmitter.emit(*_request);
}

void Zia::Parser::Instance::parseClientIp()
{
    size_t hostFlagIndex = _request->getRequestHttp().find(hostFlag);
    if (_request->getRequestHttp() == "" || hostFlagIndex == -1)
        _request->setClientIP("");
    else {
        std::string hostStart = _request->getRequestHttp().substr(hostFlagIndex + hostFlag.length());
        size_t hostEnd = hostStart.find("\n");
        if (hostEnd == -1)
            hostEnd = hostStart.length() - 1;
        std::string ip = hostStart.substr(0, hostEnd);
        size_t port = ip.find(":");
        if (port == -1)
            _request->setClientIP(ip);
        else
            _request->setClientIP(ip.substr(0, port));
    }
}
void Zia::Parser::Instance::parseFilename()
{
    size_t filenameIndex = _request->getRequestHttp().find(filenameFlag);
    if (_request->getRequestHttp() == "" || filenameIndex == -1)
        _request->setFilename("");
    else {
        std::string filename_start = _request->getRequestHttp().substr(filenameIndex + filenameFlag.length());
        size_t filenameEnd = filename_start.find("\n");
        if (filenameEnd == -1)
            filenameEnd = filename_start.length() - 1;
        std::string filename = filename_start.substr(0, filenameEnd);
        if (filename.find("'") != -1 || filename.find("\"") != -1)
            filename = filename.substr(1, filename.length() - 2);
         _request->setClientIP(filename);
    }
}
void Zia::Parser::Instance::parseProtocol()
{
    if (_request->getRequestHttp() != "") {
        size_t endFirstLine = _request->getRequestHttp().find("\n");
        if (endFirstLine == -1)
            endFirstLine = _request->getRequestHttp().length() - 1;
        std::string first_line = _request->getRequestHttp().substr(0, endFirstLine);
        for (const std::string &protocol : httpProtocol)
            if (_request->getRequestHttp().find(protocol) != -1) {
                _request->setProtocol(protocol);
                return;
            }
    }
    _request->setProtocol("");
}
void Zia::Parser::Instance::parseUrl()
{
    if (_request->getRequestHttp() != "") {
        size_t endFirstLine = _request->getRequestHttp().find("\n");
        if (endFirstLine == -1)
            endFirstLine = _request->getRequestHttp().length() - 1;
        std::string first_line = _request->getRequestHttp().substr(0, endFirstLine);
        size_t methodFlagSeparatorIndex = first_line.find(" ");
        if (methodFlagSeparatorIndex != -1) {
            std::string first_line_without_method = first_line.substr(methodFlagSeparatorIndex + 1);
            size_t endUrlIndex = first_line_without_method.find(" ");
            if (endUrlIndex != -1) {
                _request->setUrl(first_line_without_method.substr(0, endUrlIndex));
                return;
            }
        }
    }
    _request->setUrl("");
}

void Zia::Parser::Instance::parseMethod()
{
    if (_request->getRequestHttp() != "") {
        size_t endFirstLine = _request->getRequestHttp().find("\n");
        if (endFirstLine == -1)
            endFirstLine = _request->getRequestHttp().length() - 1;
        std::string first_line = _request->getRequestHttp().substr(0, endFirstLine);
        for (const std::string &method : httpMethod)
            if (_request->getRequestHttp().find(method) != -1) {
                _request->setMethod(method);
                return;
            }
    }
    _request->setMethod("");
}
void Zia::Parser::Instance::argumentParseKeyValue(std::string &arguments) {
    size_t delimiterkeyValue;

    while ((delimiterkeyValue = arguments.find("=")) != -1) {
        std::string key = arguments.substr(0, delimiterkeyValue);
        size_t delimiterOtherKeyvalue = arguments.find("&");
        if (delimiterOtherKeyvalue == -1)
            delimiterOtherKeyvalue = arguments.length();
        std::string value = arguments.substr(delimiterkeyValue + 1, delimiterOtherKeyvalue - key.length() - 1);
        _request->setArgument(key, value);
        if (arguments.find("&") != -1)
            arguments = arguments.substr(delimiterOtherKeyvalue + 1);
        else
            break;
    }
}
void Zia::Parser::Instance::parseArgument()
{
    std::string url = _request->getURL();
    if (url != "") {
        size_t argumentIndex = url.find("?");
        if (argumentIndex != -1) {
            std::string arguments = url.substr(argumentIndex + 1);
            size_t delimiterkeyValue = arguments.find("=");
            if (delimiterkeyValue != -1) {
                argumentParseKeyValue(arguments);
                return;
            }
        }
    }
    _request->setArgument(std::map<std::string, std::string>());
}

bool Zia::Parser::Instance::headerParseKeyValue(std::string &header)
{
    bool endHeader = false;

    while (!endHeader) {
        if (header.compare("") == 0)
            break;

        size_t indexSeparator = header.find(headerSeparator);
        if (indexSeparator == -1)
            break;
        
        std::string key = header.substr(0, indexSeparator);
        size_t indexNewLine = header.find("\n");
        if (indexNewLine == -1) {
            endHeader = true;
            indexNewLine = header.length() - 1;
        }
        _request->setHeader(
            key,
            header.substr(indexSeparator + headerSeparator.length(), indexNewLine - key.length() - headerSeparator.length())
        );
        header = header.substr(indexNewLine + 1);
    }
    return endHeader;
}

void Zia::Parser::Instance::parseHeader()
{
    if (_request->getRequestHttp() != "") {
        size_t endFirstLineIndex = _request->getRequestHttp().find("\n");
        if (endFirstLineIndex != -1) {
            std::string requestWithoutFirstLine = _request->getRequestHttp().substr(endFirstLineIndex + 1);
            size_t bodyIndex = requestWithoutFirstLine.find("\n\n");
            if (bodyIndex == -1)
                bodyIndex = requestWithoutFirstLine.length() - 1;
            std::string requestHeader = requestWithoutFirstLine.substr(0, bodyIndex);
            if (headerParseKeyValue(requestHeader))
                return;
        }
    }
    _request->setHeader(std::map<std::string, std::string>());
}
void Zia::Parser::Instance::parseBody()
{
    if (_request->getRequestHttp() != "") {
        size_t bodyIndex = _request->getRequestHttp().find("\n\n");
        if (bodyIndex != -1) {
            std::string body = _request->getRequestHttp().substr(bodyIndex + 2);
            _request->setBody(std::vector<char>(body.begin(), body.end()));
            return;
        }
    }
    _request->setBody(std::vector<char>());
}
