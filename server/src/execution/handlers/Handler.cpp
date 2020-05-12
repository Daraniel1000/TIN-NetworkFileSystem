#include "Handler.h"

void Handler::fail()
{
    //TODO ustawia data
    std::lock_guard<std::mutex> lk(m);
    cv.notify_all();
}