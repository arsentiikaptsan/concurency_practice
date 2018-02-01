#include <mutex>
#include <array>
#include <thread>
#include <cmath>
#include <vector>
#include <bitset>
#include <atomic>

#define BITSET_SIZE 32

class PetersonLock
{
public:
    PetersonLock()
    {
        want[0].store(false);
        want[1].store(false);
        waiting.store(0);
    }

    PetersonLock& operator=(const PetersonLock&) = delete;
    PetersonLock& operator=(PetersonLock&&) = delete;

    void lock(int threadId)
    {
        int other = 1 - threadId;
        want[threadId].store(true);
        waiting.store(threadId);
        while (want[other].load() && waiting.load() == threadId) {
            std::this_thread::yield();
        }
    }

    void unlock(int threadId) {
        want[threadId].store(false);
    }

private:
    std::array<std::atomic<bool>, 2> want;
    std::atomic<int> waiting;
};

class TreeMutex {
public:
    TreeMutex(int n_threads) {
        tree_depth = (int)ceil(log2((double)n_threads));
        leafs_num = (int)pow(2.0, (double)tree_depth);
        locks_tree = std::vector<PetersonLock>(leafs_num);
    }

    void lock(int current_thread) {
        int index = leafs_num + current_thread;
        while (index > 1) {
            int parent = index / 2;
            locks_tree.at(parent).lock(index % 2);
            index = parent;
        }
    }

    void unlock(int current_thread) {
        int index = leafs_num + current_thread;

        std::bitset<BITSET_SIZE> current_thread_binary(current_thread);
        int current_node = 1;
        for (int i = tree_depth - 1;  (current_node != index) && (i >= 0); i--) {
            int child = 2*current_node + current_thread_binary[i];
            locks_tree.at(current_node).unlock(current_thread_binary[i]);
            current_node = child;
        }
    }

private:
    int leafs_num;
    int tree_depth;

    //locks_tree[0] is empty
    std::vector<PetersonLock> locks_tree;
};