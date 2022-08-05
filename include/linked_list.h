#ifndef GBSTL_LINKED_LIST_H
#define GBSTL_LINKED_LIST_H

#include <cstddef>
#include <iostream>
#include <memory>

namespace gbstl {

    template<typename type> class LinkedList {
        struct Link {
            type value;
            std::shared_ptr<Link>nextLink;
            explicit Link(type val) : value(val), nextLink(nullptr){}
            explicit Link(type val, std::shared_ptr<Link> next) : value(val), nextLink(next){}
        };
    private:
        std::shared_ptr<Link>mp_FirstLink;
        std::shared_ptr<Link>mp_currentLink;
        size_t m_Length;
    public:
        // CONSTRUCTOR
        LinkedList() : mp_FirstLink(nullptr), mp_currentLink(nullptr), m_Length(0) {}

        // COPY CONSTRUCTOR
        LinkedList(const LinkedList<type> &src) {
            m_Length = src.m_Length;
            mp_FirstLink = std::shared_ptr<Link>(new Link(src.mp_FirstLink->value, src.mp_FirstLink->nextLink));
            mp_currentLink = mp_FirstLink;
            while (mp_currentLink->nextLink != nullptr) {
                mp_currentLink->nextLink = std::shared_ptr<Link>(new Link(mp_currentLink->nextLink->value, mp_currentLink->nextLink->nextLink));
                if (mp_currentLink->nextLink != nullptr) mp_currentLink = mp_currentLink->nextLink;
            }
        }

        // MOVE CONSTRUCTOR
        LinkedList(const LinkedList<type> &&src) noexcept {
            mp_FirstLink = src.mp_FirstLink;
            mp_currentLink = mp_FirstLink;
            m_Length = src.m_Length;
        }
        type& getLinkRefAt(unsigned int index) {
            mp_currentLink = mp_FirstLink;
            if (mp_currentLink == nullptr) throw std::out_of_range("linked list is empty");
            if (index >= m_Length) throw std::out_of_range(std::string("index ") + std::to_string(index) + std::string(" is out of range"));
            for (int i = 0; i < index; i++) {
                mp_currentLink = mp_currentLink->nextLink;
            }
            return mp_currentLink->value;
        }
        type getLinkAt(unsigned int index) {
            return getLinkRefAt(index);
        }
        type& operator[](unsigned int index) {
            return getLinkRefAt(index);
        }
        type operator[](unsigned int index) const {
            return getLinkAt(index);
        }
        void append(type value) {
            if (mp_FirstLink == nullptr) {
                mp_FirstLink = std::shared_ptr<Link>(new Link(value));
            } else {
                mp_currentLink = mp_FirstLink;
                while (mp_currentLink->nextLink != nullptr)
                    mp_currentLink = mp_currentLink->nextLink;
                mp_currentLink->nextLink = std::shared_ptr<Link>(new Link(value));
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
        // TODO INSERT
        // TODO: APPENDARRAY
        // TODO: INSERTARRAY
        // TODO: APPEND
        // TODO: SORT
        // TODO: OPTIMIZE RUN TIME BY CHECKING IF CURRENT LINK IS USABLE FOR FUNCTION
        // TODO: INITIALIZER LIST

        size_t length() { return m_Length; }

        class Iterator {
        public:
            explicit Iterator(std::shared_ptr<Link> ptr) : mp_Ptr(ptr) {}
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
            std::shared_ptr<Link> mp_Ptr;
        };

        Iterator begin() {
            return Iterator(mp_FirstLink);
        }

        Iterator end() {
            return Iterator(nullptr);
        }
    };

}
#endif //GBSTL_LINKED_LIST_H
