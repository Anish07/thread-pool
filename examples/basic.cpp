
#include <iostream>
#include <chrono>
#include "thread_pool/thread_pool.hpp"

int main() {
    tp::thread_pool pool(4);
    auto f1 = pool.enqueue([]{ return 40 + 2; });
    auto f2 = pool.enqueue([]{ std::this_thread::sleep_for(std::chrono::milliseconds(100)); return std::string("done"); });
    std::cout << "f1=" << f1.get() << ", f2=" << f2.get() << "\n";
    return 0;
}
