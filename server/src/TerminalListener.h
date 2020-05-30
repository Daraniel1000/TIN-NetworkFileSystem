#ifndef MYNFS_TERMINALLISTENER_H
#define MYNFS_TERMINALLISTENER_H

#include <transport/socket/UDPSocket.h>
#include <iostream>
#include <mutex>

class TerminalListener {
    UDPSocket& socket;
public:
    std::mutex serverStop;

    TerminalListener(UDPSocket& s): socket(s) {};

    void writeQuit(){
        std::cout<<"Server quit correctly"<<std::endl;
    }

    void run(){
        serverStop.lock();
        std::cout << "Press any key to stop the server..." << std::endl;
        std::cin.get();
        serverStop.unlock();
        socket.signal();
    };

};

#endif //MYNFS_TERMINALLISTENER_H
