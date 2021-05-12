/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** Configuration
*/

#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <../Zia-Docs/include/zia/Zia.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <map>
#include <vector>

namespace zia::common {

    /* Error for Configuration class */

    inline static const std::string UNFOUND_FILE(std::string const &path) { return "Unfound file located at the path: '" + path + "'"; };
    inline static const std::string UNFOUND_MAGICKEY(std::string const &path) { return "Magic key not found in folder located at the path: '" + path + "'"; };
    inline static const std::string UNMAPPABLE_DATA() { return "Unmappable config file"; };

    class ConfigurationError : public std::exception {

        public:
            ConfigurationError(const std::string &message) : _errorMessage(message) {};
            ~ConfigurationError() = default;

            const char *what() const throw() { return _errorMessage.c_str(); }

        private:
            std::string _errorMessage;
    };

    /* Configuration Class */

    // Magic key
    static const std::string MAGIC_KEY = "666LOPES666";

    // Default file configuration
    static const std::string DEFAULT_CONFIG_FILE = "./config/.default_config.json";

    class Configuration {
        public:
            Configuration();
            ~Configuration();

            void openConfigFile(std::string const &filePath);

            bool isFolerValid();
            bool hasFileMagicKey();
            bool doesFileExists(std::string const &filePath);
            std::vector<std::string> getConfigFiles(std::string const &folderPath);

            boost::property_tree::ptree getFileContent() const;
            void setFileContent(std::string const &filePath);

            void setMapDataConfig();
            std::map<std::string, std::string> getDataConfig() const;
        protected:
        private:
            boost::property_tree::ptree _root;
            std::map<std::string, std::string> _dataConfig = {};
    };
}

#endif /* !CONFIGURATION_HPP_ */
