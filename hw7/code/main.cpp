#include "weight.hpp"

#include <iomanip>
#include <iostream>

// ------------------------------------------------------------------
//
// Operator overloading, various constructors, more templates, etc
//
// ------------------------------------------------------------------
int main()
{
    usu::microgram mcg(1000000);
    usu::gram g = usu::weight_cast<usu::gram>(mcg);
    usu::pound lb = usu::weight_cast<usu::pound>(g);
    usu::ounce oz = usu::weight_cast<usu::ounce>(lb);
    usu::ton ton = usu::weight_cast<usu::ton>(lb);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "--- From micrograms ---" << std::endl;
    std::cout << "micrograms : " << mcg.count() << std::endl;
    std::cout << "grams      : " << g.count() << std::endl;
    std::cout << "lbs        : " << lb.count() << std::endl;
    std::cout << "ounces     : " << oz.count() << std::endl;
    std::cout << "tons       : " << ton.count() << std::endl;

    usu::pound somePounds(2000);
    usu::microgram ugFromPounds = usu::weight_cast<usu::microgram>(somePounds);
    usu::gram gramsFromPounds = usu::weight_cast<usu::gram>(somePounds);
    usu::ounce ouncesFromPounds = usu::weight_cast<usu::ounce>(somePounds);
    usu::ton tonsFromPounds = usu::weight_cast<usu::ton>(ouncesFromPounds);

    std::cout << std::endl
              << "--- From pounds ---" << std::endl;
    std::cout << "micrograms : " << ugFromPounds.count() << std::endl;
    std::cout << "grams      : " << gramsFromPounds.count() << std::endl;
    std::cout << "lbs        : " << somePounds.count() << std::endl;
    std::cout << "ounces     : " << ouncesFromPounds.count() << std::endl;
    std::cout << "tons       : " << tonsFromPounds.count() << std::endl;

    std::cout << std::endl
              << "--- Operator Overloading ---" << std::endl;
    {
        usu::pound a(1);
        usu::pound b(0.5);
        usu::pound c = a + b;
        std::cout << std::setprecision(2);
        std::cout << "(pound + pound) : " << a.count() << " + " << b.count() << " = " << c.count();
        std::cout << " ==> grams: " << usu::weight_cast<usu::gram>(c).count() << std::endl;
    }

    {
        usu::pound a(1);
        usu::pound b(0.5);
        usu::pound c = a - b;
        std::cout << std::setprecision(2);
        std::cout << "(pound - pound) : " << a.count() << " - " << b.count() << " = " << c.count();
        std::cout << " ==> grams: " << usu::weight_cast<usu::gram>(c).count() << std::endl;
    }

    {
        usu::pound a(1);
        usu::pound b = a * 2.2;
        usu::pound c = 3.2 * a;
        std::cout << std::setprecision(2);
        std::cout << "(pound * scalar) : " << a.count() << " * 2.2 "
                  << " = " << b.count();
        std::cout << " ==> grams: " << usu::weight_cast<usu::gram>(b).count() << std::endl;

        std::cout << "(scalar * pound) : 3.2 * " << a.count() << " = " << c.count();
        std::cout << " ==> grams: " << usu::weight_cast<usu::gram>(c).count() << std::endl;
    }

    return 0;
}
