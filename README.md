# Thread Pool (C++17)

A lightweight, header-only **thread pool library** implemented in C++17.  
This project demonstrates **multithreaded programming, task scheduling, synchronization, and futures**, all essential for building high-performance systems.

---

## Features
- **Header-only** — just include and use
- Configurable number of worker threads
- Task enqueueing with return values via `std::future`
- Graceful shutdown on destruction
- Uses `std::mutex` and `std::condition_variable` for synchronization

---

## Build Instructions

### Prerequisites
- CMake (>= 3.16)
- C++17-compatible compiler (GCC, Clang, MSVC)

### Steps
```bash
# Clone this repo
git clone https://github.com/Anish07/thread-pool-cpp.git
cd thread-pool-cpp

# Configure and build
cmake -S . -B build
cmake --build build -j

# Run example
./build/thread_pool_example
