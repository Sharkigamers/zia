/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** Loader
*/

#include <string>
#include <iostream>

#include "ILoader.hpp"

#ifndef LOADER_HPP_
#define LOADER_HPP_

namespace Zia::loader {
    #ifdef _WIN32

        #include <Windows.h>
        #include <libloaderapi.h>

        static const std::string NO_HANDLER = "Error: Invalid handler (NULL)";

        class Loader {
            public:
                Loader(std::string const &filePath){
                    openLib(filePath);
                };
                ~Loader(){
                    freeLib();
                };

                    void openLib(std::string const &filePath) {
                        const std::string path = filePath + ".dll";
                        _handle = LoadLibrary(TEXT(path.c_str()));
                    };
                    void freeLib() {
                        FreeLibrary(_handle);
                    };

                    void *loadLib(std::string const &symbol) {
                        if (_handle != NULL)
                            return GetProcAddress(_handle, symbol.c_str());
                        std::cerr << NO_HANDLER << '\n';
                        return nullptr;
                    };


            protected:
            private:
                HMODULE _handle;
        };
    #else

        #include <dlfcn.h>

        class Loader {
            public:
                Loader(std::string const &filePath) {
                    openLib(filePath);
                };
                ~Loader() {
                    freeLib();
                };

                std::string getModuleName(std::string const &filePath) {
                    std::string s = filePath;
                    std::string delimiter = "/";
                    size_t pos = 0;
                    std::string token;
                    std::vector<std::string> tokenList;
                    std::string res;
                    
                    while ((pos = s.find(delimiter)) != std::string::npos) {
                        token = s.substr(0, pos);
                        tokenList.push_back(token);
                        s.erase(0, pos + delimiter.length());
                    }
                    for (auto x:tokenList) {
                        res += x;
                        res += '/';
                    }
                    res = "./"+res +"lib"+s+".so";
                    return (res);
                }

                void openLib(std::string const &filePath) {
                    const std::string path = getModuleName(filePath);
                    _handle = dlopen(path.c_str(), RTLD_LAZY);
                };

                void freeLib() {
                    if (_handle) 
                        dlclose(_handle);
                };

                void *loadLib(std::string const &symbol) {
                    if (_handle) {
                        void *sym = dlsym(_handle, symbol.c_str());

                        char *error = dlerror();

                        if (error != nullptr) {
                            std::cout << error << std::endl;
                            delete error;
                        }

                        if (sym)
                            return sym;
                        else
                            return nullptr;
                    } else {
                        return(nullptr);
                    }
                };

            protected:
            private:
                void *_handle;
        };
    #endif /* End of condition */
}

#endif /* !LOADER_HPP_ */
