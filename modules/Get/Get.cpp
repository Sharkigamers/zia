/*
** EPITECH PROJECT, 2021
** Get
** File description:
** Get
*/

#include "Get.hpp"

Zia::Get::Get(Zia::IConf &conf) {
}

void Zia::Get::handle(const IRequest &req, IResponse &res, IContext &ctx, ILogger &log) {
    std::string url = req.getURL();
    std::string contentType;

    if (url == "/")
        url = "./html/index.html";
    else 
        url = "." + url;
    contentType = getMimeType(getExtension(url));

    if (contentType != EXTENSION_ERR && contentType != "text/plain" && contentType != PHPFILE) {
        if(contentType == "image/jpeg" || contentType == "image/png" || contentType == "image/gif") {
            openImg(url, log, res);
        } else {
            res.setHeader("Content-Type", contentType);
            openFile(url, log, res);
        }
    } else if (contentType == PHPFILE) {
        return;
    } else {
        res.setHeader("Content-Type", "text/html");
        fileError(url, log, res);
    }
}

std::string Zia::Get::getExtension(const std::string &URL) const noexcept {
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

void Zia::Get::openFile(const std::string &URL, ILogger &log, IResponse &res) const noexcept { 
    std::vector<char> charvect;
    std::ifstream file(URL);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            line += "\r\n";
            charvect.insert(charvect.end(), line.begin(), line.end());
        }
        file.close();
        res.setBody(charvect);
        res.setCode(200);
    } else {
        fileError(URL, log, res);
    }
}

void Zia::Get::fileError(const std::string &URL, ILogger &log, IResponse &res) const noexcept {
    std::vector<char> charvect;
    std::string errorFile = "<!DOCTYPE html>\r\n<html lang=\"fr\">\r\n<head>\r\n<meta charset=\"UTF-8\">\r\n<title></title>\r\n<meta name=\"description\">\r\n</head>\r\n<body>\r\n<h1>404</h1>\r\n<p>Page Not Found</p>\r\n</body>\r\n</html>";
    charvect.insert(charvect.end(), errorFile.begin(), errorFile.end());
    res.setBody(charvect);
    res.setCode(404);
}
void Zia::Get::openImg(const std::string &URL, ILogger &log, IResponse &res) const noexcept { 
        std::ifstream file(URL);
        std::vector<char> charvect;
        if (file.is_open()) {
            std::string rawData((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
            using namespace boost::archive::iterators;
            using It = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
            auto tmp = "\r\n" + std::string(It(std::begin(rawData)), It(std::end(rawData)));
            tmp.append((3 - rawData.size() % 3) % 3, '=');
            tmp += "\r\n";
            charvect.insert(charvect.end(), rawData.begin(), rawData.end());
            res.setBody(charvect);
            res.setCode(200);
            res.setHeader("content-length", std::to_string(rawData.length()));
        }
}

extern "C" {
    ZIA_EXPORT_SYMBOL Zia::Module::IHandler* createHandler(Zia::IConf &conf) {
        return (new Zia::Get(conf));
    }
}
