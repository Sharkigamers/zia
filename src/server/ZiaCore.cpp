/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** Zia
*/

#include "ZiaCore.hpp"

bool ctrlc = false;

Zia::ZiaCore::ZiaCore(const std::string& configPath)
	: _configFile(std::make_unique<zia::common::Configuration>()), _ctx(), _logger(std::make_unique<Zia::Logger::BasicOutputLogger>()), _parser(nullptr), _connectionWrapper(nullptr), _sign()
	, _jsonConf(configPath)
{
	boost::asio::ip::tcp::endpoint serverEndpoint(boost::asio::ip::tcp::v4(), 8080); // Port en dur pour l'instant
	_configFile->openConfigFile(configPath);
	_acceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(_ctx, serverEndpoint);
	_clientsWatcher = std::make_unique<std::thread>([this]() {
		runLoopClient();
	});
	_pipelineHandler = std::make_unique<std::thread>([this]() {
		runPipeline();
	});
	_confFileChecker = std::make_unique<std::thread>([this, configPath]() {
		updateConf(configPath);
	});

	try
	{
		loadModules();
	}
	catch(const std::exception& e)
	{
		throw e;
	}
	
}

Zia::ZiaCore::~ZiaCore()
{
	_running = false;
	_clientsWatcher->join();
	_pipelineHandler->join();
	_confFileChecker->join();

	if (_parser != nullptr) {
		delete _parser;
	}
	if (_connectionWrapper != nullptr) {
		delete _connectionWrapper;
	}
	for (auto &x : _lstHandlers) {
		delete x;
	}

	for (auto &x : _lstLoggers) {
		delete x;
	}
	_libs.clear();
}

void Zia::ZiaCore::updateConf(const std::string &filePath) 
{
	std::filesystem::file_time_type ftime;
	std::filesystem::path p = filePath;
	ftime = std::filesystem::last_write_time(p);

	while(_running) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::filesystem::path p = filePath;
		if (std::filesystem::last_write_time(p) != ftime) {
			_configFile->openConfigFile(filePath);
			loadModules();
			ftime = std::filesystem::last_write_time(p);
		}
		if (_sign.hasExited()) {
			_running = false;
			_ctx.stop();
		}
	}
}

void Zia::ZiaCore::loadConnectionWrapper(const std::string& path)
{
	std::shared_ptr<Zia::loader::Loader> libLoader = std::make_shared<Zia::loader::Loader>(path);

	Zia::Module::IConnectionWrapper* (*sym)(Zia::IConf&) = (Zia::Module::IConnectionWrapper * (*)(Zia::IConf&))libLoader->loadLib("createConnectionWrapper");

	if (sym != nullptr) {
		_connectionWrapper = sym(_jsonConf);
		_connectionWrapperEnabled = true;
		_libs.push_back(std::make_pair("connectionWrapper", libLoader));
	}
}

void Zia::ZiaCore::loadLoggers(const std::string &path)
{
	std::shared_ptr<Zia::loader::Loader> libLoader = std::make_shared<Zia::loader::Loader>(path);

	Zia::Module::ILogger* (*sym)(Zia::IConf&) = (Zia::Module::ILogger * (*)(Zia::IConf&))libLoader->loadLib("createLogger");

	if (sym != nullptr) {
		_lstLoggers.push_back(sym(_jsonConf));
		_libs.push_back(std::make_pair("logger", libLoader));
	}
}

void Zia::ZiaCore::loadParser(const std::string& path)
{
	std::shared_ptr<Zia::loader::Loader> libLoader = std::make_shared<Zia::loader::Loader>(path);

	Zia::Module::IParser* (*sym)(Zia::IConf&) = (Zia::Module::IParser * (*)(Zia::IConf&))libLoader->loadLib("createParser");

	if (sym != nullptr) {
		_parser = sym(_jsonConf);
		_libs.push_back(std::make_pair("parser", libLoader));
	}
}

void Zia::ZiaCore::openHandler(const std::string& path)
{
	try
	{
		std::shared_ptr<Zia::loader::Loader> libLoader = std::make_shared<Zia::loader::Loader>(path);
		Zia::Module::IHandler* (*sym)(Zia::IConf&) = (Zia::Module::IHandler * (*)(Zia::IConf&))libLoader->loadLib("createHandler");

		if (sym != nullptr) {
			_lstHandlers.push_back(sym(_jsonConf));
			_libs.push_back(std::make_pair("handler", libLoader));
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void Zia::ZiaCore::loadModules()
{
	_libs.clear();
	_lstHandlers.clear();
	_lstLoggers.clear();

	for (auto &x : _lstLoggers) {
		x->log("Loading modules");
	}

	try
	{
		auto connectionWrapperIterator = _configFile->getFileContent().get_child("connection_wrapper");
	
		for (auto it = connectionWrapperIterator.begin(); it != connectionWrapperIterator.end(); it++)
		{
			if (it->first == "path") {
				_logger->log("Opening: " + it->second.data());
				loadConnectionWrapper(it->second.data());
			}
		}
	}
	catch(const std::exception& e)
	{
		for (auto &x: _lstLoggers) {
			x->log(e.what());
		}
	}

	try
	{
		auto parserIterator = _configFile->getFileContent().get_child("parser");

		for (auto it = parserIterator.begin(); it != parserIterator.end(); it++)
		{
			if (it->first == "path") {
				_logger->log("Opening: " + it->second.data());
				loadParser(it->second.data());
			}
		}
	}
	catch(const std::exception& e)
	{
		for (auto &x: _lstLoggers) {
			x->log(e.what());
		}
	}

	try
	{
		auto handlersIterators = _configFile->getFileContent().get_child("handlers");

		for (auto it = handlersIterators.begin(); it != handlersIterators.end(); it++)
		{
			for (auto it3 = it->second.begin(); it3 != it->second.end(); ++it3)
			{
				if (it3->first == "path") {
					_logger->log("Opening: " + it3->second.data());
					openHandler(it3->second.data());
				}
			}
		}

	}
	catch(const std::exception& e)
	{
		for (auto &x: _lstLoggers) {
			x->log(e.what());
		}
	}
	
	try
	{
		auto loggersIterator = _configFile->getFileContent().get_child("loggers");

		for (auto it = loggersIterator.begin(); it != loggersIterator.end(); it++)
		{
			for (auto it3 = it->second.begin(); it3 != it->second.end(); ++it3)
			{
				if (it3->first == "path") {
					_logger->log("Opening: " + it3->second.data());
					loadLoggers(it3->second.data());
				}
			}
		}
	}
	catch(const std::exception& e)
	{
		for (auto &x: _lstLoggers) {
			x->log(e.what());
		}
	}
}

int Zia::ZiaCore::run()
{
	acceptConnection();
	for (auto &x: _lstLoggers) {
		x->log("Starting server");
	}
	_ctx.run();
	return 0;
}

void Zia::ZiaCore::runLoopClient()
{
	while (_running) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		try
		{
			_globalMutex.lock();
			for (auto& x : _clients) {
				if (!x->isActive()) {
					_logger->log("Deleting client : " + std::to_string(x->getId()));
					_clients.erase(std::find(_clients.begin(), _clients.end(), x));
					break;
				} else if (x->hasNewMessage()) {
					_lstTasks.push_back(x->getLastTask());
				}
				else {
					if (_parser != nullptr) {
						_logger->log("Creating parser instance");
						std::unique_ptr<Zia::Module::IParser::IInstance> parserInstance = _parser->create(*x->getConnection(), *_logger, *x);
						if (parserInstance != nullptr) {
							try
							{
								parserInstance->parse();
							}
							catch (const std::exception &ex)
							{
								_logger->log(ex.what());
								x->setActive(false);
								break;
							}
						}
					}
				}
			}
			_globalMutex.unlock();
		}
		catch (const std::exception &e)
		{
			_logger->log(e.what());
		}
	}
}

void Zia::ZiaCore::handleTask(Zia::ZiaPipeLineTask& task)
{
	const Zia::IRequest* request = task.getRequest();
	std::unique_ptr<Zia::Response::Response> response = std::make_unique<Zia::Response::Response>();

	for (const auto& handler : _lstHandlers) {
		handler->handle(*request, *response, *(task.getContext()), *_logger);
		if (*std::any_cast<bool>(task.getContext()->get("STOP")) == true || response->mustStopPipeline())
			break;
	}

	if (response->getBody()->data() == nullptr) {
		response->setErrorResponse();
	}

	std::string header = response->getHeaderToWrite();
	task.getClient().write(header);
	task.getClient().write(response->getBody());
}

void Zia::ZiaCore::runPipeline()
{
	while (_running) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		_globalMutex.lock();

		if (!_lstTasks.empty()) {
			for (auto &x : _lstTasks) {
				handleTask(*x);
			}
		}
		_lstTasks.clear();
		_globalMutex.unlock();
	}
}

std::unique_ptr<Zia::IConnection> Zia::ZiaCore::createConnection(std::unique_ptr<Zia::IConnection>& base)
{
	if (_connectionWrapperEnabled == true) {
		std::unique_ptr<Zia::IConnection> newConnection =  _connectionWrapper->create(*base);
		if (newConnection == nullptr) {
			return std::move(base);
		} else {
			return newConnection;
		}
	}
	else {
		return std::move(base);
	}
}

void Zia::ZiaCore::acceptConnection()
{
	Zia::Network::TcpConnection *newConnection = new Zia::Network::TcpConnection(_ctx);

	_acceptor->async_accept(*newConnection->getSocket(),
		std::bind(&Zia::ZiaCore::handleNewConnection, this,
			std::placeholders::_1,
			newConnection
		)
	);
}

void Zia::ZiaCore::handleNewConnection(const boost::system::error_code& error, Zia::Network::TcpConnection *newConnection)
{
	if (!error)
	{
		std::unique_ptr<Zia::IConnection> connection;

		newConnection->setNonBlocking(true);

		if (_connectionWrapperEnabled == true) {
			connection = _connectionWrapper->create(*newConnection);
			if (connection == nullptr)
				connection = std::unique_ptr<Zia::IConnection>(std::move(newConnection));
		}
		else {
			connection = std::unique_ptr<Zia::IConnection>(std::move(newConnection));
		}
		_logger->log("Connection from: " + newConnection->getSocket()->remote_endpoint().address().to_string());

		_globalMutex.lock();

		if (_connectionWrapperEnabled == true) {
			_clients.push_back(std::make_shared<Zia::ZiaClient>(connection));
		}
		else {
			_clients.push_back(std::make_shared<Zia::ZiaClient>(connection));
		}
		_globalMutex.unlock();

		//_clients.back()->startRead();
		this->acceptConnection();
	}
	else {
		std::cerr << "Connection denied" << std::endl;
	}
}