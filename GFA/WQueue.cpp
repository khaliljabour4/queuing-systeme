 #include "WQueue.h"

#define SIZE_ASSERT(x) if ((x & 0xF0) != 0) return
#define SIZE_ASSERT_RET(x,i) if ((x & 0xF0) != 0) return i

WQueue::WQueue(String ns) {
    cnf.begin(("Q"+ns).c_str());
    cnf.getBytes("queues",cqueue,16);
}

bool WQueue::flush() {
  return cnf.putBytes("queues",cqueue,16) == 16;  
}

int WQueue::next(byte id) {
    SIZE_ASSERT_RET(id,-1);
    byte queue = cqueue[id];
    short head = queuesH[queue] + 1;
    short tail = queuesT[queue];
    if (head > tail) {
        return -1;
    }
    queuesH[queue] += 1;
    counters[id] = head;
    return head;
}

void WQueue::setQueue(byte id, byte queue) {
    SIZE_ASSERT(id);
    SIZE_ASSERT(queue);
    cqueue[id] = queue;
}
int WQueue::getQueue(byte id) {
    SIZE_ASSERT_RET(id, -1);
    return cqueue[id];
}
int WQueue::getCurrent(byte id) {
    SIZE_ASSERT_RET(id, -1);
    return queuesH[cqueue[id]];
}
bool WQueue::isActive(byte id) {
    return getCurrent(id) > 0;
}
int WQueue::getCount(byte id) {
    SIZE_ASSERT_RET(id, -1);
    int count = 0;
    for (int i = 0; i < 16; i++){
        if (cqueue[i] == id) count += 1;
    }
    return count;
}
int WQueue::remaining(byte id) {
    SIZE_ASSERT_RET(id, -1);
    byte queue = cqueue[id];
    short head = queuesH[queue];
    short tail = queuesT[queue];
    return tail - head;
}
int WQueue::push(byte id) {
    SIZE_ASSERT_RET(id, -1);
    return queuesT[id] += 1;
}

int WQueue::getLast(void) {
    for (size_t i = 0; i < 16; i++)
    {
        if(counters[i] <= 0)
            return i;
    }
    return 16;
}
