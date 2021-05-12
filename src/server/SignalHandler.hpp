/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** SignalHandler
*/

#ifndef SIGNALHANDLER_HPP_
#define SIGNALHANDLER_HPP_

#include <functional>
#include <csignal>

namespace Zia {
    class SignalHandler {
        public:
            explicit SignalHandler();
            ~SignalHandler();

            static void handler(int signal)
            {
                (void)signal;
                _hasExited = true;
            }

            static bool hasExited() { return _hasExited; }

        private:
            static bool _hasExited;
    };
}

#endif /* !SIGNALHANDLER_HPP_ */
