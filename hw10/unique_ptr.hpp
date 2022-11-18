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
    // TEMPLATED unique_ptr CLASS
    //=======================================================================================================================================================================
    //=======================================================================================================================================================================
    template <typename T>
    // Where T is the data type (e.g. int, double, MyClass) of the object to which we'll be pointing with the unique_ptr.
    class unique_ptr
    {
      public:
        //==== CONSTRUCTORS, DESTRUCTOR ====================
        unique_ptr();                                        // Default constructor
        unique_ptr(T* ptrToObj);                             // Overloaded constructor
        unique_ptr(const unique_ptr<T>& ptrToCopy) = delete; // Deleted copy constructor
        unique_ptr(unique_ptr<T>&& ptrToMove);               // Move constructor
        ~unique_ptr();                                       // Destructor

        //==== OPERATORS ===================================
        unique_ptr<T>& operator=(const unique_ptr& rhs) = delete; // Deleted copy assignment operator
        unique_ptr<T>& operator=(unique_ptr&& rhs);               // move assignment operator
        T operator*();                                            // dereference operator
        T* operator->();                                          // pointer operator
        // == operator
        bool operator==(const unique_ptr& rhs)
        {
            return (m_ptrToObj == rhs.m_ptrToObj);
        }
        // != operator
        bool operator!=(const unique_ptr& rhs)
        {
            return (m_ptrToObj != rhs.m_ptrToObj);
        }

        //==== OTHER METHODS ===============================
        T* get() const { return (m_ptrToObj); }
        T* release(); // Releases ownership of the raw pointer from unique_ptr, returns raw ptr as return value.

      private:
        //==== PRIVATE DATA MEMBERS ========================
        T* m_ptrToObj; // raw ptr to "object-of-interest"
    };

    // Default constructor
    template <typename T>
    unique_ptr<T>::unique_ptr() :
        m_ptrToObj(nullptr)
    {
    }

    // Overloaded constructor
    template <typename T>
    unique_ptr<T>::unique_ptr(T* ptrToObj) :
        m_ptrToObj(ptrToObj)
    {
    }

    // Move constructor
    template <typename T>
    unique_ptr<T>::unique_ptr(unique_ptr<T>&& ptrToMove)
    {
        // Move ownership of the ptrToMove to our new unique_ptr
        m_ptrToObj = ptrToMove.m_ptrToObj;
        // We must do this, otherwise destructor would delete this pointer (since ptrToMove goes out of scope).
        ptrToMove.m_ptrToObj = nullptr;
    }

    // Destructor
    template <typename T>
    unique_ptr<T>::~unique_ptr()
    {
        delete m_ptrToObj;
        m_ptrToObj = nullptr;
    }

    // Move assignment operator
    template <typename T>
    unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& rhs)
    {
        // Prevent trouble with self-assignment, then swap ownership of pointer
        if (this != &rhs)
        {
            std::swap(m_ptrToObj, rhs.m_ptrToObj);
        }
        return (*this);
    }

    // Dereference operator *
    template <typename T>
    T unique_ptr<T>::operator*()
    {
        // Return dereferenced m_ptrToObj (what managed raw ptr is pointing to).
        return (*m_ptrToObj);
    }

    // Pointer operator ->
    template <typename T>
    T* unique_ptr<T>::operator->()
    {
        return (m_ptrToObj);
    }

    // Release method
    template <typename T>
    T* unique_ptr<T>::release()
    {
        T* releasedPtr = this->m_ptrToObj;
        this->m_ptrToObj = nullptr;
        return (releasedPtr);
    }

    /*
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // TEMPLATED == AND != OPERATORS OUTSIDE OF THE unique_ptr CLASS
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

    // ***** NOTE ******
    // I tried using these as templated methods outside of the unique_ptr class, but could only get == and != to work as member methods of the unique_ptr class (see above).

    // Equality operator ==
    template <typename T>
    bool operator==(unique_ptr<T> ptr1, unique_ptr<T> ptr2)
    {
        return (ptr1.m_ptrToObj == ptr2.m_ptrToObj);
    }

    // Inequality operator !=
    template <typename T>
    bool operator!=(unique_ptr<T> ptr1, unique_ptr<T> ptr2)
    {
        return (ptr1.m_ptrToObj != ptr2.m_ptrToObj);
    }
    */

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // make_shared FUNCTION IMPLEMENTATION (NOT FOR ARRAYS) : provided by Dr. Mathias
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template <typename T, typename... Args>
    unique_ptr<T> make_unique(Args&&... args)
    {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

} // namespace usu
