#ifndef APLIB_BOUNDS
#define APLIB_BOUNDS

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
};

#endif // APLIB_BOUNDS