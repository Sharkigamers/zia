/*
** EPITECH PROJECT, 2021
** Logger.hpp
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "../../Zia-Docs/include/zia/Zia.hpp"
#include <iostream>
#include <fstream>

namespace Zia {
    class Logger : public Zia::Module::ILogger {
        public:
            Logger(Zia::IConf &conf);
            ~Logger() = default;

            void log(const std::string &str);
        protected:
        private:
            std::string _fileName;

    };
}

#endif /* !LOGGER_HPP_ */