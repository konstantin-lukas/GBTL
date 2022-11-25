#pragma once

#include <cstddef>
#include <iostream>
#include <memory>

namespace gbtl {

    template<typename T> class linked_list {
        struct link {
            T value;
            link *nextLink;
            explicit link(const T &val) : value(val), nextLink(nullptr){}
            explicit link(const T &val, link *next) : value(val), nextLink(next){}
        };
    private:
        link *mp_Front = nullptr;
        link *mp_Back = nullptr;
        size_t m_Size = 0;
    public:

        /**
         * @brief The default constructor creates a list without elements in constant time.
         */
        linked_list() = default;

        linked_list(std::initializer_list<T> init) {
            auto iterator = init.begin();
            if (iterator != init.end()) {
                if (m_Size == 0) {
                    mp_Front = mp_Back = new link(*iterator);
                } else {
                    mp_Back = mp_Back->nextLink = new link(*iterator);
                }
                m_Size++;
                iterator++;
                for (;iterator != init.end(); iterator++) {
                    mp_Back = mp_Back->nextLink = new link(*iterator);
                    m_Size++;
                }
            }
        }

        // COPY CONSTRUCTOR
        linked_list(const linked_list &src) {
            m_Size = src.m_Size;
            mp_Front = new link(src.mp_Front->value, src.mp_Front->nextLink);
            link *tmpPtr = mp_Front;
            while (tmpPtr->nextLink != nullptr) {
                tmpPtr->nextLink = new link(tmpPtr->nextLink->value, tmpPtr->nextLink->nextLink);
                if (tmpPtr->nextLink != nullptr) tmpPtr = tmpPtr->nextLink;
            }
            mp_Back = tmpPtr;
        }

        linked_list& operator=(const linked_list &src) {
            if (this != &src) {
                m_Size = src.m_Size;
                mp_Front = new link(src.mp_Front->value, src.mp_Front->nextLink);
                link *tmpPtr = mp_Front;
                while (tmpPtr->nextLink != nullptr) {
                    tmpPtr->nextLink = new link(tmpPtr->nextLink->value, tmpPtr->nextLink->nextLink);
                    if (tmpPtr->nextLink != nullptr) tmpPtr = tmpPtr->nextLink;
                }
                mp_Back = tmpPtr;
            }
            return *this;
        }

        // MOVE CONSTRUCTOR
        linked_list(linked_list &&src) noexcept {
            mp_Front = src.mp_Front;
            mp_Back = src.mp_Back;
            m_Size = src.m_Size;
            src.mp_Front = nullptr;
            src.mp_Back = nullptr;
            src.m_Size = 0;
        }

        linked_list& operator=(linked_list &&src) noexcept {
            if (this != &src) {
                mp_Front = src.mp_Front;
                mp_Back = src.mp_Back;
                m_Size = src.m_Size;
                src.mp_Front = nullptr;
                src.mp_Front = nullptr;
                src.m_Size = 0;
            }
            return *this;
        }

        // DESTRUCTOR
        ~linked_list() { clear(); }

        void clear() {
            link* garbage = mp_Front;
            while (garbage != nullptr) {
                link *nextLink = garbage->nextLink;
                delete garbage;
                garbage = nextLink;
            }
            mp_Front = nullptr;
            mp_Back = nullptr;
            m_Size = 0;
        }

        void push_front(const T &value) {
            mp_Front = new link(value, mp_Front);
            m_Size++;
        }

        void push_front(const T values[], uint32_t begin, uint32_t end) {
            if (end < begin) throw std::out_of_range("end cannot be smaller than begin");
            link *tmpPtr = mp_Front = new link(values[begin], mp_Front);
            for (uint32_t i = begin + 1; i <= end; ++i) {
                tmpPtr = tmpPtr->nextLink = new link(values[i], tmpPtr->nextLink);
            }
            if (m_Size == 0) mp_Back = tmpPtr;
            m_Size += end - begin + 1;
        }

        void push_back(const T &value) {
            if (m_Size == 0)
                mp_Front = mp_Back = new link(value);
            else {
                mp_Back->nextLink = new link(value);
                mp_Back = mp_Back->nextLink;
            }
            m_Size++;
        }

        void push_back(const T values[], uint32_t begin, uint32_t end) {
            if (end < begin) throw std::out_of_range("end cannot be smaller than begin");
            if (m_Size == 0)
                mp_Front = mp_Back = new link(values[begin]);
            else {
                mp_Back = mp_Back->nextLink = new link(values[begin]);
            }
            for (uint32_t i = begin + 1; i <= end; ++i) {
                mp_Back = mp_Back->nextLink = new link(values[i]);
            }
            m_Size += end - begin + 1;
        }

        void insert(const T& value, uint32_t pos) {
            if (pos > m_Size - 1) throw std::out_of_range("specified position is out of range");
            if (m_Size == 0) {
                mp_Front = mp_Back = new link(value);
                m_Size = 1;
            } else {
                if (pos == 0) {
                    mp_Front = new link(value, mp_Front);
                } else if (pos == m_Size - 1) {
                    mp_Back->nextLink = new link(value);
                    mp_Back = mp_Back->nextLink;
                } else {
                    link *tmpPtr = mp_Front;
                    for (uint32_t i = 1; i < pos; i++) tmpPtr = tmpPtr->nextLink;
                    tmpPtr->nextLink = new link(value, tmpPtr->nextLink);
                }
                m_Size++;
            }
        }

        void insert(const T values[], uint32_t pos, uint32_t begin, uint32_t end) {
            if (pos > m_Size - 1) throw std::out_of_range("specified position is out of range");
            if (end < begin) throw std::out_of_range("end cannot be smaller than begin");
            link *tmpPtr;
            if (m_Size == 0) {
                tmpPtr = mp_Front = new link(values[begin]);
                mp_Back = tmpPtr;
            } else {
                if (pos == 0) {
                    tmpPtr = mp_Front = new link(values[begin], mp_Front);
                } else {
                    tmpPtr = mp_Front;
                    for (uint32_t i = 1; i < pos; ++i) tmpPtr = tmpPtr->nextLink;
                    tmpPtr = tmpPtr->nextLink = new link(values[begin], tmpPtr->nextLink);
                }
            }
            for (uint32_t i = begin + 1; i <= end; ++i) {
                tmpPtr = tmpPtr->nextLink = new link(values[i], tmpPtr->nextLink);
            }
            if (pos == m_Size - 1) mp_Back = tmpPtr;
            m_Size += end - begin + 1;
        }

        void pop_front() {
            if (m_Size == 0) return;
            if (m_Size == 1) {
                delete mp_Front;
                mp_Front = mp_Back = nullptr;
                m_Size = 0;
            } else {
                link *tmpPtr = mp_Front->nextLink;
                delete mp_Front;
                m_Size--;
                mp_Front = tmpPtr;
            }
        }

        void pop_back() {
            if (m_Size == 0) return;
            if (m_Size == 1) {
                delete mp_Front;
                mp_Front = mp_Back = nullptr;
                m_Size = 0;
            } else {
                link *tmpPtr = mp_Front;
                while (tmpPtr->nextLink != mp_Back) tmpPtr = tmpPtr->nextLink;
                delete mp_Back;
                mp_Back = tmpPtr;
                m_Size--;
            }
        }

        // TODO: POP_POS (OVERLOAD ARRAY)
        // TODO: CONCAT
        // TODO: SORT
        // TODO: MERGE
        // TODO: EMPLACE
        // TODO: DOCUMENTATION

        [[nodiscard]] size_t size() const { return m_Size; }

        [[nodiscard]] bool empty() const { return mp_Front == nullptr; }

        [[nodiscard]] const T& front() const {
            if (mp_Front == nullptr) return NULL;
            return mp_Front->value;
        }

        [[nodiscard]] const T& back() const {
            if (mp_Back == nullptr) return NULL;
            return mp_Back->value;
        }

        class iterator {
            // TODO: REVERSE ITERATOR
        public:
            explicit iterator(link *ptr) : mp_Ptr(ptr) {}
            iterator& operator++() {
                mp_Ptr = mp_Ptr->nextLink;
                return *this;
            }
            const iterator operator++(int) {
                iterator it = *this;
                ++(*this);
                return it;
            }
            T operator*() {
                return this->mp_Ptr->value;
            }
            bool operator!=(const iterator& it) const {
                return mp_Ptr != it.mp_Ptr;
            }
            bool operator==(const iterator& it) const {
                return mp_Ptr == it.mp_Ptr;
            }
        private:
            link *mp_Ptr;
        };

        iterator begin() {
            return iterator(mp_Front);
        }

        iterator end() {
            return iterator(nullptr);
        }

        friend std::ostream& operator<< (std::ostream& stream, const linked_list& list) {
            link* link = list.mp_Front;
            stream << "[";
            while (link != nullptr) {
                stream << link->value;
                link = link->nextLink;
                if (link != nullptr)
                    stream << ", ";
            }
            stream << "]";
            return stream;
        }
    };

}
