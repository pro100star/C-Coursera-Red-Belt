#include <iostream>
#include <vector>

template <typename T>
class Deque {
public:
    Deque() {
        back = {};
        front = {};
    }

    bool Empty() const {
        return back.empty() && front.empty();
    }

    size_t Size() const {
        return back.size() + front.size();
    }

    T& operator[](size_t index) {
        if (index < front.size()) {
            return front[front.size() - index - 1];
        }
        return back[index - front.size()];
    }

    const T& operator[](size_t index) const {
        if (index < front.size()) {
            return front[front.size() - index - 1];
        }
        return back[index - front.size()];
    }

    T& At(size_t index) {
        if (index >= Size()) {
            throw std::out_of_range("Deque index is out of range");
        }
        return (*this)[index];
    }

    const T& At(size_t index) const {
        if (index >= Size()) {
            throw std::out_of_range("Deque index is out of range");
        }
        return this[index];
    }

    T& Front() {
        if (!front.empty()) {
            return front.back();
        }
        if (!back.empty()) {
            return back.front();
        }
        throw std::out_of_range("");
    }

    const T& Front() const {
        if (!front.empty()) {
            return front.back();
        }
        if (!back.empty()) {
            return back.front();
        }
        throw std::out_of_range("");
    }

    T& Back() {
        if (!back.empty()) {
            return back.back();
        }
        if (!front.empty()) {
            return front.front();
        }
        throw std::out_of_range("");
    }

    const T& Back() const {
        if (!back.empty()) {
            return back.back();
        }
        if (!front.empty()) {
            return front.front();
        }
        throw std::out_of_range("");
    }

    void PushBack(const T& t) {
        back.push_back(t);
    }

    void PushFront(const T& t) {
        front.push_back(t);
    }

private:
    std::vector<T> front, back;
};
