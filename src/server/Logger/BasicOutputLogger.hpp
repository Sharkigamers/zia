/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** TcpSocket
*/

#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <iostream>

#include "../../../../Zia-Docs/include/zia/Zia.hpp"

namespace Zia {
	namespace Logger {
		class BasicOutputLogger : public Zia::ILogger {
			public:
				BasicOutputLogger() = default;
				~BasicOutputLogger() = default;

				void log(const std::string& str) final { std::cout << "[BASIC LOGGER]: " << str << std::endl; }
		};
	}
}