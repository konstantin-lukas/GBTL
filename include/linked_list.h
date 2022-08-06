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
        };
    private:
        Link *mp_Head;
        Link *mp_InternalPtr;
        size_t m_Length = 0;
    public:
        // CONSTRUCTOR
        LinkedList() : mp_Head(nullptr), mp_InternalPtr(nullptr) {};

        // COPY CONSTRUCTOR
        LinkedList(const LinkedList &src) {
            m_Length = src.m_Length;
            mp_Head = new Link(src.mp_Head->value, src.mp_Head->nextLink);
            mp_InternalPtr = mp_Head;
            while (mp_InternalPtr->nextLink != nullptr) {
                mp_InternalPtr->nextLink = new Link(mp_InternalPtr->nextLink->value, mp_InternalPtr->nextLink->nextLink);
                if (mp_InternalPtr->nextLink != nullptr) mp_InternalPtr = mp_InternalPtr->nextLink;
            }
        }

        // MOVE CONSTRUCTOR
        LinkedList(LinkedList &&src) noexcept {
            mp_Head = src.mp_Head;
            mp_InternalPtr = mp_Head;
            m_Length = src.m_Length;
            src.mp_Head = nullptr;
            src.mp_InternalPtr = nullptr;
            src.m_Length = 0;
        }

        LinkedList& operator=(LinkedList &&src) noexcept {
            if (this != &src) {
                mp_Head = src.mp_Head;
                mp_InternalPtr = mp_Head;
                m_Length = src.m_Length;
                src.mp_Head = nullptr;
                src.mp_InternalPtr = nullptr;
                src.m_Length = 0;
            }
            return *this;
        }

        // DESTRUCTOR
        ~LinkedList() {
            Link* garbage = mp_Head;
            while (garbage != nullptr) {
                Link* nextLink = garbage->nextLink;
                delete garbage;
                garbage = nextLink;
            }
        }
        type& getLinkAt(unsigned int index) {
            mp_InternalPtr = mp_Head;
            if (mp_InternalPtr == nullptr) throw std::out_of_range("linked list is empty");
            if (index >= m_Length) throw std::out_of_range(std::string("index ") + std::to_string(index) + std::string(" is out of range"));
            for (int i = 0; i < index; i++) {
                mp_InternalPtr = mp_InternalPtr->nextLink;
            }
            return mp_InternalPtr->value;
        }
        const type& getLinkAt(unsigned int index) const {
            return getLinkAt(index);
        }
        type& operator[](unsigned int index) {
            return getLinkAt(index);
        }
        const type& operator[](unsigned int index) const {
            return getLinkAt(index);
        }
        void append(const type& value) {
            if (mp_Head == nullptr) {
                mp_Head = new Link(value);
            } else {
                mp_InternalPtr = mp_Head;
                while (mp_InternalPtr->nextLink != nullptr)
                    mp_InternalPtr = mp_InternalPtr->nextLink;
                mp_InternalPtr->nextLink = new Link(value);
            }
            this->m_Length++;
        }
        // TODO: ITERATOR

        // TODO: REMOVE ELEMENT AT
        // TODO: EMPTY
        // TODO: CONSTRUCTOR FROM ARRAY
        // TODO: DOUBLY LINKED LIST
        // TODO: GET INDEX OF
        // TODO: COUNT
        // TODO: TAIL MEMBER
        // TODO INSERT
        // TODO: APPENDARRAY
        // TODO: INSERTARRAY
        // TODO: APPEND
        // TODO: SORT
        // TODO: OPTIMIZE RUN TIME BY CHECKING IF CURRENT LINK IS USABLE FOR FUNCTION
        // TODO: INITIALIZER LIST

        [[nodiscard]] size_t length() const { return m_Length; }

        class Iterator {
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