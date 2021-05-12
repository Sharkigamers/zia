/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** main
*/

#include "src/server/ZiaCore.hpp"

#include <string>
#include <filesystem>

#include "Request.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "No config file provided: Usage: ./zia [config file path]" << std::endl;
        return 84;
    }
    else {
        std::srand(std::time(nullptr));
        const std::string path = av[1];

        if (path.find(".json") == std::string::npos) {
            std::cerr << "Config file must be json formatted." << std::endl;
            return 84;
        }
        try
        {
            Zia::ZiaCore core(path);
            core.run();
            return 0;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    return 1;
}