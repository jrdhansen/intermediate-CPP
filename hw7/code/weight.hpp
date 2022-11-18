//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PRE-PROCESSOR DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
#include <cstdint>
#include <ratio>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// usu NAMESPACE
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace usu
{
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // TEMPLATED weight CLASS
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template <typename R, typename D = std::uint64_t>
    // Where R is template parameter for the std::ratio describing weight class instance relation to 1 gram.
    // where D is the data type (double, std::uint64_t, etc.) for count of how many units of the given weight type.
    class weight
    {
      public:
        // weight CLASS METHOD DECLARATIONS, SEE DEFINITIONS DIRECTLY BELOW CLASS SCOPE IN THIS SAME FILE.
        // Default constructor, overloaded constructor, count method.
        weight();
        weight(D count);
        D count();

        // Create one alias for the ratio (R) and another alias
        // for the data type of count (D) to expose them for use in the weight_cast function and overloaded operators.
        using expRatio = R;
        using expCountType = D;

      private:
        // Private data members are the m_ratio for this weight and the m_count of how many units of this weight.
        R m_ratio;
        D m_count;
    };

    // weight CLASS METHOD DEFINITIONS (SEE DECLARATIONS ABOVE IN weight CLASS TEMPLATE):
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Default constructor, initializes storage count (m_count) to 0.
    template <typename R, typename D>
    weight<R, D>::weight() :
        m_count(0)
    {
    }
    // Overloaded constructor that accepts count and initializes m_count to count using direct initialization.
    template <typename R, typename D>
    weight<R, D>::weight(D count) :
        m_count(count)
    {
    }
    // Count method returns the count (m_count) for the given weight type.
    template <typename R, typename D>
    D weight<R, D>::count() { return m_count; }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // OVERLOADED + AND - OPERATORS FOR weight CLASS OBJECTS (adds, subtracts the weights for two of the same weight type, e.g. two ounce-types, two gram-types, etc.)
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template <typename W>
    W operator+(W weight1, W weight2)
    {
        auto newCount = weight1.count() + weight2.count();
        W newWeight(newCount);
        return (newWeight);
    }

    template <typename W>
    W operator-(W weight1, W weight2)
    {
        auto newCount = weight1.count() - weight2.count();
        W newWeight(newCount);
        return (newWeight);
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // OVERLOADED * OPERATORS FOR weight CLASS OBJECTS : same function, just with parameter order switched to account for both cases. Multiplies the weight count by scalar.
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template <typename W>
    W operator*(W weight1, double scalar)
    {
        using W_ctType = typename W::expCountType;
        W_ctType newCount = static_cast<W_ctType>((weight1.count()) * scalar);
        W newWeight(newCount);
        return (newWeight);
    }

    template <typename W>
    W operator*(double scalar, W weight1)
    {
        using W_ctType = typename W::expCountType;
        W_ctType newCount = static_cast<W_ctType>(scalar * (weight1.count()));
        W newWeight(newCount);
        return (newWeight);
    }

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // DEFINING TYPE ALIASES FOR: microgram, gram, kilogram, ounce, pound, ton. Used http://www.onlineconversion.com/weight_common.htm to obtain ratios.
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    using microgram = weight<std::ratio<1, 1'000'000>>;
    using gram = weight<std::ratio<1, 1>>;
    using kilogram = weight<std::ratio<1'000, 1>>;
    using ounce = weight<std::ratio<45359237, 1600000>, double>;
    using pound = weight<std::ratio<45'359'237, 100'000>, double>;
    using ton = weight<std::ratio<45'359'237, 50>, double>;

    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // weight_cast FUNCTION IMPLEMENTATION : is used to convert a weight - with weightType and count - to a new weight. E.g can convert [500 ounces] ==> [31.25 pounds] .
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    template <typename newWtType, typename oldWtType>
    newWtType weight_cast(oldWtType oldWtInstance)
    {
        // Extract the numerators and denominators of both the newWtType and the oldWtType, store them as constant integers (we know all ratios are composed only of integers.)
        const int newNumr = newWtType::expRatio::num;
        const int newDenm = newWtType::expRatio::den;
        const int oldNumr = oldWtType::expRatio::num;
        const int oldDenm = oldWtType::expRatio::den;
        // Define aliases for the old and new ratios, use these ratios to determine endRatio to allow conversion from
        // oldWtType to newWtType (using gram conversions for both as intermediate conversion to get endRatio).
        using newRatio = std::ratio<newNumr, newDenm>;
        using oldRatio = std::ratio<oldNumr, oldDenm>;
        using endRatio = std::ratio_divide<newRatio, oldRatio>;
        // Define alias for the data type (e.g. double, std::uint64_t, etc.) of count corresponding to newWtType.
        using newCtType = typename newWtType::expCountType;

        // Determine the count in units of newWtType ("being-converted-to" units), save as correct data type (using alias defined just above).
        auto intermedCount = (static_cast<double>(endRatio::den) / endRatio::num) * oldWtInstance.count();
        newCtType finalCount = static_cast<newCtType>(intermedCount);

        // Initialize and return a weight object of type newWtType (e.g. ounces, grams, etc.) with finalCount.
        newWtType finalWt = weight<std::ratio<newNumr, newDenm>, decltype(finalCount)>(finalCount);
        return (finalWt);
    }
} // namespace usu