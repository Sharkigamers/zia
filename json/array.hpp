/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** array
*/


#pragma once

#include <optional>
#include "../Zia-Docs/include/zia/Zia.hpp"
#include "object.hpp"

namespace Zia::Json {

	class JsonArray : public IArray {
	public:
		explicit JsonArray() = default;
		explicit JsonArray(std::any value) : _value(value) {
		};
		~JsonArray() {};

		void remove(size_t index) final {
			_objects.erase(_objects.begin() + index);
		}

		size_t getSize(void) const final {
            return _objects.size();
        }
		std::optional<Number> getNumber(size_t arg) const final {
			Number result = 0;

			try {
				result = std::any_cast<Number>(_objects.at(arg)->getValue());
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
				result = std::any_cast<Integer>(_objects.at(arg)->getValue());
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
				result = std::any_cast<String>(_objects.at(arg)->getValue());
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
				result = std::any_cast<Integer>(_objects.at(arg)->getValue());
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
			return _objects.at(arg).get();
		};

		const IArray* getArray(size_t arg) const final {
			return _array.get();
		};

		void setNumber(size_t arg, Number value) final {
			_objects.push_back(std::make_shared<JsonObject>(std::make_any<Number>(value)));
		};

		void setInteger(size_t arg, Integer value) final {
			_objects.push_back(std::make_shared<JsonObject>(std::make_any<Integer>(value)));
		};

		void setString(size_t arg, const String& value) final {
            _objects.push_back(std::make_shared<JsonObject>(std::make_any<String>(value)));
        };

		void setBool(size_t arg, Bool value) final {
            _objects.push_back(std::make_shared<JsonObject>(std::make_any<Bool>(value)));
        };

		IObject& createEmptyObject(size_t arg) final {
            _objects.push_back(std::make_shared<JsonObject>());
            return *_objects[arg];
        };

        IArray& createEmptyArray(size_t arg) final {
            IArray *arr;
            return *arr;
        };

	private:
		std::vector< std::shared_ptr<JsonObject> > _objects;
		std::any _value;
		std::unique_ptr<Zia::Json::JsonArray> _array;
	};
};
