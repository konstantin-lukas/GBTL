#ifndef GBSTL_LINKED_LIST_H
#define GBSTL_LINKED_LIST_H

#include <cstddef>
#include <iostream>
#include <memory>

namespace gbstl {

    template<typename type> class LinkedList {
        struct Link {
            type value;
            Link *nextLink;
            explicit Link(type val) : value(val), nextLink(nullptr){}
            explicit Link(type val, Link *next) : value(val), nextLink(next){}
            ~Link() { printf("gaw");}
        };
    private:
        Link *mp_Head = nullptr;
        Link *mp_Tail = nullptr;
        size_t m_Length = 0;
    public:
        // CONSTRUCTOR
        LinkedList() = default;

        // COPY CONSTRUCTOR
        LinkedList(const LinkedList &src) {
            m_Length = src.m_Length;
            mp_Head = new Link(src.mp_Head->value, src.mp_Head->nextLink);
            Link *tmpPtr = mp_Head;
            while (tmpPtr->nextLink != nullptr) {
                tmpPtr->nextLink = new Link(tmpPtr->nextLink->value, tmpPtr->nextLink->nextLink);
                if (tmpPtr->nextLink != nullptr) tmpPtr = tmpPtr->nextLink;
            }
            mp_Tail = tmpPtr;
        }

        // MOVE CONSTRUCTOR
        LinkedList(LinkedList &&src) noexcept {
            mp_Head = src.mp_Head;
            mp_Tail = src.mp_Tail;
            m_Length = src.m_Length;
            src.mp_Head = nullptr;
            src.mp_Tail = nullptr;
            src.m_Length = 0;
        }

        LinkedList& operator=(LinkedList &&src) noexcept {
            if (this != &src) {
                mp_Head = src.mp_Head;
                mp_Tail = src.mp_Tail;
                m_Length = src.m_Length;
                src.mp_Head = nullptr;
                src.mp_Head = nullptr;
                src.m_Length = 0;
            }
            return *this;
        }

        // DESTRUCTOR
        ~LinkedList() { flush(); }

        void flush() {
            Link* garbage = mp_Head;
            while (garbage != nullptr) {
                Link *nextLink = garbage->nextLink;
                delete garbage;
                garbage = nextLink;
            }
            mp_Head = nullptr;
            mp_Tail = nullptr;
            m_Length = 0;
        }

        void pushHead(const type& value) {
            mp_Head = new Link(value, mp_Head);
        }

        void pushTail(const type& value) {
            if (mp_Head == nullptr)
                mp_Head = mp_Tail = new Link(value);
            else {
                mp_Tail->nextLink = new Link(value);
                mp_Tail = mp_Tail->nextLink;
            }
            this->m_Length++;
        }

        void popHead() {
            if (mp_Head == nullptr) return;
            Link *tmpPtr = mp_Head->nextLink;
            delete mp_Head;
            mp_Head = tmpPtr;
        }

        void popTail() {
            if (mp_Head == nullptr) return;
            Link *tmpPtr = mp_Head;
            while (tmpPtr->nextLink != mp_Tail) tmpPtr = tmpPtr->nextLink;
            delete mp_Tail;
            mp_Tail = tmpPtr;
            mp_Tail->nextLink = nullptr;
        }

        // TODO PUSH_POS (OVERLOAD ARRAY)
        // TODO POP_POS (OVERLOAD ARRAY)
        // TODO: CONSTRUCTOR FROM ARRAY
        // TODO: CONCAT
        // TODO: SORT
        // TODO: MERGE
        // TODO: DOCUMENTATION

        [[nodiscard]] size_t length() const { return m_Length; }

        [[nodiscard]] bool isEmpty() const { return mp_Head == nullptr; }

        [[nodiscard]] const type& head() const { return mp_Head->value; }

        [[nodiscard]] const type& tail() const { return mp_Tail->value; }

        class Iterator {
            // TODO: REVERSE ITERATOR
        public:
            explicit Iterator(Link *ptr) : mp_Ptr(ptr) {}
            Iterator& operator++() {
                mp_Ptr = mp_Ptr->nextLink;
                return *this;
            }
            const Iterator operator++(int) {
                Iterator it = *this;
                ++(*this);
                return it;
            }
            type operator*() {
                return this->mp_Ptr->value;
            }
            bool operator!=(const Iterator& it) const {
                return mp_Ptr != it.mp_Ptr;
            }
            bool operator==(const Iterator& it) const {
                return mp_Ptr == it.mp_Ptr;
            }
        private:
            Link *mp_Ptr;
        };

        Iterator begin() {
            return Iterator(mp_Head);
        }

        Iterator end() {
            return Iterator(nullptr);
        }
    };

}
#endif //GBSTL_LINKED_LIST_H