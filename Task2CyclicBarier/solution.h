#ifndef TASK2CYCLICBARIER_CYCLICBARIER_H
#define TASK2CYCLICBARIER_CYCLICBARIER_H

#endif //TASK2CYCLICBARIER_CYCLICBARIER_H

#pragma once

#include <condition_variable>
#include <cstddef>
#include <atomic>
#include <mutex>

//typedef std::condition_variable ConditionVariable;

template <typename ConditionVariable = std::condition_variable>
struct Monitor {
    std::mutex mutex;
    ConditionVariable condition;
};

template <typename ConditionVariable = std::condition_variable>
class CyclicBarrier {
public:
    CyclicBarrier(size_t num_threads) : threads_number(num_threads) {
        locked_threads_number.store(0);
        is_barrier_reached.store(false);
    }

    void Pass() {
        std::unique_lock<std::mutex> lock1_on_is_barrier_reached(monitor_is_barrier_reached.mutex);
        while (is_barrier_reached.load()) {
            monitor_is_barrier_reached.condition.wait(lock1_on_is_barrier_reached);
        }
        lock1_on_is_barrier_reached.unlock();

        size_t new_lck_num = locked_threads_number.fetch_add(1) + 1;

        if (new_lck_num == threads_number) {
            std::unique_lock<std::mutex> lock2_on_is_barrier_reached(monitor_is_barrier_reached.mutex);
            is_barrier_reached.store(true);
            monitor_is_barrier_reached.condition.notify_all();
            lock2_on_is_barrier_reached.unlock();
        }

        std::unique_lock<std::mutex> lock3_on_is_barrier_reached(monitor_is_barrier_reached.mutex);
        while (!is_barrier_reached.load()) {
            monitor_is_barrier_reached.condition.wait(lock3_on_is_barrier_reached);
        }
        lock3_on_is_barrier_reached.unlock();

        new_lck_num = locked_threads_number.fetch_sub(1) - 1;

        if (new_lck_num == 0) {
            std::unique_lock<std::mutex> lock4_on_is_barrier_reached(monitor_is_barrier_reached.mutex);
            is_barrier_reached.store(false);
            monitor_is_barrier_reached.condition.notify_all();
            lock4_on_is_barrier_reached.unlock();
        }
    }

private:
    const size_t threads_number;

    std::atomic_size_t locked_threads_number;
    std::atomic_bool is_barrier_reached;

    Monitor<ConditionVariable> monitor_is_barrier_reached;
};