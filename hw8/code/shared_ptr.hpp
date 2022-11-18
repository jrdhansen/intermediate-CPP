//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// usu NAMESPACE
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace usu
{
    //=======================================================================================================================================================================
    //=======================================================================================================================================================================
    // TEMPLATED shared_ptr CLASS (not for arrays)
    //=======================================================================================================================================================================
    //=======================================================================================================================================================================
    template <typename T>
    // Where T is the data type (e.g. int, double, MyClass) of the object to which we'll be pointing with the shared_ptr.
    class shared_ptr
    {
      public:
        //==== CONSTRUCTORS, DESTRUCTOR ====================
        shared_ptr(T* ptrToObj);                    // overloaded constructor
        shared_ptr(const shared_ptr<T>& ptrToCopy); // copy constructor
        shared_ptr(shared_ptr<T>&& ptrToMove);      // move constructor
        ~shared_ptr();                              // destructor

        //==== OPERATORS ===================================
        shared_ptr<T>& operator=(const shared_ptr& rhs); // assignment operator
        shared_ptr<T>& operator=(shared_ptr&& rhs);      // move assignment operator
        T* operator->();                                 // pointer operator
        T operator*();                                   // dereference operator

        //==== OTHER METHODS ===============================
        T* get();        // returns a ptr to m_ptrToObj
        int use_count(); // returns the reference count

      private:
        //==== PRIVATE DATA MEMBERS ========================
        T* m_ptrToObj;          // raw ptr to "object-of-interest"
        unsigned* m_ptrToRefCt; // raw ptr to reference count
    };

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // FUNCTION IMPLEMENTATIONS FOR TEMPLATED shard_ptr CLASS (not for arrays)
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Overloaded constructor
    template <typename T>
    shared_ptr<T>::shared_ptr(T* ptrToObj) :
        m_ptrToObj(ptrToObj)
    {
        m_ptrToRefCt = new unsigned(1u);
    }

    // Copy constructor
    template <typename T>
    shared_ptr<T>::shared_ptr(const shared_ptr<T>& ptrToCopy)
    {
        // Copy the values of the passed-in ptrToCopy, increment the reference count.
        m_ptrToObj = ptrToCopy.m_ptrToObj;
        m_ptrToRefCt = ptrToCopy.m_ptrToRefCt;
        *m_ptrToRefCt = *m_ptrToRefCt + 1u;
    }

    // Move constructor
    template <typename T>
    shared_ptr<T>::shared_ptr(shared_ptr<T>&& ptrToMove)
    {
        // Move ownership of the ptrToMove to our new shared_ptr
        m_ptrToObj = ptrToMove.m_ptrToObj;
        m_ptrToRefCt = ptrToMove.m_ptrToRefCt;
        // We must do this, otherwise destructor would delete these pointers (since ptrToMove goes out of scope).
        ptrToMove.m_ptrToObj = nullptr;
        ptrToMove.m_ptrToRefCt = nullptr;
    }

    // Destructor
    //          when a shared_ptr goes out of scope the destructor is invoked and
    //          decrements the reference count, if the refCount goes to 0 it cleans up allocated memory.
    template <typename T>
    shared_ptr<T>::~shared_ptr()
    {
        if (m_ptrToRefCt != nullptr)
        {
            *m_ptrToRefCt = *m_ptrToRefCt - 1u;
        }
        if ((m_ptrToRefCt != nullptr) && (*m_ptrToRefCt == 0u))
        {
            delete m_ptrToObj;
            delete m_ptrToRefCt;
            m_ptrToObj = nullptr;
            m_ptrToRefCt = nullptr;
        }
    }

    // Assignment operator
    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& rhs)
    {
        // Make sure LHS != RHS
        if (&rhs != this)
        {
            // Decrement LHS refCount before re-assignment.
            if (m_ptrToRefCt != nullptr)
            {
                *m_ptrToRefCt = *m_ptrToRefCt - 1u;
            }
            // Release memory of LHS if this is last of shared_ptrs for this object.
            if ((m_ptrToRefCt != nullptr) && (*m_ptrToRefCt == 0u))
            {
                delete m_ptrToObj;
                delete m_ptrToRefCt;
                m_ptrToObj = nullptr;
                m_ptrToRefCt = nullptr;
            }
            // Copy RHS into LHS
            m_ptrToObj = rhs.m_ptrToObj;
            m_ptrToRefCt = rhs.m_ptrToRefCt;
            // Increment the new LHS (the passed-in RHS)
            *m_ptrToRefCt = *m_ptrToRefCt + 1u;
        }
        return (*this);
    }

    // Move assignment operator
    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& rhs)
    {
        // Prevent trouble with self-assignment
        if (this != &rhs)
        {
            // Swap ownership of pointers
            std::swap(m_ptrToObj, rhs.m_ptrToObj);
            std::swap(m_ptrToRefCt, rhs.m_ptrToRefCt);
        }
        return (*this);
    }

    // Pointer operator ->
    template <typename T>
    T* shared_ptr<T>::operator->()
    {
        return (m_ptrToObj);
    }

    // Dereference operator *
    template <typename T>
    T shared_ptr<T>::operator*()
    {
        // Return dereferenced m_ptrToObj (what managed raw ptr is pointing to).
        return (*m_ptrToObj);
    }

    // get method
    template <typename T>
    T* shared_ptr<T>::get()
    {
        return (m_ptrToObj);
    }

    // use_count method
    template <typename T>
    int shared_ptr<T>::use_count()
    {
        return (*m_ptrToRefCt);
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // make_shared FUNCTION IMPLEMENTATION (NOT FOR ARRAYS) : provided by Dr. Mathias, performs the raw pointer memory allocation.
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    //=======================================================================================================================================================================
    //=======================================================================================================================================================================
    // TEMPLATED shared_ptr CLASS (specifically for arrays)
    //=======================================================================================================================================================================
    //=======================================================================================================================================================================
    template <typename T>
    // Where T is the data type (e.g. int, double, MyClass) of the array elements to which we'll be pointing with the shared_ptr.
    class shared_ptr<T[]>
    {
      public:
        //==== CONSTRUCTORS, DESTRUCTOR ====================
        shared_ptr(T* ptrToArr, int numElements);     // overloaded constructor
        shared_ptr(const shared_ptr<T[]>& ptrToCopy); // copy constructor
        shared_ptr(shared_ptr<T[]>&& ptrToMove);      // move constructor
        ~shared_ptr();                                // destructor

        //==== OPERATORS ===================================
        shared_ptr<T[]>& operator=(const shared_ptr& rhs); // assignment operator
        shared_ptr<T[]>& operator=(shared_ptr&& rhs);      // move assignment operator
        T& operator[](int index);                          // brackets operator

        //==== OTHER METHODS ===============================
        unsigned size(); // returns number of elements in array
        int use_count(); // returns the reference count

      private:
        //==== PRIVATE DATA MEMBERS ========================
        T* m_ptrToArr;          // raw ptr to first element in "array-of-interest"
        unsigned* m_ptrToRefCt; // raw ptr to reference count
        int m_numElements = 0;  // how many elements are in the array
    };

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // FUNCTION IMPLEMENTATIONS FOR TEMPLATED shard_ptr CLASS (specifically for arrays)
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Overloaded constructor
    template <typename T>
    shared_ptr<T[]>::shared_ptr(T* ptrToArr, int numElements) :
        m_ptrToArr(ptrToArr),
        m_numElements(numElements)
    {
        m_ptrToRefCt = new unsigned(1u);
    }

    // Copy constructor
    template <typename T>
    shared_ptr<T[]>::shared_ptr(const shared_ptr<T[]>& ptrToCopy)
    {
        // Copy the values of the passed-in ptrToCopy, increment the reference count.
        for (int i = 0; i < ptrToCopy.m_numElements; ++i)
        {
            m_ptrToArr[i] = ptrToCopy.m_ptrToArr[i];
        }
        m_ptrToRefCt = ptrToCopy.m_ptrToRefCt;
        *m_ptrToRefCt = *m_ptrToRefCt + 1u;
    }

    // Move constructor (using direct initialization to move pointers)
    template <typename T>
    shared_ptr<T[]>::shared_ptr(shared_ptr<T[]>&& ptrToMove) :
        m_ptrToArr(ptrToMove.m_ptrToArr),
        m_ptrToRefCt(ptrToMove.m_ptrToRefCt)
    {
        // We must do this, otherwise destructor would delete these pointers (since ptrToMove goes out of scope).
        ptrToMove.m_ptrToArr = nullptr;
        ptrToMove.m_ptrToRefCt = nullptr;
    }

    // Destructor
    template <typename T>
    shared_ptr<T[]>::~shared_ptr()
    {
        // Ensure m_ptrToRefCt isn't NULL, then decrement refCount.
        if (m_ptrToRefCt != nullptr)
        {
            *m_ptrToRefCt = *m_ptrToRefCt - 1u;
        }
        // Next, clean up allocated memory when refCount hits 0.
        if ((m_ptrToRefCt != nullptr) && (*m_ptrToRefCt == 0u))
        {
            delete[] m_ptrToArr;
            delete m_ptrToRefCt;
            m_ptrToArr = nullptr;
            m_ptrToRefCt = nullptr;
        }
    }

    // Assignment operator
    template <typename T>
    shared_ptr<T[]>& shared_ptr<T[]>::operator=(const shared_ptr& rhs)
    {
        // Make sure LHS != RHS
        if (&rhs != this)
        {
            // Decrement LHS refCount before re-assignment.
            *m_ptrToRefCt = *m_ptrToRefCt - 1u;
            // Release memory of LHS if this is last of shared_ptrs for this object.
            if ((m_ptrToRefCt != nullptr) && (*m_ptrToRefCt == 0u))
            {
                delete[] m_ptrToArr;
                delete m_ptrToRefCt;
                m_ptrToArr = nullptr;
                m_ptrToRefCt = nullptr;
            }
            // Copy the values of the passed-in rhs into lhs ("this"), increment the reference count.
            for (int i = 0; i < rhs.m_numElements; ++i)
            {
                m_ptrToArr[i] = rhs.m_ptrToArr[i];
            }
            m_ptrToRefCt = rhs.m_ptrToRefCt;
            // Increment the new LHS (the passed-in RHS)
            *m_ptrToRefCt = *m_ptrToRefCt + 1u;
        }
        return (*this);
    }

    // Move assignment operator
    template <typename T>
    shared_ptr<T[]>& shared_ptr<T[]>::operator=(shared_ptr&& rhs)
    {
        // Prevent trouble with self-assignment
        if (this != &rhs)
        {
            // Move ownership of the ptrToMove to our new shared_ptr
            m_ptrToArr = rhs.m_ptrToArr;
            m_ptrToRefCt = rhs.m_ptrToRefCt;
            // We must do this, otherwise destructor would delete these pointers (since ptrToMove goes out of scope).
            rhs.m_ptrToArr = nullptr;
            rhs.m_ptrToRefCt = nullptr;
        }
        return (*this);
    }

    // brackets (indexing) operator
    template <typename T>
    T& shared_ptr<T[]>::operator[](int index)
    {
        // Have this if statement to catch any indices passed that are too large
        // (otherwise we get an error "not all control paths return a value")
        if (index >= m_numElements)
        {
            throw std::out_of_range{"Index " + std::to_string(index) + " is too large"};
        }
        return (m_ptrToArr[index]);
    }

    // size method: returns number of elements in the array
    template <typename T>
    unsigned shared_ptr<T[]>::size()
    {
        return (m_numElements);
    }

    // use_count method: returns the reference count for the shared_ptr
    template <typename T>
    int shared_ptr<T[]>::use_count()
    {
        return (*m_ptrToRefCt);
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // make_shared_array FUNCTION IMPLEMENTATION : provided by Dr. Mathias, performs the raw pointer memory allocation.
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template <typename T, unsigned int N>
    shared_ptr<T[]> make_shared_array()
    {
        return shared_ptr<T[]>(new T[N], N);
    }

} // namespace usu
