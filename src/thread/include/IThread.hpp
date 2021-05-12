/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** IThread
*/

#include <functional>

#ifndef ITHREAD_HPP_
#define ITHREAD_HPP_

class IThread {
    public:
        virtual ~IThread() = default;

        virtual void createThread(std::function<void()> const &myFunc) = 0;

    protected:
    private:
};

#endif /* !ITHREAD_HPP_ */
