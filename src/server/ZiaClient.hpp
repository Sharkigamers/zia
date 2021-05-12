/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** Zia
*/

#pragma once

#include <string>
#include <memory>
#include <algorithm>

#include <boost/asio.hpp>
#include <thread>
#include "src/server/Network/include/TcpConnection.hpp"
#include "src/server/Logger/BasicClientOutputLogger.hpp"
#include "../../Zia-Docs//include/zia/Zia.hpp"
//#include "../common/include/ZiaPipeLineTask.hpp"
#include "../context/include/HttpContext.hpp"

namespace Zia {
	class ZiaClient;
	class ZiaPipeLineTask;
};

namespace Zia {
	class ZiaPipeLineTask {
		public:
			explicit ZiaPipeLineTask(std::shared_ptr<Zia::IContext>& ctx, Zia::ZiaClient& client, const Zia::IRequest *req) : _ctx(ctx), _client(client), _request(req) {};
			~ZiaPipeLineTask() = default;

			std::shared_ptr<Zia::IContext> getContext() {
				return _ctx; 
			}
			Zia::ZiaClient& getClient() { return _client; }
			const Zia::IRequest* getRequest() { return _request; }

		private:
			std::shared_ptr<Zia::IContext> _ctx;
			Zia::ZiaClient& _client;
			const Zia::IRequest* _request;
	};

	class ZiaClient : public Zia::IRequest::IEmitter {
		public:
			explicit ZiaClient(std::unique_ptr<Zia::IConnection> &connection) : _connection(std::move(connection)), _clientLogger(std::make_unique<Zia::Logger::BasicClientOutputLogger>()) {
				_id = std::rand();
			};

			~ZiaClient() = default;

			bool isActive() const { return _active; }
			void setActive(bool newStatus) { _active = newStatus; }
			int getId() const { return _id;  }
			bool operator==(const int other) { return other == _id; }
			bool operator==(const ZiaClient& other) { return other.getId() == _id; }
			bool operator==(const std::shared_ptr<ZiaClient> &other) { return other->getId() == _id; }

			std::unique_ptr<Zia::IConnection>& getConnection() { return _connection; }

		private:
			std::array<char, 4096> _clientBuffer;

		public:
			/*bool hasIncomingMessage() const {
				return _connection->getSocket()->available() != 0;
			};

			void startRead() {
				_connection->getSocket()->async_read_some(boost::asio::buffer(_clientBuffer, 4096), [this](boost::system::error_code ec, std::size_t read) {
					if (!ec) {
						std::string clientMessage(_clientBuffer.data(), read);
						_clientLogger->log(clientMessage);
						std::string message = "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><h2>Bigga lopes Server</h2><div>200 lopes</div></body></html>";
						std::string sample = "HTTP/1.1 200\r\nServer: Bigga lopes\r\nContent-Length: " + std::to_string(message.length()) + "\r\nConnection: close\r\nContent-Type: text/html\r\n\r\n";
						_connection->getSocket()->write_some(boost::asio::buffer(sample));
						_connection->getSocket()->write_some(boost::asio::buffer(message));
						startRead();
					}
					else {
						_clientLogger->log(ec.message());
						_active = false;
					}
				});*/
			//}
			void write(const std::string &str) {
				_connection->write(str.size(), str.c_str());
			};

			void write(const std::vector<char> *str) {
				_connection->write(str->size(), str->data());
			};

			void emit(const Zia::IRequest& request) final {
				std::shared_ptr<Zia::IContext> ctx = std::make_shared<Zia::Context::HttpContext>();
				ctx->set("STOP", std::make_any<bool>(false));

				_lstTasks.push_back(std::make_shared<ZiaPipeLineTask>(ctx, *this, &request));
			}

			bool hasNewMessage() const { return !_lstTasks.empty(); }

			std::shared_ptr<ZiaPipeLineTask> getLastTask() {
				std::shared_ptr<ZiaPipeLineTask> task = _lstTasks.front();

				_lstTasks.erase(_lstTasks.begin());
				return task;
			};

		private:
			std::unique_ptr<Zia::IConnection> _connection;
			bool _active = true;
			std::unique_ptr<Zia::ILogger> _clientLogger;
			int _id;
			std::vector<std::shared_ptr<ZiaPipeLineTask> > _lstTasks;
	};
}