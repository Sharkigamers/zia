/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** conf
*/


#pragma once

#include <optional>
#include <typeinfo>
#include "../Zia-Docs/include/zia/Zia.hpp"
#include "object.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include <boost/optional/optional.hpp>
#include <boost/algorithm/string.hpp>
#include <regex>
#include <typeinfo>
#include <memory>

#define concast  const_cast<Zia::Json::IObject&>

namespace Zia {
	class JsonConf : public Zia::IConf {

	public:
        JsonConf(const std::string& jsonPath) {
            _jsonPath = jsonPath;
        };
		~JsonConf() {};

        Zia::Json::JsonObject Object_first(boost::property_tree::ptree const& pt, std::string name, Zia::Json::JsonObject Obj) const
        {
            using boost::property_tree::ptree;
            ptree::const_iterator end = pt.end();
            for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
                 if (it->first == name) {
                     Obj.createEmptyObject(name);
                for (auto& actual_obj : it->second) {
                    if (actual_obj.first == "conf") {
                        Obj.getObject(name)->createEmptyObject("conf");
                        for (auto& actual_conf : actual_obj.second) {
                            if (actual_conf.first == "load") {
                                Obj.getObject(name)->getObject("conf")->createEmptyArray("load");
                                std::string full_n = name + '.' + "conf" + '.' + "load";
                                for (auto& actual_load : pt.get_child(full_n))
                                    Obj.getObject(name)->getObject("conf")->getArray("load")->setString(Obj.getObject(name)->getObject("conf")->getArray("load")->getSize(), actual_load.second.get_value<std::string>());
                            }
                            else
                                Obj.getObject(name)->getObject("conf")->setString(actual_conf.first, actual_conf.second.get_value<std::string>());
                        }
                    }
                    else
                        Obj.getObject(name)->setString(actual_obj.first, actual_obj.second.get_value<std::string>());
                }
                }
                Object_first(it->second, name, Obj);
        }
        return (Obj);
        }

        Zia::Json::JsonObject Array_first(boost::property_tree::ptree const& pt, std::string name, Zia::Json::JsonObject Obj) const {
            Obj.createEmptyArray(name);
            for (auto& actual_array : pt.get_child(name)) {
                Obj.getArray(name)->createEmptyObject(Obj.getArray(name)->getSize());
                for (auto& actual_obj : actual_array.second) {
                    if (actual_obj.first == "conf") {
                        Obj.getArray(name)->getObject(Obj.getArray(name)->getSize()-1)->createEmptyObject("conf");
                        for (auto& actual_conf : actual_obj.second) {
                            if (actual_conf.first == "load") {
                                 Obj.getArray(name)->getObject(Obj.getArray(name)->getSize()-1)->getObject("conf")->createEmptyArray("load");
                                 std::string full_n = name + '.' + "conf" + '.' + "load";
                                 for (auto& actual_load : actual_conf.second)
                                    Obj.getArray(name)->getObject(Obj.getArray(name)->getSize()-1)->getObject("conf")->getArray("load")->setString(Obj.getArray(name)->getObject(Obj.getArray(name)->getSize()-1)->getObject("conf")->getArray("load")->getSize(), actual_load.second.get_value<std::string>());
                            }
                            else
                                Obj.getArray(name)->getObject(Obj.getArray(name)->getSize()-1)->getObject("conf")->setString(actual_conf.first, actual_conf.second.get_value<std::string>());
                        }
                    }
                    else
                        Obj.getArray(name)->getObject(Obj.getArray(name)->getSize()-1)->setString(actual_obj.first, actual_obj.second.get_value<std::string>());
                }
            }
            return (Obj);
        }

        Zia::Json::JsonObject parse_object(boost::property_tree::ptree const& pt, Zia::Json::JsonObject Obj) const {
            using boost::property_tree::ptree;
            ptree::const_iterator end = pt.end();
            
            Obj = Zia::JsonConf::Object_first(pt, "connection_wrapper", Obj);
            Obj = Zia::JsonConf::Object_first(pt, "parser", Obj);
            Obj = Zia::JsonConf::Array_first(pt, "loggers", Obj);
            Obj = Zia::JsonConf::Array_first(pt, "handlers", Obj);
            return (Obj);
        };
            

        std::unique_ptr<Json::IObject> read(void) const final {
            Zia::Json::JsonObject Obj;
            boost::property_tree::ptree pt;
            boost::property_tree::read_json(_jsonPath, pt);
            Obj = Zia::JsonConf::parse_object(pt, Obj);
            return std::make_unique<Json::JsonObject>(Obj);
        };

        void loopSnd(boost::property_tree::ptree &child1, size_t i, std::string key, const Json::IObject &jsonObject,
        const std::string &keyObjArr)
        {
            for (auto key2 : concast(jsonObject).getArray(keyObjArr)->getObject(i)->getObject(key)->getKeys()) {
                if (key2 == "output" || key2 == "path") {
                    std::string value = concast(jsonObject).getArray(keyObjArr)->getObject(i)->getObject(key)->getString(key2).value();
                    std::string value2 = std::regex_replace(value, std::regex("/"), "\u2215");
                    child1.put(key + "." + key2, value2);
                } else if (key2 == "load") {
                    boost::property_tree::ptree children;
                    size_t counter = concast(jsonObject).getArray(keyObjArr)->getObject(i)->getObject(key)->getArray(key2)->getSize();
                    for (size_t j = 0; j != counter; j++) {
                        boost::property_tree::ptree childLoad;
                        childLoad.put("", concast(jsonObject).getArray(keyObjArr)->getObject(i)->getObject(key)->getArray(key2)->getString(j).value());
                        children.push_back(std::make_pair("", childLoad));
                    }
                    child1.add_child(key + "." +key2, children);
                }
            }
        }

        void intern_write_array(const Json::IObject &jsonObject, const std::string &keyObjArr)
        {
            size_t nbObj = concast(jsonObject).getArray(keyObjArr)->getSize();
            boost::property_tree::ptree children;
            boost::property_tree::ptree child1;

            for (size_t i = 0; i != nbObj; i++) {
                boost::property_tree::ptree childTmp;
                size_t count = 0;
                size_t inc = 1;

                for (auto s : concast(jsonObject).getArray(keyObjArr)->getObject(i)->getKeys())
                    count++;
                for (auto key : concast(jsonObject).getArray(keyObjArr)->getObject(i)->getKeys()) {
                    std::string pathstring = keyObjArr + ".";
                    if (key == "path" || key == "output") {
                        try {
                        std::string value = concast(jsonObject).getArray(keyObjArr)->getObject(i)->getString(key).value();
                        std::string value2 = std::regex_replace(value, std::regex("/"), "\u2215");
                        if (nbObj < 1)
                            child1.put(key, value2);
                        else
                            childTmp.put(key, value2);
                        } catch (const std::exception &ex) {
                            auto value = concast(jsonObject).getArray(keyObjArr)->getObject(i)->getNumber(key).value();
                        if (nbObj < 1)
                            child1.put(key, (double)value);
                        else
                            childTmp.put(key, (double)value);
                        }

                    } else if (key == "conf") {
                        if (inc == 0 && count <= 1)
                            loopSnd(child1, i, key, jsonObject, keyObjArr);
                        else
                            loopSnd(childTmp, i, key, jsonObject, keyObjArr);
                    }
                    if (inc == count && childTmp.size() > 0) {
                        children.push_back(std::make_pair("", childTmp));
                    }
                    inc++;
                }
            }
            if (child1.size() > 0)
                children.push_back(std::make_pair("", child1));
            _wpt.add_child(keyObjArr, children);
        };

        void intern_write_object(const Json::IObject &jsonObject, const std::string &keyObjArr)
        {
            for (auto key : jsonObject.getObject(keyObjArr)->getKeys()) {
                size_t count = 0;
                std::string pathstring = keyObjArr + ".";

                if (key == "path" || key == "output") {
                    try {
                    std::string value = jsonObject.getObject(keyObjArr)->getString(key).value();
                    std::string value2 = std::regex_replace(value, std::regex("/"), "\u2215");
                    _wpt.put(pathstring + key, value2);
                    } catch (const std::exception &ex) {
                        auto value = jsonObject.getObject(keyObjArr)->getNumber(key).value();
                        _wpt.put(pathstring + key, value);
                    }
                } else if (key == "conf") {
                    try {
                        for (auto key2 : jsonObject.getObject(keyObjArr)->getObject(key)->getKeys()) {
                            count++;
                            if (key2 == "output" || key2 == "path") {
                                std::string value = jsonObject.getObject(keyObjArr)->getObject(key)->getString(key2).value();        
                                std::string value2 = std::regex_replace(value, std::regex("/"), "\u2215");
                                
                                _wpt.put(pathstring + key + "." + key2, value2);
                            }
                        }
                    } catch (boost::exception &e) {
                        return;
                    }
                    if (count != 0)
                    _wpt.put(pathstring + key, "");
                }
            }
        };

        void intern_write_all(const Json::IObject &jsonObject, const std::string &keyObjArr)
        {
            try {
                auto check = concast(jsonObject).getArray(keyObjArr)->getSize();
                if (check != 0)
                    intern_write_array(jsonObject, keyObjArr);
                else
                    intern_write_object(jsonObject, keyObjArr);
            } catch (boost::exception &e) {
                intern_write_object(jsonObject, keyObjArr);
            }
        }

        void write(const Json::IObject &jsonObject) final {
            for (auto keyObjArr : jsonObject.getKeys()) {
                if (keyObjArr == "loggers" || keyObjArr == "handlers") { 
                    intern_write_array(jsonObject, keyObjArr);
                } else if (keyObjArr == "connection_wrapper" || keyObjArr == "parser") {
                    intern_write_object(jsonObject, keyObjArr);
                } else
                    intern_write_all(jsonObject, keyObjArr);
            }
            boost::property_tree::write_json(_jsonPath, _wpt);
        };
    private:
        boost::property_tree::ptree _wpt;
        std::string _jsonPath;
    };
};