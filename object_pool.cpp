#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        if (!released.empty()) {
            T* ref = released.front();
            allocated.insert(ref);
            released.pop();
            return ref;
        }
        T* ref = new T;
        allocated.insert(ref);
        return ref;
    }


    T* TryAllocate() {
        if (!released.empty()) {
            T* ref = released.front();
            allocated.insert(ref);
            released.pop();
            return ref;
        }
        return nullptr;
    }

    void Deallocate(T* object) {
        auto it = allocated.find(object);
        if (it == allocated.end()) {
            throw invalid_argument("");
        }
        released.push(*it);
        allocated.erase(it);
    }

    ~ObjectPool() {
        for (auto& e : allocated) {
            delete e;
        }
        allocated.clear();
        while (!released.empty()) {
            delete released.front();
            released.pop();
        }
    }

private:
    set<T*> allocated;
    queue<T*> released;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
