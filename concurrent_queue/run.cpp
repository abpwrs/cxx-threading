//
// Created by Alex Powers on 2019-01-01.
//
#include <thread>
#include <iostream>
#include "ConcurrentQueue.h"

void enqueue(ConcurrentQueue<int> &c) {
    for (int i = 0; i < 50; ++i) {
        c.blockingPut(i);
    }
}

void dequeue(ConcurrentQueue<int> &c) {
    while (c.size() != 0) {
        c.blockingGet();
    }
}

int main() {
    ConcurrentQueue<int> cq;
    std::thread t1(enqueue, std::ref(cq));
    std::thread t2(dequeue, std::ref(cq));
    t1.join();
    t2.join();
    return 0;
}