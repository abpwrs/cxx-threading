//
// Created by Alex Powers on 2019-01-01.
//

#ifndef CXX_THREADING_CONCURRENTQUEUE_H
#define CXX_THREADING_CONCURRENTQUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>

template<typename T>
class ConcurrentQueue {
public:
    void blockingPut(T data) {
        queue_mutex.lock();
        std::cout << "enqueuing data: " << data << std::endl;
        m_queue.push(data);
        queue_mutex.unlock();
    }

    T blockingGet() {
        queue_mutex.lock();
        T temp = m_queue.front();
        m_queue.pop();
        std::cout << "dequeuing item: " << temp << std::endl;
        queue_mutex.unlock();
        return temp;
    }

    int size() {
        queue_mutex.lock();
        int val = m_queue.size();
        queue_mutex.unlock();
        return val;
    }

    bool empty() {
        queue_mutex.lock();
        bool val = m_queue.empty();
        queue_mutex.unlock();
        return val;
    }

private:
    std::condition_variable canRead;
    std::mutex queue_mutex;
    std::queue <T> m_queue;
};


#endif //CXX_THREADING_CONCURRENTQUEUE_H
