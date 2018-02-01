#pragma once

#include <functional>
#include <vector>
#include <list>
#include <array>
#include <mutex>
#include <atomic>
#include <algorithm>

#define MIN_TABLE_SIZE (size_t)10

///////////////////////////////////////////////////////////////////////

//template <typename T, class Hash = std::hash<T>>
//class LockHelper;

template <typename T, class Hash = std::hash<T>>
class StripedHashSet {
public:
    //friend LockHelper;

    explicit StripedHashSet(const size_t concurrency_level,
                            const size_t growth_factor_ = 3,
                            const double load_factor_ = 0.75) : locks_num(concurrency_level),
                                                                growth_factor(growth_factor_),
                                                                load_factor(load_factor_)
    {
        set_size.store(0);
        table_size.store(std::max(concurrency_level, MIN_TABLE_SIZE));
        table = new std::list<T>[table_size.load()];
        locks = new std::recursive_mutex[locks_num];
    }

    virtual ~StripedHashSet() {
        delete[] table;
        delete[] locks;
    }

    bool Insert(const T& element) {
        Acquire(element);

        std::list<T>* bucket = table + GetBucketIndex(element);
        auto item = std::find(bucket->begin(), bucket->end(), element);
        if (item != (bucket->end())) {
            Release(element);
            return false;
        }
        bucket->push_back(element);
        set_size++;

        Release(element);

        if (Policy()) {
            Resize();
        }

        return true;
    }

    bool Remove(const T& element) {
        Acquire(element);

        std::list<T>* bucket = table + GetBucketIndex(element);
        auto item = std::find(bucket->begin(), bucket->end(), element);
        if (item == (bucket->end())) {
            Release(element);
            return false;
        }
        bucket->erase(item);
        set_size--;

        Release(element);
        return true;
    }

    bool Contains(const T& element) {
        Acquire(element);
        std::list<T>* bucket = table + GetBucketIndex(element);

        bool result = (std::find(bucket->begin(), bucket->end(), element) != bucket->end());

        Release(element);
        return result;
    }

    size_t Size() {
        return set_size.load();
    }

private:
    size_t GetBucketIndex(const T& element) const {
        return Hash() (element) % table_size.load();
    }

    size_t GetStripeIndex(const T& element) const {
        return Hash() (element) % locks_num;
    }

    void Acquire(const T& element) {
        locks[GetStripeIndex(element)].lock();
    }

    void Release(const T& element) {
        locks[GetStripeIndex(element)].unlock();
    }

    bool Policy() {
        return (table_size.load() < load_factor * set_size);
    }

    void Resize() {
        locks[0].lock();
        if (!Policy()) {
            //нас кто-то опередил
            locks[0].unlock();
            return;
        }
        for (size_t i = 1; i < locks_num; i++) {
            locks[i].lock();
        }

        size_t new_table_size = growth_factor * table_size.load();
        std::list<T>* new_table = new std::list<T>[new_table_size];

        for (size_t i = 0; i < table_size.load(); i++) {
            for (auto iter = table[i].begin(); iter != table[i].end(); ++iter) {
                new_table[Hash() (*iter) % new_table_size].push_back(*iter);
            }
        }
        delete[] table;

        table = new_table;
        table_size.store(new_table_size);

        for (size_t i = 0; i < locks_num; i++) {
            locks[i].unlock();
        }
    }

private:
    std::list<T>* table;
    std::atomic_size_t table_size;

    std::recursive_mutex* locks;
    const size_t locks_num;

    std::atomic_size_t set_size;

    const size_t growth_factor;
    const double load_factor;
};

template <typename T> using ConcurrentSet = StripedHashSet<T>;

//template <typename T, class Hash = std::hash<T>>
//class LockHelper {
//public:
//    explicit LockHelper(StripedHashSet <T, Hash> *link, const T& element_) : link(link), element(element_) {
//        link->Acquire(element);
//    }
//
//    virtual ~LockHelper() {
//        link->Release(element);
//    }
//
//private:
//    StripedHashSet<T>* link;
//
//    const T& element;
//};
