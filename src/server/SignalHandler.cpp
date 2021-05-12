/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SignalHandler
*/

#include "SignalHandler.hpp"

bool Zia::SignalHandler::_hasExited = false;

Zia::SignalHandler::SignalHandler()
{
    std::signal(SIGINT, handler);
}

Zia::SignalHandler::~SignalHandler()
{
}
