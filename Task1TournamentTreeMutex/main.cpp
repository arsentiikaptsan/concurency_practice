#include <iostream>
#include <thread>
#include "solution.h"

#define THREADS_NUM 10

void work(TreeMutex* lock, int* count, int thread_id) {
    for (int i = 0; i < 50; i++) {
        lock->lock(thread_id);
        (*count)++;
        lock->unlock(thread_id);
    }
}

int main() {
    TreeMutex lock(THREADS_NUM);
    int* count = new int;
    *count = 0;
    std::vector<std::thread> vthr;
    for (int i = 0; i < THREADS_NUM; i++) {
        vthr.push_back(std::thread(work, &lock, count, i));
    }

    for (int i = 0; i < THREADS_NUM; i++) {
        vthr[i].join();
    }

    std::cout << *count << std::endl;

    delete count;
    return 0;
}