/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** ZiaError
*/

#pragma once

#include <string>
#include <memory>
#include <exception>


namespace Zia::Error {
    class ParseError : public std::exception {
        public:
            ParseError(const std::string& message) : _errorMessage(message) {};
            ~ParseError() = default;

            const char* what() const throw() { return _errorMessage.c_str(); }

        private:
            std::string _errorMessage;
        };
    
    class ReadRetryError : public std::exception {
        public:
            ReadRetryError(const std::string& message) : _errorMessage(message) {};
            ~ReadRetryError() = default;

            const char* what() const throw() { return _errorMessage.c_str(); }

        private:
            std::string _errorMessage;
        };
};