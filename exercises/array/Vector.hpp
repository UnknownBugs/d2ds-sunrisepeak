#ifndef VECTOR_HPP_D2DS
#define VECTOR_HPP_D2DS

#include <initializer_list>

#include "common/common.hpp"

namespace d2ds {
// show your code

template <typename T, typename Alloc = DefaultAllocator>
class Vector {

public:
    T * begin() {
        return mDataPtr_e;
    }

    T * end() {
        return mDataPtr_e + mSize_e;
    }

    const T * begin() const {
        return mDataPtr_e;
    }

    const T * end() const {
        return mDataPtr_e + mSize_e;
    }

public:

    void push_back(const T &val) {
        if (mSize_e + 1 > mCapacity_e) {
            resize(mCapacity_e == 0 ? 2 : mCapacity_e * 2);
        }
        new (mDataPtr_e + mSize_e) T(val);
        mSize_e++;
    }

    void pop_back() {
        mSize_e--;
        (mDataPtr_e + mSize_e)->~T();
        if (mSize_e <= mCapacity_e / 3) {
            resize(mCapacity_e / 2);
        }
    }

    void resize(int n) {
        auto newDataPtr = static_cast<T *>(Alloc::allocate(n * sizeof(T)));

        for (int i = 0; i < mSize_e; i++) {
            new (newDataPtr + i) T(mDataPtr_e[i]);
            (mDataPtr_e + i)->~T();
        }

        if (mDataPtr_e) {
            Alloc::deallocate(mDataPtr_e, mCapacity_e * sizeof(T));
        }

        mDataPtr_e = newDataPtr;
        mCapacity_e = n;
    }

public:

    T & operator[](int index) {
        return mDataPtr_e[index];
    }

    const T & operator[](int index) const {
        return mDataPtr_e[index];
    }

    bool empty() const {
        return mSize_e == 0;
    }

    int size() const {
        return mSize_e;
    }

    int capacity() const {
        return mCapacity_e;
    }

public:

    Vector() : mSize_e { 0 }, mDataPtr_e { nullptr } {
        mCapacity_e = 0;
    }

    Vector(int size) {
        mSize_e = mCapacity_e = size;
        mDataPtr_e = static_cast<T *> (Alloc::allocate(mCapacity_e * sizeof(T)));
        for (int i = 0; i < size; i++) {
            new (mDataPtr_e + i) T();
        }
    }

    Vector(std::initializer_list<T> list) {
        mCapacity_e = list.end() - list.begin();
        mSize_e = mCapacity_e;
        mDataPtr_e = static_cast<T *> (Alloc::allocate(mCapacity_e * sizeof(T)));
        T * addr = mDataPtr_e;
        for (auto it = list.begin(); it != list.end(); it++) {
            new (addr) T(*it);
            addr++;
        }

    }

    ~Vector() {
        if (mSize_e) {
            for (int i = 0; i < mSize_e; i++) {
                (mDataPtr_e + i)->~T();
            }
            Alloc::deallocate(mDataPtr_e, mSize_e * sizeof(T));
        }
        mSize_e = 0;
        mDataPtr_e = nullptr;
    }


public:
    Vector(const Vector &dsObj) {
        mSize_e = dsObj.mSize_e;
        mCapacity_e = dsObj.mCapacity_e;
        mDataPtr_e = (T *) Alloc::allocate(mCapacity_e * sizeof(T));
        for (int i = 0; i < mSize_e; i++) {
            new (mDataPtr_e + i) T( dsObj.mDataPtr_e[i] );
        }
    }

    Vector(Vector &&dsObj) {
        mSize_e = dsObj.mSize_e;
        mDataPtr_e = dsObj.mDataPtr_e;
        mCapacity_e = dsObj.mCapacity_e;

        // reset
        dsObj.mSize_e = 0;
        dsObj.mDataPtr_e = nullptr;
        dsObj.mCapacity_e = 0;
    }

    Vector & operator=(const Vector &dsObj) {

        if (this == &dsObj) return *this;

        this->~Vector();

        mSize_e = dsObj.mSize_e;
        mCapacity_e = dsObj.mCapacity_e;
        mDataPtr_e = (T *) Alloc::allocate(mCapacity_e * sizeof(T));
        for (int i = 0; i < mSize_e; i++) {
            //new (mDataPtr_e + i) T( dsObj.mDataPtr_e[i] );
            mDataPtr_e[i] = dsObj.mDataPtr_e[i];
        }

        return *this;

    }

    Vector & operator=(Vector &&dsObj) {
        if (this == &dsObj) return *this;

        this->~Vector();

        mSize_e = dsObj.mSize_e;
        mDataPtr_e = dsObj.mDataPtr_e;
        mCapacity_e = dsObj.mCapacity_e;

        // reset
        dsObj.mSize_e = 0;
        dsObj.mDataPtr_e = nullptr;
        dsObj.mCapacity_e = 0;

        return *this;
    }

private:
    int mSize_e, mCapacity_e;
    T * mDataPtr_e;
};

template <typename T>
bool operator==(const Vector<T> &v1, const Vector<T> &v2) {
    if (v1.size() != v2.size()) return false;
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
Vector<T> operator+(const Vector<T> &v1, const Vector<T> &v2) {
    Vector<T> v(v1.capacity());
    for (int i = 0; i < v.size(); i++) {
        v[i] = v1[i] + v2[i];
    }
    return v;
}

template <typename T>
Vector<T> operator-(const Vector<T> &v1, const Vector<T> &v2) {
    Vector<T> v(v1.capacity());
    for (int i = 0; i < v.size(); i++) {
        v[i] = v1[i] - v2[i];
    }
    return v;
}

}

#endif