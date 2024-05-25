#ifndef ARRAY_HPP_D2DS
#define ARRAY_HPP_D2DS

#include <initializer_list>

namespace d2ds {
// show your code

template <typename T, unsigned int N>
class Array {
public:
    Array(std::initializer_list<T> list) {
        int i = 0;
        for (auto it = list.begin(); it != list.end() && i < N; it++) {
            mData_e[i] = *it;
            i++;
        }
    }
public: // bigFive
    Array() = default;

    Array(const Array &dsObj) {
        for (int i = 0; i < N; i++) {
            mData_e[i] = dsObj.mData_e[i];
        }
    }

    Array & operator=(const Array &dsObj) {
        D2DS_SELF_ASSIGNMENT_CHECKER
        for (int i = 0; i < N; i++) {
            mData_e[i] = dsObj.mData_e[i];
        }
        return *this;
    }

    Array(Array &&dsObj) {
        for (int i = 0; i < N; i++) {
            mData_e[i] = std::move(dsObj.mData_e[i]);
        }
    }

    Array & operator=(Array &&dsObj) {
        D2DS_SELF_ASSIGNMENT_CHECKER
        for (int i = 0; i < N; i++) {
            mData_e[i] = std::move(dsObj.mData_e[i]);
        }
        return *this;
    }

    ~Array() = default;

public:

    T & operator[](int index) {
        // add start
        if (index < 0)
            index = N + index;
        // add end
        d2ds_assert(index >= 0 && index < N);
        return mData_e[index];
    }

    unsigned int size() const {
        return N;
    }

    T back() const {
        return mData_e[N != 0 ? N - 1 : 0];
    }

public:
    T * begin() {
        return mData_e;
    }

    T * end() {
        return mData_e + N;
    }

private:
    T mData_e[N == 0 ? 1 : N];
};


}

#endif