#pragma once

#include <cstddef>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <iostream>

class BlockingQueueException : public std::exception {};

//typedef int T;

template <class T, class Container = std::deque<T> >
class BlockingQueue {
public:
    explicit BlockingQueue(const size_t& capacity) : capacity(capacity) {
        is_running = true;
    }
    void Put(T&& element) {
        std::unique_lock<std::mutex> lock(core_mutex);
        //std::cout << "put" << std::endl;

        if (!is_running) {
            throw BlockingQueueException();
        }

        while (is_running && (core.size() == capacity)) {
            put_condition.wait(lock);
        }

        if (!is_running) return;

        core.push_back(std::move(element));

        get_condition.notify_one();
    }

    bool Get(T& result) {
        std::unique_lock<std::mutex> lock(core_mutex);
        //std::cerr << "get" << std::endl;

        while (is_running && core.empty()) {
            get_condition.wait(lock);
        }

        if (core.empty() && !is_running) return false;

        result = std::move(core.front());
        core.pop_front();

        put_condition.notify_one();
        return true;
    }

    void Shutdown() {
        std::unique_lock<std::mutex> lock(core_mutex);
        //std::cerr << "shutdown" << std::endl;

        is_running = false;
        put_condition.notify_all();
        get_condition.notify_all();
    }

private:
    const size_t capacity;

    std::deque<T> core;
    bool is_running;

    std::mutex core_mutex;
    std::condition_variable put_condition;
    std::condition_variable get_condition;
};