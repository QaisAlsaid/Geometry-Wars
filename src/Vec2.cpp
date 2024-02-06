#include "Vec2.hpp"
#define pi 3.14159265359

using namespace kr::math;


Vec2::Vec2(float x, float y) : x(x), y(y) {}


Vec2::Vec2(){}


sf::Vector2f Vec2::toSfVec() const
{
    return sf::Vector2f(x, y);
}


Vec2 Vec2::operator + (const Vec2& other) const
{
    return Vec2(other.x + x, other.y + y);
}


Vec2 Vec2::operator - (const Vec2& other) const
{
    return Vec2(other.x - x, other.y - y);
}


Vec2 Vec2::operator * (const float scaler) const
{
    return Vec2(x * scaler, y * scaler);
}


Vec2 Vec2::operator / (const float devider) const
{
    return Vec2(x / devider, y / devider);
}


bool Vec2::operator == (const Vec2& other) const
{
    return x == other.x && y == other.y;
}


bool Vec2::operator != (const Vec2& other) const
{
    return x != other.x && y != other.y;
}


Vec2& Vec2::operator += (const Vec2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}


Vec2& Vec2::operator -= (const Vec2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}


Vec2& Vec2::operator *= (const float scaler)
{
    x *= scaler;
    y *= scaler;
    return *this;
}


Vec2& Vec2::operator /= (const float devider)
{
    x /= devider;
    y /= devider;
    return *this;
}


bool Vec2::operator > (const Vec2& other) const
{
    return x > other.x && y > other.y;
}


bool Vec2::operator < (const Vec2& other) const
{
    return x < other.x && y < other.y;
}


bool Vec2::operator >= (const Vec2& other) const
{
    return x >= other.x && y >= other.y;
}


bool Vec2::operator <= (const Vec2& other) const
{
    return x <= other.x && y <= other.y;
}


float Vec2::len() const
{
    return std::sqrt(x*x + y*y);
}


Vec2& Vec2::normalize()
{
    *this /= this->len();
    return *this;
}


Vec2 Vec2::normalized() const
{
    return Vec2(x / this->len(), y / this->len());
}


float Vec2::dist(const Vec2& other) const
{
    return Vec2(*this - other).len();
}


float Vec2::angle() const
{
    return std::atan2(y, x);
}


float Vec2::angleDeg() const
{
    return std::atan2(y, x) * 180 / pi;
}

