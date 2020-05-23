#ifndef MYNFS_TERMINALLISTENER_H
#define MYNFS_TERMINALLISTENER_H

#include <iostream>
#include <mutex>

class TerminalListener {
public:
    std::mutex serverStop;

    //TerminalListener(std::mutex& m): serverStop(m) {};

    void run(){
        serverStop.lock();
        std::cout<<"Press any key to stop the server...";
        std::cin.get();
        serverStop.unlock();
    };

};

#endif //MYNFS_TERMINALLISTENER_H
