#include <cstdio>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <utility>

#ifndef TASK2ROBOT_SOLUTION_H
#define TASK2ROBOT_SOLUTION_H

#endif //TASK2ROBOT_SOLUTION_H


class Semaphore {
public:

    explicit Semaphore(const size_t capacity) : capacity(capacity) {
        state = 0;
    }

    void acquire() {
        std::unique_lock<std::mutex> lock(my_mutex);
        while (state == capacity) {
            condition.wait(lock);
        }
        state++;
        lock.unlock();
    }

    void release() {
        std::unique_lock<std::mutex> lock(my_mutex);
        state--;
        condition.notify_all();
        lock.unlock();
    };

private:
    const size_t capacity;
    size_t state;
    std::mutex my_mutex;
    std::condition_variable condition;
};

class RobotBrain {
public:

    RobotBrain(const size_t num_foots, std::function<void(size_t)> step_action) : num_foots(num_foots), step_action(
            std::move(step_action)) {
        permitiom_for_step = new bool[num_foots] {};
        mutexes_on_permitions = new std::mutex[num_foots];
        conditions = new std::condition_variable[num_foots];

        permitiom_for_step[0] = true;
    }

    virtual ~RobotBrain() {
        delete[] permitiom_for_step;
        delete[] mutexes_on_permitions;
        delete[] conditions;
    }

    void Step(size_t foot) {
        std::unique_lock<std::mutex> lock_on_thisone(this->mutexes_on_permitions[foot]);
        while (!permitiom_for_step[foot]) {
            conditions[foot].wait(lock_on_thisone);
        }
        step_action(foot);
        permitiom_for_step[foot] = false;
        lock_on_thisone.unlock();

        std::unique_lock<std::mutex> lock_on_nextone(this->mutexes_on_permitions[NextFoot(foot)]);
        permitiom_for_step[NextFoot(foot)] = true;
        conditions[NextFoot(foot)].notify_all();
        lock_on_nextone.unlock();
    }

private:
    const size_t num_foots;
    const std::function<void(size_t)> step_action;

    bool* permitiom_for_step;
    std::mutex* mutexes_on_permitions;
    std::condition_variable* conditions;

    size_t NextFoot(size_t foot) {
        return (foot + 1) % num_foots;
    }
};

class Robot {
public:
    Robot() : brain(2, Robot::step_function) {}

    void StepLeft() {
        brain.Step(0);
    }

    void StepRight() {
        brain.Step(1);
    }

private:
    static void step_function(size_t foot) {
        std::cout << (foot ? "right" : "left") << std::endl;
    }

    RobotBrain brain;
};