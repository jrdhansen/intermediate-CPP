#include "unique_ptr.hpp"

#include "gtest/gtest.h"
#include <string>
#include <utility> // std::move

class MyClass
{
  public:
    MyClass(std::string name) :
        m_name(name)
    {
    }

    void updateName(std::string name)
    {
        m_name = name;
    }

    std::string m_name;
};

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Constructors, Default)
{
    usu::unique_ptr<int> p1;
    usu::unique_ptr<MyClass> p2;

    EXPECT_EQ(p1.get(), nullptr);
    EXPECT_EQ(p1.get(), nullptr);
}

TEST(Constructors, Overloaded)
{
    auto raw1 = new int(4);
    auto raw2 = new MyClass("Unit Test");
    usu::unique_ptr<int> p1(raw1);
    usu::unique_ptr<MyClass> p2(raw2);

    EXPECT_EQ(raw1, p1.get());
    EXPECT_EQ(raw2, p2.get());
}

TEST(Constructors, Move)
{
    auto raw1 = new int(4);
    usu::unique_ptr<int> p1(raw1);
    usu::unique_ptr<int> p1m = std::move(p1);

    auto raw2 = new MyClass("Unit Test");
    usu::unique_ptr<MyClass> p2(raw2);
    usu::unique_ptr<MyClass> p2m = std::move(p2);

    EXPECT_EQ(p1.get(), nullptr);
    EXPECT_EQ(p1m.get(), raw1);

    EXPECT_EQ(p2.get(), nullptr);
    EXPECT_EQ(p2m.get(), raw2);
}

TEST(Destructors, Destructor)
{
    try
    {
        // Default shouldn't crash when going out of scope
        {
            usu::unique_ptr<int> p1;
        }

        // Overloaded shouldn't crash when going out of scope
        {
            usu::unique_ptr<int> p1 = usu::make_unique<int>(4);
        }
        EXPECT_EQ(true, true);
    }
    catch (...)
    {
        EXPECT_EQ(true, false);
    }
}

TEST(Methods, get)
{
    usu::unique_ptr<int> p1;
    usu::unique_ptr<MyClass> p2;

    EXPECT_EQ(p1.get(), nullptr);
    EXPECT_EQ(p1.get(), nullptr);

    auto raw3 = new int(4);
    auto raw4 = new MyClass("Unit Test");
    usu::unique_ptr<int> p3(raw3);
    usu::unique_ptr<MyClass> p4(raw4);

    EXPECT_EQ(raw3, p3.get());
    EXPECT_EQ(raw4, p4.get());
}

TEST(Methods, release)
{
    usu::unique_ptr<int> p1;
    usu::unique_ptr<MyClass> p2;

    EXPECT_EQ(p1.release(), nullptr);
    EXPECT_EQ(p1.release(), nullptr);

    auto raw3 = new int(4);
    auto raw4 = new MyClass("Unit Test");
    usu::unique_ptr<int> p3(raw3);
    usu::unique_ptr<MyClass> p4(raw4);

    EXPECT_EQ(p3.release(), raw3);
    EXPECT_EQ(p4.release(), raw4);

    EXPECT_EQ(p3.get(), nullptr);
    EXPECT_EQ(p4.get(), nullptr);
}

TEST(Operators, Dereference)
{
    usu::unique_ptr<int> p1 = usu::make_unique<int>(4);
    usu::unique_ptr<double> p2 = usu::make_unique<double>(2.2);

    EXPECT_EQ(*p1, 4);
    EXPECT_EQ(*p2, 2.2);
}

TEST(Operators, Pointer)
{
    usu::unique_ptr<int> p1 = usu::make_unique<int>(4);
    usu::unique_ptr<MyClass> p2 = usu::make_unique<MyClass>("Unit Test");

    EXPECT_EQ(*(p1.operator->()), 4);
    EXPECT_EQ(p2->m_name, "Unit Test");

    p2->updateName("Another Test");
    EXPECT_EQ(p2->m_name, "Another Test");
}

TEST(Operators, Equality)
{
    usu::unique_ptr<int> p1;
    usu::unique_ptr<int> p2;

    usu::unique_ptr<int> p3 = usu::make_unique<int>(4);
    usu::unique_ptr<int> p4 = usu::make_unique<int>(4);

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p3 == p4);
}

TEST(Operators, Inequality)
{
    auto raw1 = new int(4);
    auto raw2 = new int(4);
    usu::unique_ptr<int> p1(raw1);
    usu::unique_ptr<int> p2(raw2);

    auto raw3 = new MyClass("First");
    auto raw4 = new MyClass("First");
    usu::unique_ptr<MyClass> p3(raw3);
    usu::unique_ptr<MyClass> p4(raw4);

    EXPECT_TRUE(p1 != p2);
    EXPECT_TRUE(p3 != p4);
}
