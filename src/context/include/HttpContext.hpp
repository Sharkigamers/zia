/*
** EPITECH PROJECT, 2021
** HttpContext
** File description:
** HttpContext
*/

#pragma once

#include "../../../Zia-Docs/include/zia/Zia.hpp"

namespace Zia::Context {
    class HttpContext : public Zia::IContext {
    public:
        explicit HttpContext() = default;
        ~HttpContext() = default;

        const std::any* get(const std::string& key) const final {
            return &(_values.at(key));
        };

        void set(const std::string& key, const std::any& value) final {
            _values[key] = value;
        };
    private:
        std::map<std::string, std::any> _values;
    
    };
}

