/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** SSL
*/

#include "SSL.hpp"

Zia::SSLConnectionWrapper::SSLConnectionWrapper(Zia::IConf &conf)
{
    try
    {
        _certPath = conf.read()->getObject("connection_wrapper")->getObject("conf")->getString("certificate_path").value();
        _keyPath = conf.read()->getObject("connection_wrapper")->getObject("conf")->getString("key_path").value();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

std::unique_ptr<Zia::IConnection> Zia::SSLConnectionWrapper::create(Zia::IConnection& connection)
{
    std::unique_ptr<Zia::SSLConnection> newConnection = std::make_unique<Zia::SSLConnection>(connection, _certPath, _keyPath);

    if (newConnection->isValid()) {
        return newConnection;
    } else {
        return nullptr;
    }
}

extern "C" {
    ZIA_EXPORT_SYMBOL Zia::Module::IConnectionWrapper* createConnectionWrapper(Zia::IConf &conf) {
        return (new Zia::SSLConnectionWrapper(conf));
    }
}
