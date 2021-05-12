///*
//** EPITECH PROJECT, 2021
//** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
//** File description:
//** ZiaPipeLineTask
//*/
//
//#pragma once
//
//#include <string>
//#include <memory>
//
//#include "../context/include/HttpContext.hpp"
//#include "../../Zia-Docs//include/zia/Zia.hpp"
//
//namespace Zia {
//	class ZiaClient;
//
//	class ZiaPipeLineTask {
//	public:
//		explicit ZiaPipeLineTask(std::shared_ptr<Zia::IContext>& ctx, Zia::ZiaClient &client) : _ctx(ctx), _client(client) {};
//		~ZiaPipeLineTask() = default;
//
//		std::shared_ptr<Zia::IContext>& getContext() { return _ctx; }
//		Zia::ZiaClient& getClient() { return _client; }
//
//	private:
//		std::shared_ptr<Zia::IContext>& _ctx;
//		Zia::ZiaClient &_client;
//	};
//};