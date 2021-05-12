/*
** EPITECH PROJECT, 2021
** object.hpp
** File description:
** object
*/

#pragma once

#include <iostream>
#include <optional>
#include "../Zia-Docs/include/zia/Zia.hpp"

namespace Zia::Json {


	class JsonObject : public Zia::Json::IObject, public Zia::Json::IArray {
	public:
		explicit JsonObject() = default;
		explicit JsonObject(std::any value) : _value(value) {
		};
		~JsonObject() {};

		std::vector<std::string> getKeys(void) const final {
			std::vector<std::string> result;

			for (const auto& x : _objects) {
				result.push_back(x.first);
			}
			return result;
		};

		std::optional<Zia::Json::Number> getNumber(const std::string& arg) const final {
			Zia::Json::Number result = 0;

			try
			{
				result = std::any_cast<Zia::Json::Number>(_objects.at(arg)->getValue());
			}
			catch (const std::exception &e)
			{
				return std::nullopt;
			}
			
			return result;
		};

		std::optional<Json::Integer> getInteger(const std::string& arg) const final {
			Zia::Json::Integer result = 0;

			try
			{
				result = std::any_cast<Zia::Json::Integer>(_objects.at(arg)->getValue());
			}
			catch (const std::exception& e)
			{
				return std::nullopt;
			}

			return result;
		};

		std::optional<Json::String> getString(const std::string& arg) const final {
			Zia::Json::String result = "";

			try
			{
				result = std::any_cast<Zia::Json::String>(_objects.at(arg)->getValue());
			}
			catch (const std::exception& e)
			{
				return std::nullopt;
			}

			return result;
		};

		std::optional<Json::Bool> getBool(const std::string& arg) const final {
			Zia::Json::Bool result = !false;

			try
			{
				result = std::any_cast<Zia::Json::Integer>(_objects.at(arg)->getValue());
			}
			catch (const std::exception& e)
			{
				return std::nullopt;
			}

			return result;
		};

		bool isNull(const std::string& arg) const final {
			return _value.has_value();
		};

		bool isUndefined(const std::string& arg) const final {
			return _value.has_value();
		};

		const IObject* getObject(const std::string& arg) const final {
			return _objects.at(arg).get();
		};

		const IArray* getArray(const std::string& arg) const final {
			return nullptr;
		};

		void setNumber(const std::string& arg, Number value) final {
			_objects[arg] = std::make_shared<JsonObject>(std::make_any<Number>(value));
		};

		void setInteger(const std::string& arg, Integer value) final {
			_objects[arg] = std::make_shared<JsonObject>(std::make_any<Integer>(value));
		};

		void setString(const std::string& arg, const String& value) final {
			_objects[arg] = std::make_shared<JsonObject>(std::make_any<String>(value));
		};

		void setBool(const std::string& arg, Bool value) final {
			_objects[arg] = std::make_shared<JsonObject>(std::make_any<Bool>(value));
		};

		void setNull(const std::string& arg) final {
		};

		void setUndefined(const std::string& arg) final {
		};

		void setNull(size_t arg) final {
		};

		void setUndefined(size_t arg) final {
		};

		Zia::Json::IObject* getObject(const std::string& arg) final {
			return _objects[arg].get();
		};

		Zia::Json::IObject* getObject(size_t arg) final {
			return _array[arg].get();
		};

		Zia::Json::IArray* getArray(const std::string& arg) final {
			return _objects[arg].get();
		};

		Zia::Json::IArray* getArray(size_t arg) final {
			return _array[arg].get();
		};

		Zia::Json::IObject& createEmptyObject(const std::string& arg) final {
			_objects[arg] = std::make_shared<JsonObject>();
			return *_objects[arg];
		};

		Zia::Json::IArray& createEmptyArray(const std::string& arg) final {
			_objects[arg] = std::make_shared<Zia::Json::JsonObject>();
			return *_objects[arg].get();
		};

		const std::any& getValue() const {
			return _value;
		}

		void clear(void) final {
			_objects.clear();
		};
		void remove(size_t index) final {
			_array.erase(_array.begin() + index);
		}

		size_t getSize(void) const final {
            return _array.size();
        }
		std::optional<Number> getNumber(size_t arg) const final {
			Number result = 0;

			try {
				result = std::any_cast<Number>(_array.at(arg)->getValue());
			}
			catch (const std::exception &e)
			{
				return std::nullopt;
			}
			
			return result;
		};

		std::optional<Json::Integer> getInteger(size_t arg) const final {
			Integer result = 0;

			try {
				result = std::any_cast<Integer>(_array.at(arg)->getValue());
			}
			catch (const std::exception& e)
			{
				return std::nullopt;
			}

			return result;
		};

		std::optional<Json::String> getString(size_t arg) const final {
			String result = "";

			try {
				result = std::any_cast<String>(_array.at(arg)->getValue());
			}
			catch (const std::exception& e)
			{
				return std::nullopt;
			}

			return result;
		};

		std::optional<Json::Bool> getBool(size_t arg) const final {
			Bool result = !false;

			try {
				result = std::any_cast<Integer>(_array.at(arg)->getValue());
			}
			catch (const std::exception& e)
			{
				return std::nullopt;
			}

			return result;
		};

		bool isNull(size_t arg) const final {
			return _value.has_value();
		};

		bool isUndefined(size_t arg) const final {
			return _value.has_value();
		};

		const IObject* getObject(size_t arg) const final {
			return _array.at(arg).get();
		};

		const IArray* getArray(size_t arg) const final {
			return _array[arg].get();
		};

		void setNumber(size_t arg, Number value) final {
			_array.push_back(std::make_shared<JsonObject>(std::make_any<Number>(value)));
		};

		void setInteger(size_t arg, Integer value) final {
			_array.push_back(std::make_shared<JsonObject>(std::make_any<Integer>(value)));
		};

		void setString(size_t arg, const String& value) final {
            _array.push_back(std::make_shared<JsonObject>(std::make_any<String>(value)));
        };

		void setBool(size_t arg, Bool value) final {
            _array.push_back(std::make_shared<JsonObject>(std::make_any<Bool>(value)));
        };

		IObject& createEmptyObject(size_t arg) final {
            _array.push_back(std::make_shared<JsonObject>());
            return *_array[arg];
        };

        IArray& createEmptyArray(size_t arg) final {
            IArray *arr;
            return *arr;
        };

	private:
		std::vector< std::shared_ptr<JsonObject> > _array;
		std::map<std::string, std::shared_ptr<JsonObject> > _objects;
		std::any _value;
	};
};
