#pragma once

#include <thread>
#include <atomic>

///////////////////////////////////////////////////////////////////////

template <typename T, template <typename U> class Atomic = std::atomic>
class LockFreeQueue {
    struct Node {
        T element{};
        Atomic<Node*> next{nullptr};

        explicit Node(T element, Node* next = nullptr)
                : element(std::move(element))
                , next(next) {
        }

        explicit Node() {
        }
    };

public:
    LockFreeQueue() {
        Node* dummy = new Node{};
        head = dummy;
        tail = dummy;
        head_of_trash = dummy;

        invocations_counter.store(0);
    }

    ~LockFreeQueue() {
        Node* iter = head_of_trash;
        while (iter != nullptr) {
            Node* next = iter->next.load();

            delete iter;

            iter = next;
        }
    }

    void Enqueue(T element) {
        invocations_counter++;

        Node* node = new Node(element);
        while (true) {
            Node* last = tail.load();
            Node* next = last->next.load();
            if (last == tail.load()) {
                if (next == nullptr) {
                    if (last->next.compare_exchange_strong(next, node)) {
                        tail.compare_exchange_strong(last, node);
                        invocations_counter--;
                        return;
                    }
                } else {
                    tail.compare_exchange_strong(last, next);
                }
            }
        }
    }

    bool Dequeue(T& element) {
        invocations_counter++;

        bool result = false;
        while (true) {
            Node* first = head.load();
            Node* last = tail.load();
            Node* next = first->next.load();
            if (first == head.load()) {
                if (first == last) {
                    if (next == nullptr) {
                        result = false;
                        break;
                    }
                    tail.compare_exchange_strong(last, next);
                } else {
                    T value = next->element;
                    if (head.compare_exchange_strong(first, next)) {
                        element = value;
                        result = true;
                        break;
                    }
                }
            }
        }

        Node* head_node = head.load();
        if (invocations_counter.load() == 1) {
            Node* iter = head_of_trash;
            while (iter != head_node) {
                Node* next = iter->next.load();

                delete iter;

                iter = next;
            }
            head_of_trash = iter;
        }

        invocations_counter--;
        return result;
    }

private:
    Atomic<Node*> head{nullptr};
    Atomic<Node*> tail{nullptr};

    std::atomic_size_t invocations_counter;

    Node* head_of_trash{nullptr};
};

///////////////////////////////////////////////////////////////////////
