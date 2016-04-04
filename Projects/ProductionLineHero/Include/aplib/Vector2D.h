#ifndef APLIB_VECTOR_2D
#define APLIB_VECTOR_2D

// aplib
#include <aplib/Direction2D.h>

// std
#include <sstream>

template <typename T>
struct Vector2D
{
    T x;
    T y;

    Vector2D<T>() 
    {

    }

    Vector2D<T>(T i_X, T i_Y) : 
        x(i_X), 
        y(i_Y)
    {
        
    }

    Vector2D<T>(Vector2D<T> const & i_Other) : 
        x(i_Other.x), 
        y(i_Other.y)
    {
        
    }

    template <typename U>
    operator Vector2D<U>() const
    {
        return Vector2D<U>(x, y);
    }

    Vector2D<T> & operator += (Vector2D<T> const & i_Other)
    {
        x += i_Other.x;
        y += i_Other.y;
        return *this;
    }

    Vector2D<T> & operator -= (Vector2D<T> const & i_Other)
    {
        x -= i_Other.x;
        y -= i_Other.y;
        return *this;
    }

    Vector2D<T> &  operator *= (Vector2D<T> const & i_Other)
    {
        x *= i_Other.x;
        y *= i_Other.y;
        return *this;
    }

    Vector2D<T> & operator /= (Vector2D<T> const & i_Other)
    {
        x /= i_Other.x;
        y /= i_Other.y;
        return *this;
    }
    
    Vector2D<T> & operator += (T const & i_Factor)
    {
        x += i_Factor;
        y += i_Factor;
        return *this;
    }

    Vector2D<T> & operator -= (T const & i_Factor)
    {
        x -= i_Factor;
        y -= i_Factor;
        return *this;
    }

    Vector2D<T> & operator *= (T const & i_Factor)
    {
        x *= i_Factor;
        y *= i_Factor;
        return *this;
    }

    Vector2D<T> & operator /= (T const & i_Factor)
    {
        x /= i_Factor;
        y /= i_Factor;
        return *this;
    }

    Vector2D<T> & operator %= (T const & i_Factor)
    {
        x %= i_Factor;
        y %= i_Factor;
        return *this;
    }

    bool operator < (Vector2D<T> const & i_Other) const
    {
        return x < i_Other.x && y < i_Other.y;
    }

    bool operator <= (Vector2D<T> const & i_Other) const
    {
        return x <= i_Other.x && y <= i_Other.y;
    }

    bool operator > (Vector2D<T> const & i_Other) const
    {
        return x > i_Other.x && y > i_Other.y;
    }

    bool operator >= (Vector2D<T> const & i_Other) const
    {
        return x >= i_Other.x && y >= i_Other.y;
    }

    bool operator == (Vector2D<T> const & i_Other) const
    {
        return x == i_Other.x && y == i_Other.y;
    }

    bool operator != (Vector2D<T> const & i_Other) const
    {
        return x != i_Other.x || y != i_Other.y;
    }

    T area() const
    {
        return x * y;
    }

    Vector2D<T> & increment(Dir2DWithDiag i_Dir)
    {
        switch (i_Dir) {
        case Dir2DWithDiag::LEFT:        x -= 1;         break;
        case Dir2DWithDiag::RIGHT:       x += 1;         break;
        case Dir2DWithDiag::UP:                  y -= 1; break;
        case Dir2DWithDiag::DOWN:                y += 1; break;
        case Dir2DWithDiag::UPPER_LEFT:  x -= 1; y -= 1; break;
        case Dir2DWithDiag::UPPER_RIGHT: x += 1; y -= 1; break;
        case Dir2DWithDiag::LOWER_LEFT:  x -= 1; y += 1; break;
        case Dir2DWithDiag::LOWER_RIGHT: x += 1; y += 1; break;
        }
        return *this;
    }

    T norm() const
    {
        return sqrt(x * x + y * y);
    }

    T normSqr() const
    {
        return x * x + y * y;
    }

    Vector2D<T> & normalize()
    {
        T l = norm();
        x /= l;
        y /= l;
        return *this;
    }

    T distanceTo(Vector2D<T> const & i_Other) const
    {
        return (i_Other - *this).norm();
    }

    std::string toString() const
    {
        std::stringstream ss;
        ss << "(" << x << ", " << y << ")";
        return ss.str();
    }
};

template <typename T>
Vector2D<T> operator + (Vector2D<T> const & i_Vec, T i_Factor)
{
    return Vector2D<T>(i_Vec) += i_Factor;
}

template <typename T>
Vector2D<T> operator - (Vector2D<T> const & i_Vec, T i_Factor)
{
    return Vector2D<T>(i_Vec) -= i_Factor;
}

template <typename T>
Vector2D<T> operator - (Vector2D<T> const & i_Vec)
{
    return Vector2D<T>(i_Vec) *= -1;
}

template <typename T>
Vector2D<T> operator * (Vector2D<T> const & i_Vec, T i_Factor)
{
    return Vector2D<T>(i_Vec) *= i_Factor;
}

template <typename T>
Vector2D<T> operator / (Vector2D<T> const & i_Vec, T i_Factor)
{
    return Vector2D<T>(i_Vec) /= i_Factor;
}

template <typename T>
Vector2D<T> operator + (Vector2D<T> const & i_VecA, Vector2D<T> const & i_VecB)
{
    return Vector2D<T>(i_VecA) += i_VecB;
}

template <typename T>
Vector2D<T> operator - (Vector2D<T> const & i_VecA, Vector2D<T> const & i_VecB)
{
    return Vector2D<T>(i_VecA) -= i_VecB;
}

template <typename T>
Vector2D<T> operator * (Vector2D<T> const & i_VecA, Vector2D<T> const & i_VecB)
{
    return Vector2D<T>(i_VecA) *= i_VecB;
}

template <typename T>
Vector2D<T> operator / (Vector2D<T> const & i_VecA, Vector2D<T> const & i_VecB)
{
    return Vector2D<T>(i_VecA) /= i_VecB;
}

template <typename T>
Vector2D<T> operator % (Vector2D<T> const & i_VecA, Vector2D<T> const & i_VecB)
{
    return Vector2D<T>(i_VecA) %= i_VecB;
}

template <typename T>
bool operator == (Vector2D<T> const & i_VecA, Vector2D<T> const & i_VecB)
{
    return i_VecA.x == i_VecB.x && i_VecA.y == i_VecB.y;
}

template <typename T>
Vector2D<T> incremented(Vector2D<T> const & i_Vec, Dir2DWithDiag i_Dir)
{
    return Vector2D<T>(i_Vec).increment(i_Dir);
}

template <typename T>
Vector2D<T> normalized(Vector2D<T> const & i_Vec)
{
    return Vector2D<T>(i_Vec).normalize();
}

#endif // APLIB_VECTOR_2D