#include <iostream>
#include <thread>
#include "solution.h"

void work(BlockingQueue<int>* queue) {
    queue->Put(5);
    int res;
    queue->Get(res);
    std::cout << res << std::endl;
}

int main() {
    BlockingQueue<int> queue(1);
    std::thread thread1(work, &queue);

    queue.Shutdown();
    thread1.join();
    return 0;
}
