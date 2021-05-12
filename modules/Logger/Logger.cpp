/*
** EPITECH PROJECT, 2021
** Logger.cpp
** File description:
** Logger
*/

#include "Logger.hpp"

Zia::Logger::Logger(Zia::IConf &conf) {
    _fileName = "./log.txt";
}

void Zia::Logger::log(const std::string &str) {
    std::ofstream myfile;
    myfile.open (_fileName);
    myfile << str << std::endl;
    myfile.close();
}

extern "C" {
    ZIA_EXPORT_SYMBOL Zia::Module::ILogger* createLogger(Zia::IConf &conf) {
        return (new Zia::Logger(conf));
    }
}
