#pragma once

#include "spinlock_pause.h"

#include <iostream>
#include <atomic>
#include <thread>

//////////////////////////////////////////////////////////////////////

/* scalable and fair MCS (Mellor-Crummy, Scott) spinlock implementation
 *
 * usage:
 * {
 *   MCSSpinLock::Guard guard(spinlock); // spinlock acquired
 *   ... // in critical section
 * } // spinlock released
 */

template <template <typename T> class Atomic = std::atomic>
class MCSSpinLock {
public:
    class Guard {
    public:
        explicit Guard(MCSSpinLock& spinlock)
                : spinlock_(spinlock) {
            Acquire();
        }

        ~Guard() {
            Release();
        }

    private:
        void Acquire() {
            Guard* prev_tail = spinlock_.wait_queue_tail_.exchange(this);

            if (prev_tail != nullptr) {
                is_owner_.store(false);
                prev_tail->next_.store(this);

                while (!is_owner_.load()) {
                    std::this_thread::yield();
                }
            }
        }

        void Release() {
            if (next_.load() == nullptr) {
                Guard* cpy = this;
                if (spinlock_.wait_queue_tail_.compare_exchange_strong(cpy, nullptr)) {
                    return;
                }
                while (next_.load() == nullptr) {
                    std::this_thread::yield();
                }
            }
            next_.load()->is_owner_ = true;
            next_.store(nullptr);
        }

    private:
        MCSSpinLock& spinlock_;

        Atomic<bool> is_owner_{false};
        Atomic<Guard*> next_{nullptr};
    };

private:
    Atomic<Guard*> wait_queue_tail_{nullptr};
};

/////////////////////////////////////////////////////////////////////

// alias for checker
template <template <typename T> class Atomic = std::atomic>
using SpinLock = MCSSpinLock<Atomic>;

/////////////////////////////////////////////////////////////////////

