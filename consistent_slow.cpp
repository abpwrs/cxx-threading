#include <iostream>
#include <thread>
#include <mutex>

int n_thread = 0;
std::mutex n_mutex; // global mutex to control access to n_thread

void f1(int &n) {
    for (int i = 0; i < 500000; ++i) {
        n_mutex.lock(); // lock access to n_thread
        ++n; // increment n_thread directly inside current thread
        n_mutex.unlock(); // unlock access to n_thread
    }
}

// increment is consistent -- mutex lock maintains state of shared memory
int main() {
    std::thread t1(f1, std::ref(n_thread)); // pass by reference
    std::thread t2(f1, std::ref(n_thread)); // pass by reference
    t1.join();
    t2.join();
    std::cout << "Threaded value of n is " << n_thread << '\n';
}


