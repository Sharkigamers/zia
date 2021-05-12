/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** Configuration
*/

#include "Configuration.hpp"

zia::common::Configuration::Configuration()
{
}

zia::common::Configuration::~Configuration()
{
}

void zia::common::Configuration::openConfigFile(std::string const &filePath)
{
     if (doesFileExists(filePath)) {
         try {
              setFileContent(filePath);

             // if (hasFileMagicKey() != 0)
             //     throw ConfigurationError(UNFOUND_MAGICKEY(filePath));
         } catch(const std::exception& e) {
              throw ConfigurationError(UNFOUND_FILE(filePath));
         }
     } else
        throw ConfigurationError(UNFOUND_FILE(filePath));
}

bool zia::common::Configuration::isFolerValid()
{
    return true;
}

bool zia::common::Configuration::hasFileMagicKey()
{
    return _root.get<std::string>("MagicKey").compare(MAGIC_KEY);
}

bool zia::common::Configuration::doesFileExists(std::string const &filePath)
{
    std::ifstream fileExist(filePath);

    if (fileExist)
        return true;
    return false;
}

boost::property_tree::ptree zia::common::Configuration::getFileContent() const
{
    return _root;
}

void zia::common::Configuration::setFileContent(std::string const &filePath)
{
    boost::property_tree::read_json(filePath, _root);
}

void zia::common::Configuration::setMapDataConfig()
{
    try {
        for (boost::property_tree::ptree::const_iterator it = _root.begin(); it != _root.end(); it++) {
            _dataConfig[it->first] = it->second.get_value<std::string>();
        }
    } catch(const std::exception& e) {
        throw ConfigurationError(UNMAPPABLE_DATA());
    }
}

std::map<std::string, std::string> zia::common::Configuration::getDataConfig() const
{
    return _dataConfig;
}
