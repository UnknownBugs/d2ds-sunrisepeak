#ifndef SLINKED_LIST_HPP_D2DS
#define SLINKED_LIST_HPP_D2DS

#include <common/common.hpp>

namespace d2ds {
// show your code

template <typename T>
struct SLinkedListNode {
    SLinkedListNode *next;
    T data;
};

template <typename T>
struct SLinkedListIterator {
    using Node = SLinkedListNode<T>;
    SLinkedListIterator() : mNodePtr { nullptr } { }
    SLinkedListIterator(Node *nodePtr) { mNodePtr = nodePtr; }

    bool operator==(SLinkedListIterator it) {
        return it.mNodePtr == mNodePtr;
    }

    bool operator!=(SLinkedListIterator it) {
        return it.mNodePtr != mNodePtr;
    }

    SLinkedListIterator & operator++() {
        mNodePtr = mNodePtr->next;
        return *this;
    }

    SLinkedListIterator operator++(int) {
        auto old = *this;
        mNodePtr = mNodePtr->next;
        return old;
    }

    T * operator->() {
        return &(mNodePtr->data);
    }

    T & operator*() {
        return mNodePtr->data;
    }

    Node *mNodePtr;
};

template <typename T, typename Alloc = DefaultAllocator>
class SLinkedList {

    using Node = SLinkedListNode<T>;

public:
    using Iterator = SLinkedListIterator<T>;

    Iterator begin() {
        return mHead_e.next;
    }

    Iterator end() {
        return &mHead_e;
    }

public:
    void erase_after(Iterator pos) {
        Node *nodePtr = pos.mNodePtr->next;
        pos.mNodePtr->next = nodePtr->next;

        nodePtr->data.~T();
        Alloc::deallocate(nodePtr, sizeof(Node));
        mSize_e--;

        if (mSize_e == 0) {
            mTailPtr_e = &mHead_e;
        }
    }

    void insert_after(Iterator pos, const T &data) {
        Node *nodePtr = static_cast<Node *>(Alloc::allocate(sizeof(Node)));
        new (&(nodePtr->data)) T(data);

        nodePtr->next = pos.mNodePtr->next;
        pos.mNodePtr->next = nodePtr;
    }

public:

    SLinkedList() : mTailPtr_e { &mHead_e }, mHead_e { &mHead_e, T() } {
        mSize_e = 0;
    }

    SLinkedList(std::initializer_list<T> list) : SLinkedList() {
        for (auto it = list.begin(); it != list.end(); it++) {
            push_back(*it);
        }
    }

    SLinkedList(const SLinkedList &dsObj) : SLinkedList() {
        for (Node *nodePtr = dsObj.mHead_e.next; nodePtr != &(dsObj.mHead_e);) {
            push_back(nodePtr->data);
            nodePtr = nodePtr->next;
        }
        //mTailPtr_e = dsObj.
    }

    SLinkedList(SLinkedList &&dsObj) {
        mHead_e.next = dsObj.mHead_e.next;
        mTailPtr_e = dsObj.mTailPtr_e;
        mSize_e = dsObj.mSize_e;
        mTailPtr_e->next = &mHead_e; // Note

        // reset
        dsObj.mHead_e.next = &(dsObj.mHead_e);
        dsObj.mTailPtr_e = &(dsObj.mHead_e);
        mSize_e = 0;
    }

    SLinkedList & operator=(const SLinkedList &dsObj) {
        if (this != &dsObj) {
            this->~SLinkedList();
            for (Node *nodePtr = dsObj.mHead_e.next; nodePtr != &(dsObj.mHead_e);) {
                push_back(nodePtr->data);
                nodePtr = nodePtr->next;
            }
        }
        return *this;
    }

    SLinkedList & operator=(SLinkedList &&dsObj) {
        if (this != &dsObj) {
            mHead_e.next = dsObj.mHead_e.next;
            mTailPtr_e = dsObj.mTailPtr_e;
            mSize_e = dsObj.mSize_e;
            mTailPtr_e->next = &mHead_e; // Note

            // reset
            dsObj.mHead_e.next = &(dsObj.mHead_e);
            dsObj.mTailPtr_e = &(dsObj.mHead_e);
            mSize_e = 0;
        }
        return *this;
    }

    ~SLinkedList() {
        while (!empty()) {
            Node *nodePtr = mHead_e.next;
            mHead_e.next = nodePtr->next;

            nodePtr->data.~T();
            Alloc::deallocate(nodePtr, sizeof(Node));
            mSize_e--;
        }
        mSize_e = 0;
        mTailPtr_e = &mHead_e;
    }

public:
    bool empty() const {
        return mHead_e.next == &mHead_e;
    }

    int size() const {
        return mSize_e;
    }

    T & front() {
        return mHead_e.next->data;
    }

    T & back() {
        return mTailPtr_e->data;
    }

    T & operator[](int index) {
        Node *nodePtr = mHead_e.next;
        while (index--) {
            nodePtr = nodePtr->next;
        }
        return nodePtr->data;
    }

public:
    void push_back(const T &data) {
        Node *nodePtr = static_cast<Node *>(Alloc::allocate(sizeof(Node)));
        new (&(nodePtr->data)) T(data);

        mTailPtr_e->next = nodePtr;
        nodePtr->next = &mHead_e;

        mTailPtr_e = nodePtr;
        mSize_e++;
    }

    void _pop_back() {
        Node *nodePtr = mHead_e.next;
        while (nodePtr->next != mTailPtr_e) {
            nodePtr = nodePtr->next;
        }

        nodePtr->next = mTailPtr_e->next;
        
        mTailPtr_e->data.~T();
        Alloc::deallocate(mTailPtr_e, sizeof(Node));

        mTailPtr_e = nodePtr;
        mSize_e--;
    }

    void push_front(const T &data) {
        Node *nodePtr = static_cast<Node *>(Alloc::allocate(sizeof(Node)));
        new (&(nodePtr->data)) T(data);

        nodePtr->next = mHead_e.next;
        mHead_e.next = nodePtr;
        mSize_e++;
        if (mSize_e == 1) {
            mTailPtr_e = nodePtr;
        }
    }

    void pop_front() {
        Node *nodePtr = mHead_e.next;
        mHead_e.next = nodePtr->next;
        
        nodePtr->data.~T();
        Alloc::deallocate(nodePtr, sizeof(Node));

        mSize_e--;

        if (empty()) {
            mTailPtr_e = &mHead_e;
        }
    }

private:
    int mSize_e;
    Node *mTailPtr_e;
    Node mHead_e;
};

}

#endif