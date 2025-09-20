
#pragma once
#include <vector>
#include <thread>
#include <future>
#include <queue>
#include <functional>
#include <condition_variable>
#include <atomic>

namespace tp {

class thread_pool {
public:
    explicit thread_pool(size_t threads = std::thread::hardware_concurrency())
        : stop_(false) {
        if (threads == 0) threads = 1;
        for (size_t i = 0; i < threads; ++i) {
            workers_.emplace_back([this]{
                for (;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx_);
                        cv_.wait(lock, [this]{ return stop_ || !tasks_.empty(); });
                        if (stop_ && tasks_.empty()) return;
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    task();
                }
            });
        }
    }

    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::invoke_result<F, Args...>::type> {
        using ret_t = typename std::invoke_result<F, Args...>::type;
        auto task = std::make_shared<std::packaged_task<ret_t()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        std::future<ret_t> res = task->get_future();
        {
            std::lock_guard<std::mutex> lock(mtx_);
            if (stop_) throw std::runtime_error("enqueue on stopped thread_pool");
            tasks_.emplace([task]{ (*task)(); });
        }
        cv_.notify_one();
        return res;
    }

    ~thread_pool() {
        {
            std::lock_guard<std::mutex> lock(mtx_);
            stop_ = true;
        }
        cv_.notify_all();
        for (auto& w : workers_) if (w.joinable()) w.join();
    }

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mtx_;
    std::condition_variable cv_;
    bool stop_;
};

} // namespace tp
