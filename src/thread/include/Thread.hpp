/*
** EPITECH PROJECT, 2021
** B-YEP-500-PAR-5-1-zia-emmanuel.blineau
** File description:
** Thread
*/

#include <boost/thread.hpp>

#include "IThread.hpp"

#ifndef THREAD_HPP_
#define THREAD_HPP_

namespace zia::thread {
    class Thread : public IThread {
        public:
            Thread(std::function<void()> const &myFunc) {
                createThread(myFunc);
            };
            ~Thread() {};

            void createThread(std::function<void()> const &myFunc)
            {
                _myThread = boost::thread(myFunc);
            }

        protected:
        private:
            boost::thread _myThread;
    };
}

#endif /* !THREAD_HPP_ */
