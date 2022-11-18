#include "weight.hpp"

#include "gtest/gtest.h"
#include <cstdint>
#include <ratio>

constexpr auto kEpsilon = 1E-6;

using TestWeight = usu::weight<std::ratio<2, 1>, std::uint32_t>;
using BigWeight = usu::weight<std::ratio<4, 1>, std::uint32_t>;
using SmallWeight = usu::weight<std::ratio<1, 3>, std::uint32_t>;

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Weight_Constructor, DefaultInitializesCountToZero)
{
    TestWeight weight;

    ASSERT_EQ(0u, weight.count());
}

TEST(Weight_Constructor, OverloadedConstructorInitializesCount)
{
    TestWeight weight1(12);
    ASSERT_EQ(12u, weight1.count());

    TestWeight weight2(44);
    ASSERT_EQ(44u, weight2.count());
}

TEST(Weight_Operator, CanAddOtherWeight)
{
    TestWeight weight1(11);
    TestWeight weight2(4);

    TestWeight result = weight1 + weight2;
    ASSERT_EQ(15u, result.count());
    ASSERT_EQ(11u, weight1.count());
    ASSERT_EQ(4u, weight2.count());

    result = weight1 + TestWeight(0);
    ASSERT_EQ(11u, result.count());
    ASSERT_EQ(11u, weight1.count());
}

TEST(Weight_Operator, CanSubtractOtherWeight)
{
    TestWeight weight1(11);
    TestWeight weight2(4);

    TestWeight result = weight1 - weight2;
    ASSERT_EQ(7u, result.count());
    ASSERT_EQ(11u, weight1.count());
    ASSERT_EQ(4u, weight2.count());

    result = weight1 - TestWeight(0);
    ASSERT_EQ(11u, result.count());
    ASSERT_EQ(11u, weight1.count());
}

TEST(Weight_Operator, CanMultiplyScalarWeight)
{
    TestWeight myWeight(14);

    TestWeight result = 3 * myWeight;
    ASSERT_EQ(3u * 14u, result.count());
    ASSERT_EQ(14u, myWeight.count());
}

TEST(Weight_Operator, CanMultiplyWeightScalar)
{
    TestWeight myWeight(4);

    TestWeight result = myWeight * 5;
    ASSERT_EQ(4u * 5u, result.count());
    ASSERT_EQ(4u, myWeight.count());
}

TEST(Weight_Cast, CanDoIdentityCast)
{
    usu::weight<std::ratio<5, 1>> weight1(10); // 50 units
    decltype(weight1) result1 = usu::weight_cast<decltype(weight1)>(weight1);

    ASSERT_EQ(10u, weight1.count());
    ASSERT_EQ(10u, result1.count());

    usu::weight<std::ratio<1, 2>> weight2(5); // 2.5 units
    decltype(weight2) result2 = usu::weight_cast<decltype(weight2)>(weight2);

    ASSERT_EQ(5u, weight2.count());
    ASSERT_EQ(5u, result2.count());
}

TEST(Weight_Cast, CanCastToSmallerUnit)
{
    BigWeight bigWeight(15);

    auto result = usu::weight_cast<SmallWeight>(bigWeight);

    ASSERT_EQ(15u, bigWeight.count());
    ASSERT_EQ(180u, result.count());
}

TEST(Weight_Cast, CanCastToLargerUnit)
{
    SmallWeight smallWeight(24);

    auto result = usu::weight_cast<BigWeight>(smallWeight);

    ASSERT_EQ(24u, smallWeight.count());
    ASSERT_EQ(2u, result.count());
}

TEST(Weight_Cast, CanCastToLargerUnitWithPrecisionLoss)
{
    SmallWeight smallWeight(39);

    auto result = usu::weight_cast<BigWeight>(smallWeight);

    ASSERT_EQ(39u, smallWeight.count());
    ASSERT_EQ(3u, result.count());
}

TEST(Weight_Cast, CanCastToLargerUnitWithoutPrecisionLoss)
{
    usu::weight<std::ratio<1, 3>, double> smallWeight(39);

    auto result = usu::weight_cast<usu::weight<std::ratio<4, 1>, double>>(smallWeight);

    ASSERT_EQ(39u, smallWeight.count());
    ASSERT_NEAR(3.25, result.count(), kEpsilon);
}

TEST(Weight_Cast, CanCastToLargerUnitWithoutPrecisionLossDifferentStorageTypes)
{
    usu::weight<std::ratio<1, 3>, std::uint32_t> smallWeight(39);

    auto result = usu::weight_cast<usu::weight<std::ratio<4, 1>, double>>(smallWeight);

    ASSERT_EQ(39u, smallWeight.count());
    ASSERT_NEAR(3.25, result.count(), kEpsilon);
}
