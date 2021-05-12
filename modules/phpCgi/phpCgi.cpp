/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** phpCgi
*/

#include "phpCgi.hpp"

void Zia::phpCgi::handle(const IRequest &req, IResponse &res, IContext &ctx, ILogger &log) {
    log.log(req.getFilename());
    if (getExtension(req.getURL()) != "php") {
        return;
    }
    
    boost::process::environment env = getEnv(req);
    const std::string path = "/usr/bin/php-cgi";
    std::string responseBody = "";
    boost::process::ipstream out;
    boost::process::opstream in;
    in.flush();
    boost::process::child c(path, boost::process::std_in = in, boost::process::std_out > out, env);
    in.pipe().close();

    std::vector<char> data;
    std::vector<std::string> phpHeaders;
    std::string line;
    bool isHeader = true;
    int x = 0;
    while (c.running() && std::getline(out, line)) {
        if (line[0] == '\r') {
            isHeader = false;
        }
        if (isHeader) {
            phpHeaders.push_back(line);
        } else {
            responseBody += line;
            data.insert(data.end(), line.begin(), line.end());
        }
    }
    c.wait();
    log.log("PhpCGI exited with code: " + std::to_string(c.exit_code()));
    if (c.exit_code() == 0) {
        res.setHeader("Content-length", std::to_string(responseBody.length()));
        for (const auto &x : buildHeadersFromVector(phpHeaders)) {
            res.setHeader(x.first, x.second);
        }
        res.setBody(data);
        res.abortPipeline();
    }
}

extern "C" {
    ZIA_EXPORT_SYMBOL Zia::Module::IHandler* createHandler(Zia::IConf &conf) {
        return (new Zia::phpCgi(conf));
    }
}