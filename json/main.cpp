#include <iostream>
#include "object.hpp"
#include "conf.hpp"

int main(void)
{
	std::unique_ptr<Zia::Json::IObject> test;
	Zia::JsonConf conf("../config/default.json");
/*
	//test.createEmptyObject("test");

	test.createEmptyArray("loggers");
	//aa(test);
	/*if (test.getArray("loggers"))
          std::cout << "caca\n";
	test.getArray("loggers")->createEmptyObject(0);
	test.getArray("loggers")->getObject(0)->setString("path", "mod/filelogger");
	test.getArray("loggers")->getObject(0)->createEmptyObject("conf").setString("output", "./log.txt");

	test.createEmptyObject("connection_wrapper");
	test.getObject("connection_wrapper")->setString("path", "mod/ssl");

	test.createEmptyObject("parser");
	test.getObject("parser")->setString("path", "modules/Parser/Parser");
	test.getObject("parser")->createEmptyObject("conf");

	test.createEmptyArray("handlers");
	test.getArray("handlers")->createEmptyObject(0).setString("path", "mod/fileloader");
	test.getArray("handlers")->getObject(0)->createEmptyObject("conf");
	
	test.getArray("handlers")->getObject(0)->getObject("conf")->createEmptyArray("load");
	test.getArray("handlers")->getObject(0)->getObject("conf")->getArray("load")->setString(0, "txt");
	test.getArray("handlers")->getObject(0)->getObject("conf")->getArray("load")->setString(1, "html");
	test.getArray("handlers")->getObject(0)->getObject("conf")->getArray("load")->setString(2, "php");
	test.getArray("handlers")->getObject(0)->getObject("conf")->getArray("load")->setString(3, "js");
	test.getArray("handlers")->getObject(0)->getObject("conf")->getArray("load")->setString(4, "jpg");
	test.getArray("handlers")->getObject(0)->getObject("conf")->getArray("load")->setString(5, "png");
	test.getArray("handlers")->getObject(0)->getObject("conf")->getArray("load")->setString(6, "bmp");
	test.getArray("handlers")->getObject(0)->getObject("conf")->getArray("load")->setString(7, "wav");
	test.getArray("handlers")->getObject(0)->getObject("conf")->getArray("load")->setString(8, "mp3");
	test.getArray("handlers")->getObject(0)->getObject("conf")->getArray("load")->setString(9, "flac");

	test.getArray("handlers")->createEmptyObject(1).setString("path", "mod/php");
	test.getArray("handlers")->createEmptyObject(2).setString("path", "mod/jsminifyr");
	test.getArray("handlers")->createEmptyObject(3).setString("path", "modules/Get/Get");
*/
	/*for (auto keyObjArr : test.getKeys()) {
		std::cout << keyObjArr << std::endl;
		if (keyObjArr == "loggers" || keyObjArr == "handlers") { 
			std::cout << test.getArray(keyObjArr)->getSize() << "\n";
	
			//intern_write(jsonObject, keyObjArr);
		}
	}*/
	//if (test.getArray("loggers"))
      //          std::cout << "caca\n";

	test = conf.read();

	std::cout << test->getArray("handlers")->getObject(1)->getString("path").value() << std::endl;
	std::string testt = "yo";
	if(!is_number(testt))
		std::cout <<  'YY\n';
	//std::cout << test.getInteger("value").value() << std::endl;
	//std::cout << test.getString("lopes").value() << std::endl;
	//std::cout << test.getObject("test")->getInteger("issou").value() << std::endl;
	//for (size_t i = 0; i != test.getArray("loggers")->getSize(); i++) {
		//std::cout << test.getArray("loggers")->getObject(i)->getString("path").value() << std::endl;
	//	for (auto j : test.getArray("loggers")->getObject(i)->getKeys()) {
		//	std::cout << j << std::endl;
	//	}
	//}
	//std::cout << test.getArray("handlers")->getSize() << std::endl;
	//std::cout << td::cout << test.getArray(keyObjArr)->getSize() << "\n";->getString("path").value() << std::endl;
	//std::cout << test.getArray("loggers")->getObject(0)->getObject("conf")->getString("output").value() << std::endl;
	//std::cout << test.getObject("connection_wrapper")->getString("path").value() << std::endl;

	//Zia::JsonConf test;

	//test.read();

	return 0;
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}