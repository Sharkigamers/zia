/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** ILoader
*/

#ifndef ILOADER_HPP_
#define ILOADER_HPP_

class ILoader {
    public:
        virtual ~ILoader() = default;

        virtual void openLib(std::string const &file_path) = 0;
        virtual void freeLib() = 0;

        virtual void *loadLib(std::string const &symbol) = 0;

    protected:
    private:
};

#endif /* !ILOADER_HPP_ */
