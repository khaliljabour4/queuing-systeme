#ifndef QUEUE_H
#define QUEUE_H

#include <Arduino.h>
#include <Preferences.h>

class WQueue {
private:
    short counters[16]{};
    short queuesH[16]{};
    short queuesT[16]{};
    byte cqueue[16]{};
    Preferences cnf;
public:
    WQueue(String ns);
    int next(byte id);
    void setQueue(byte id, byte queue);
    int getQueue(byte id);
    int getCurrent(byte id);
    bool isActive(byte id);
    int getCount(byte id);
    int remaining(byte id);
    int push(byte id);
    int getLast(void);
    bool flush();
};

#endif
