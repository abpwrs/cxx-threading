#include <iostream>
#include <thread>
#include <mutex>

int n_thread = 0;
std::mutex n_mutex; // global mutex to control access to n_thread

void f1(int &n) {
    int temp = 0; // memory local to each thread
    for (int i = 0; i < 500000; ++i) {
        ++temp; // no conflict
    }
    // ONLY NEED TO ACCESS SHARED MEMORY ONCE!
    n_mutex.lock(); // lock access to n_thread
    n += temp; // increment n_thread directly inside current thread
    n_mutex.unlock(); // unlock access to n_thread
}

// same mantinence of share memory with mutex
int main() {
    std::thread t1(f1, std::ref(n_thread)); // pass by reference
    std::thread t2(f1, std::ref(n_thread)); // pass by reference
    t1.join();
    t2.join();
    std::cout << "Threaded value of n is " << n_thread << '\n';
}


