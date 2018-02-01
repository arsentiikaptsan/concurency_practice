#pragma once

#include <atomic>
#include <thread>

///////////////////////////////////////////////////////////////////////

template <typename T>
class LockFreeStack {
    struct Node {
        Node(const T& value_) : value(value_) {}

        T value;
        Node* next{nullptr};
        Node* next_in_garbage{nullptr};
    };

public:
    LockFreeStack() {
    }

    ~LockFreeStack() {
        delete_list_of_nodes(top.load(), false);
        delete_list_of_nodes(head_of_trash.load(), true);
    }

    void Push(T element) {
        Node* new_node = new Node(element);

        while (true) {
            Node* old_top = top.load();
            new_node->next = old_top;
            if (top.compare_exchange_strong(old_top, new_node)) {
                return;
            };
        }
    }

    bool Pop(T& element) {
        while (true) {
            Node* old_top = top.load();
            if (old_top == nullptr) {
                return false;
            }
            Node* new_top = old_top->next;
            if (top.compare_exchange_strong(old_top, new_top)) {
                element = old_top->value;
                while (true) {
                    Node* old_head_of_trash = head_of_trash.load();
                    old_top->next_in_garbage = old_head_of_trash;
                    if (head_of_trash.compare_exchange_strong(old_head_of_trash, old_top)) {
                        break;
                    }
                }
                return true;
            }
        }
    }

private:
    std::atomic<Node*> top{nullptr};

    std::atomic<Node*> head_of_trash{nullptr};

    void delete_list_of_nodes(Node* head, bool is_garbage_list) {
        Node* iter = head;
        while (iter != nullptr) {
            Node* next = (is_garbage_list ? iter->next_in_garbage : iter->next);
            delete iter;
            iter = next;
        }
    }
};

///////////////////////////////////////////////////////////////////////

template <typename T>
using ConcurrentStack = LockFreeStack<T>;

///////////////////////////////////////////////////////////////////////
