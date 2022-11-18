// AUTHOR : JARED HANSEN
// DATE   : THURSDAY, 12/05/2019
// CLASS  : CS3460, C++
// ASMT   : HOMEWORK 9, DYNAMIC PRIORITY QUEUE

#pragma once
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ***** NOTE 1 *******
// ********************
// I used code from https://www.techiedelight.com/min-heap-max-heap-implementation-c/ as a starting point for my priority queue (binary max-heap).
// Dr. Mathias said it was okay to use code/resources from outside sources since the focus of the assignment was iterators rather than priority queues.
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ***** NOTE 2 *******
// ********************
// My code compiles with warnings on the g++ compiler. Unfortunately, I simply ran out of time to resolve these errors. Also, it only passes 7/8 unit tests, one test fails.
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace usu
{
    template <typename T, typename PriType = unsigned int>
    class priority_queue
    {
      public:
        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // Type aliases for priority_queue class.
        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
        using priority_type = PriType;
        using value_type = T;
        using size_type = std::size_t;

        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // Struct used to bind together a value and a priority. These pqItem's are the elements comprising the m_pqVector (of this priority_queue class).
        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
        struct pqItem
        {
            pqItem() = default;
            pqItem(value_type val, priority_type pri) :
                value(val),
                priority(pri)
            {
            }
            value_type value;
            priority_type priority;
        };

        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // priority_queue class methods which DO NOT depend upon the iterator class (e.g. don't take an iterator as an argument or have an iterator return type).
        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
        priority_queue() { this->m_pqVector.reserve(0); }
        priority_queue(std::initializer_list<std::pair<value_type, priority_type>> init_list);
        // The five methods directly below implement the proper priority queue data structure (stored in a vector). Started with code from link in NOTE 1 above.
        int parent(int i) { return ((i - 1) / 2); }
        int leftChild(int i) { return ((2 * i + 1)); }
        int rightChild(int i) { return ((2 * i + 2)); }
        void siftDown(unsigned i);
        void siftUp(unsigned i);
        size_type size() { return m_lengthPQ; }
        bool empty() { return (m_lengthPQ == 0); }
        void enqueue(T value, priority_type priority);
        auto dequeue();

        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //---- iterator CLASS
        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // Aliases for iterator class.
        using pointer = std::vector<pqItem>*;
        using ref = pqItem&;
        using iterator_category = std::forward_iterator_tag;

        class iterator : public std::iterator<std::forward_iterator_tag, priority_queue*>
        {
          public:
            // Default constructor.
            iterator() :
                m_pqItemPtr(nullptr),
                m_pos(0)
            {
            }
            // Overloaded constructor: take a pointer to a std::vector<pqItem>.
            iterator(pointer ptr) :
                m_pqItemPtr(ptr),
                m_pos(0)
            {
            }
            // Overloaded constructor: takes a pointer to a std::vector<pqItem> and a position value.
            iterator(pointer ptr, size_type pos) :
                m_pqItemPtr(ptr),
                m_pos(pos)
            {
            }

            iterator(const iterator& obj);            // copy constructor declaration
            iterator(iterator&& obj) noexcept;        // move constructor declaration
            iterator& operator=(const iterator& rhs); // copy assignment operator declaration
            iterator& operator=(iterator&& rhs);      // move assignment operator declaration
            iterator operator++();                    // pre-fix incrementer operator declaration
            iterator operator++(int);                 // post-fix incrementer operator declaration
            size_type getPos() { return m_pos; }      // Accessor for m_pos member
            pointer getPtr() { return m_pqItemPtr; }  // Accessor for m_pqItemPtr member

            // Dereference operator and pointer operator, declarations and implementations
            ref operator*()
            {
                return (((*m_pqItemPtr)[m_pos]));
            }
            pqItem* operator->()
            {
                return (&((*m_pqItemPtr)[m_pos]));
            }

            // Equality operator and inequality operator, declarations and implementations.
            bool operator==(const iterator& rhs)
            {
                return m_pos == rhs.m_pos && m_pqItemPtr == rhs.m_pqItemPtr;
            }
            bool operator!=(const iterator& rhs)
            {
                return !operator==(rhs);
            }

          private:
            // Respectively: stores the position (position in container m_pqVector), stores the pointer (to m_pqVector).
            size_type m_pos;
            pointer m_pqItemPtr;
        };

        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // SET 2 priority_queue CLASS METHODS. METHODS WHICH DEPEND UPON THE iterator CLASS, e.g. TAKE AN iterator AS AN ARGUMENT OR HAVE AN iterator RETURN TYPE.
        //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
        iterator begin()
        {
            return (iterator(&m_pqVector));
        }
        iterator end()
        {
            return (iterator(&m_pqVector, static_cast<int>(size())));
        }
        iterator find(T value);
        void update(iterator i, priority_type priority);

      private:
        // Vector to store PQ elements (pqItem struct instances), counter (m_lengthPQ) to store number of elements in m_pqVector.
        std::vector<pqItem> m_pqVector;
        size_type m_lengthPQ = 0u;
    };

    //------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // SET 1 priority_queue CLASS METHODS IMPLEMENTATIONS (METHODS DON'T DEPEND UPON iterator CLASS. SET 2 METHDOS DO DEPEND UPON iterator CLASS.)
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template <typename T, typename PriType>
    priority_queue<T, PriType>::priority_queue(std::initializer_list<std::pair<value_type, priority_type>> init_list)
    {
        for (auto [val, pri] : init_list)
        {
            this->enqueue(val, pri);
        }
    }

    template <typename T, typename PriType>
    void priority_queue<T, PriType>::siftDown(unsigned i)
    {
        // Recursively moves the pqItem at index i to the correct position (can't violate max-heap tree property)
        unsigned left = leftChild(i);
        unsigned right = rightChild(i);
        unsigned largest = i;
        if (left < size() && m_pqVector[left].priority > m_pqVector[i].priority)
            largest = left;
        if (right < size() && m_pqVector[right].priority > m_pqVector[largest].priority)
            largest = right;
        if (largest != i)
        {
            std::swap(m_pqVector[i], m_pqVector[largest]);
            siftDown(largest);
        }
    }

    template <typename T, typename PriType>
    void priority_queue<T, PriType>::siftUp(unsigned i)
    {
        // Recursively moves the pqItem at index i to the correct position (can't violate max-heap tree property)
        if (i && m_pqVector[parent(i)].priority < m_pqVector[i].priority)
        {
            std::swap(m_pqVector[i], m_pqVector[parent(i)]);
            siftUp(parent(i));
        }
    }

    template <typename T, typename PriType>
    void priority_queue<T, PriType>::enqueue(T value, priority_type priority)
    {
        // Create an instance of pqItem class and push it onto pq vector, increment length of pq.
        pqItem new_pq_item(value, priority);
        m_pqVector.push_back(new_pq_item);
        ++m_lengthPQ;
        // Put this newly-added pqItem into the correct index in the max-heap structure.
        int index = static_cast<int>(m_lengthPQ) - 1u;
        siftUp(index);
        // Resize the pq vector if needed (per formula in assignment description).
        if (m_pqVector.capacity() == size() - 1u)
        {
            size_type new_size = static_cast<size_type>(std::ceil(size() * 1.25 + 1u));
            m_pqVector.resize(new_size);
        }
    }

    template <typename T, typename PriType>
    auto priority_queue<T, PriType>::dequeue()
    {
        if (size() == 0)
        {
            throw new std::out_of_range{"The PQ is empty"};
        }
        else
        {
            // Return the first element of the vector
            auto returnObj = m_pqVector[0];
            // Replace the root of the heap last vector pqItem, remove last item,
            // decrement counter, put new root pqItem into correct index with siftDown.
            m_pqVector[0] = m_pqVector.back();
            m_pqVector.pop_back();
            --m_lengthPQ;
            siftDown(0);
            return (returnObj);
        }
    }

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // SET 2 priority_queue CLASS METHODS. METHODS WHICH DEPEND UPON THE iterator CLASS, e.g. TAKE AN iterator AS AN ARGUMENT OR HAVE AN iterator RETURN TYPE.
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template <typename T, typename PriType>
    typename priority_queue<T, PriType>::iterator priority_queue<T, PriType>::find(T value)
    {
        // Assume the pq doesn't have an item with this value, initialize iterator to end iterator.
        iterator iter = end();
        unsigned valIndex = 0u;
        // Loop through the heap_vec, looking to see if value exists.
        for (auto& item : m_pqVector)
        {
            if (item.value == value)
            {
                pointer same_heapVec = &(this->m_pqVector);
                // If the value exists in pq, create an iterator for it.
                iter = iterator(same_heapVec, valIndex);
                break;
            }
            ++valIndex;
        }
        return (iter);
    }

    template <typename T, typename PriType>
    void priority_queue<T, PriType>::update(iterator i, priority_type priority)
    {
        // Make sure i is in range.
        if (i.getPos() < size() && i.getPos() >= 0)
        {
            // Save the value of the desired pqItem, remove this item from pq, decrement counter.
            T origVal = m_pqVector[i.getPos()].value;
            m_pqVector.erase(m_pqVector.begin() + (i.getPos()));
            --m_lengthPQ;
            // Create and enqueue new pqItem using saved origVal and passed-in priority.
            this->enqueue(origVal, priority);
        }
    }

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // iterator CLASS METHOD IMPLEMENTATIONS
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Copy constructor implementation
    template <typename T, typename PriType>
    priority_queue<T, PriType>::iterator::iterator(const iterator& obj)
    {
        // Copy the position and pointer to the "this" iterator instance.
        this->m_pos = obj.m_pos;
        this->m_pqItemPtr = obj.m_pqItemPtr;
    }

    // Move constructor implementation
    template <typename T, typename PriType>
    priority_queue<T, PriType>::iterator::iterator(iterator&& obj) noexcept
    {
        // Copy the position and pointer to the "this" iterator instance.
        this->m_pos = obj.m_pos;
        this->m_pqItemPtr = obj.m_pqItemPtr;
        // Set the now-moved values to (essentially) null since they've been moved to the "this" iterator instance.
        obj.m_pos = 0;
        obj.m_pqItemPtr = nullptr;
    }

    // Copy assignment implementation
    template <typename T, typename PriType>
    typename priority_queue<T, PriType>::iterator& priority_queue<T, PriType>::iterator::operator=(const iterator& rhs)
    {
        // Copy the position and pointer into the "this" iterator instance, and return the dereferenced "this" (current iterator).
        this->m_pos = rhs.m_pos;
        this->m_pqItemPtr = rhs.m_pqItemPtr;
        return (*this);
    }

    // Move assignment implementation
    template <typename T, typename PriType>
    typename priority_queue<T, PriType>::iterator& priority_queue<T, PriType>::iterator::operator=(iterator&& rhs)
    {
        // Make sure that current iterator pointer ("this") is not the same as the &rhs reference (also a pointer to an iterator).
        // Then swap the position and pointers for "this" and &rhs respectively, returning dereferenced-"this".
        if (this != &rhs)
        {
            std::swap(this->m_pos, rhs.m_pos);
            std::swap(this->m_pqItemPtr, rhs.m_pqItemPtr);
        }
        return (*this);
    }

    // Prefix (++i) incrementation implementation
    template <typename T, typename PriType>
    typename priority_queue<T, PriType>::iterator priority_queue<T, PriType>::iterator::operator++()
    {
        m_pos++;
        return *this;
    }

    // Postfix (i++) incrementation implementation
    template <typename T, typename PriType>
    typename priority_queue<T, PriType>::iterator priority_queue<T, PriType>::iterator::operator++(int)
    {
        iterator i = *this;
        m_pos++;
        return i;
    }

} // namespace usu
