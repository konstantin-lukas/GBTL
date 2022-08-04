#ifndef GBSTL_LINKED_LIST_H
#define GBSTL_LINKED_LIST_H

#include <cstddef>
#include <iostream>

namespace gbstl {

    template<typename type> class LinkedList {
        struct Link {
            type value;
            Link* nextLink;
            explicit Link(type val) : value(val), nextLink(nullptr){}
        };
    private:
        Link* m_FirstLink;
        Link* m_currentLink;
        size_t m_Size;
    public:
        LinkedList() : m_FirstLink(nullptr), m_currentLink(nullptr), m_Size(0) {}
        type& getElementAt(unsigned int index) {
            m_currentLink = m_FirstLink;
            if (m_currentLink == nullptr) throw std::out_of_range("linked list is empty");
            if (index >= m_Size) throw std::out_of_range(std::string("index ") + std::to_string(index) + std::string(" is out of range"));
            for (int i = 0; i < index; i++) {
                m_currentLink = m_currentLink->nextLink;
            }
            return m_currentLink->value;
        }
        type& operator[](unsigned int index) {
            return getElementAt(index);
        }
        const type& operator[](unsigned int index) const {
            return getElementAt(index);
        }
        ~LinkedList() {
            Link* garbage = m_FirstLink;
            while (garbage != nullptr) {
                Link* nextLink = garbage->nextLink;
                delete garbage;
                garbage = nextLink;
            }
        }
        void push(type value) {
            if (m_FirstLink == nullptr) {
                m_FirstLink = new Link(value);
            } else {
                m_currentLink = m_FirstLink;
                while (m_currentLink->nextLink != nullptr)
                    m_currentLink = m_currentLink->nextLink;
                m_currentLink->nextLink = new Link(value);
            }
            this->m_Size++;
        }
        // TODO: REMOVE ELEMENT AT
        // TODO: POP
        // TODO: COPY CONSTRUCTOR
        // TODO: EMPTY
        // TODO: CONSTRUCTOR FROM ARRAY
        void print() {
            m_currentLink = m_FirstLink;
            while (m_currentLink != nullptr) {
                std::cout << m_currentLink->value;
                if (m_currentLink->nextLink != nullptr) std::cout << ", ";
                m_currentLink = m_currentLink->nextLink;
            }
            std::cout << std::endl;
        }
        size_t length() { return m_Size; }
    };

}
#endif //GBSTL_LINKED_LIST_H
