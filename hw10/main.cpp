#include "unique_ptr.hpp"

#include <iostream>
#include <memory>

void demoUniquePointer();

// ------------------------------------------------------------------
//
// usu::unique_ptr final test
//
// ------------------------------------------------------------------
int main()
{
    demoUniquePointer();

    return 0;
}

void demoUniquePointer()
{
    std::unique_ptr<int> p1 = std::make_unique<int>(10);
    usu::unique_ptr<int> p2 = usu::make_unique<int>(10);

    // TEST: Uncomment the following lines, they should cause a compiler error!
    //std::unique_ptr<int> p1b = p1; // Causes a compile error (and it should)
    //usu::unique_ptr<int> p2b = p2; // Causes a compile error (and it should)

    std::cout << "from *p1 : " << *p1 << std::endl;
    std::unique_ptr<int> p3;
    p3 = std::move(p1);
    // TEST: Uncomment the following line, it should cause a runtime error!
    //std::cout << *p1 << std::endl;    // Causes a runtime error (and it should)
    std::cout << "from *p3 : " << *p3 << std::endl;

    std::cout << "from *p2 : " << *p2 << std::endl;
    usu::unique_ptr<int> p4;
    p4 = std::move(p2);
    std::cout << "from *p4 : " << *p4 << std::endl;
    // TEST: Uncomment the following line, it should cause a runtime error!
    //std::cout << *p2 << std::endl;    // Causes a runtime error (and it should)
}