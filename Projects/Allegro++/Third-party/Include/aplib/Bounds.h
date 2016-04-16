#ifndef APLIB_BOUNDS
#define APLIB_BOUNDS

/*================================================================================================\\
| Bounds, Limits or Interval between two quantities of the same type
|--------------------------------------------------------------------------------------------------|
| Type T should have a natural order and implement basic arithmetic and comparison operators.
\=================================================================================================*/

#include <algorithm>

// Synonym
template <typename T>
struct Bounds;

// Synonym
template <typename T>
using Limits = Bounds<T>;

// Synonym
template <typename T>
using Interval = Bounds<T>;

template <typename T>
struct Bounds
{
    T Min;
    T Max;

    explicit Bounds<T>() :
        Min(),
        Max()
    {}

    explicit Bounds<T>(T const & i_Min, T const & i_Max) :
        Min(i_Min),
        Max(i_Max)
    {}

    explicit Bounds<T>(Bounds<T> const & i_Other) :
        Min(i_Other.Min),
        Max(i_Other.Max)
    {}

    Bounds<T> & operator = (Bounds<T> const & i_Other)
    {
        Min = i_Other.Min;
        Max = i_Other.Max;
        return *this;
    }

    bool contains(T const & i_Elem) const
    {
        return i_Elem >= Min && i_Elem <= Max;
    }

    T size() const
    {
        return Max - Min;
    }

    T center() const
    {
        return (Max - Min) / 2;
    }

    T clamp(T const & i_Elem) const
    {
        return std::min(std::max(i_Elem, Min), Max);
    }
};

#endif // APLIB_BOUNDS