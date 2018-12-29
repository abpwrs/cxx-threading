#include <iostream>
#include <thread>

int n_thread = 0;

void f1(int &n) {
    for (int i = 0; i < 500000; ++i) {
        // increment n_thread directly inside current thread 
        // (I wonder what the other thread is doing...)
        ++n;
    }
}

// increment is inconsistent due to overwriting of a shared memory location between two threads
int main() {
    std::thread t1(f1, std::ref(n_thread)); // pass by reference
    std::thread t2(f1, std::ref(n_thread)); // pass by reference
    t1.join();
    t2.join();
    std::cout << "Threaded value of n is " << n_thread << '\n';
}
