/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** Zia
*/

#pragma once

#include <string>
#include <memory>
#include <thread>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <filesystem>

#include <boost/asio.hpp>

#include "ZiaClient.hpp"
#include "../library_loader/include/Loader.hpp"
#include "../context/include/HttpContext.hpp"
#include "src/server/Logger/BasicOutputLogger.hpp"
#include "../../Zia-Docs//include/zia/Zia.hpp"
#include "../common/include/Configuration.hpp"
#include "../common/include/ZiaError.hpp"
#include "../response/include/Response.hpp"
#include "SignalHandler.hpp"
#include "json/conf.hpp"


namespace Zia {
	class ZiaCore
	{
		public:
			ZiaCore(const std::string &);
			~ZiaCore();

			int run();

		private:
			std::unique_ptr<zia::common::Configuration> _configFile;
			boost::asio::io_context _ctx;
			std::shared_ptr<boost::asio::ip::tcp::acceptor> _acceptor;
			std::unique_ptr<Zia::ILogger> _logger;
			std::vector<std::shared_ptr<Zia::ZiaClient> > _clients;
			
			void loadParser(const std::string& path);
			Zia::Module::IParser *_parser;
			
			void loadModules();
		private:
			std::unique_ptr<std::thread> _clientsWatcher;

			bool _connectionWrapperEnabled = false;
			Zia::Module::IConnectionWrapper* _connectionWrapper;
			void loadConnectionWrapper(const std::string& path);

			std::vector<Zia::Module::IHandler*> _lstHandlers;
			std::vector<Zia::Module::ILogger*> _lstLoggers;
			void loadLoggers(const std::string &path);
			
			void openHandler(const std::string& path);

			void runLoopClient();
			void runPipeline();
			void acceptConnection();
			void handleNewConnection(const boost::system::error_code& error, Zia::Network::TcpConnection* newConnection);
			bool _running = true;

			std::unique_ptr<Zia::IConnection> createConnection(std::unique_ptr<Zia::IConnection> &base);

			void updateConf(const std::string &);
			void check_signal(void);
		private:
			void handleTask(ZiaPipeLineTask &task);

			std::unique_ptr<std::thread> _pipelineHandler;
			std::unique_ptr<std::thread> _confFileChecker;
			std::vector<std::shared_ptr<ZiaPipeLineTask> > _lstTasks;
			std::vector<std::pair<std::string, std::shared_ptr<Zia::loader::Loader> > > _libs;
			std::mutex _globalMutex;
			Zia::SignalHandler _sign;
			Zia::JsonConf _jsonConf;
	};
}