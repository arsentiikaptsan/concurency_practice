#ifndef TASK2CYCLICBARIER_CYCLICBARIER_H
#define TASK2CYCLICBARIER_CYCLICBARIER_H

#endif //TASK2CYCLICBARIER_CYCLICBARIER_H

#pragma once

#include <condition_variable>
#include <cstddef>

template <typename ConditionVariable = std::condition_variable>
class CyclicBarrier {
public:
    CyclicBarrier(size_t num_threads) {}

    void Pass() {}
};