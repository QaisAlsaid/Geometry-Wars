#include "Vec3.hpp"


using namespace kr::math;


Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}


Vec3::Vec3(){}


sf::Vector3f Vec3::toSfVec() const
{
    return sf::Vector3f(x, y, z);
}


Vec3 Vec3::operator + (const Vec3& other) const
{
    return Vec3(other.x + x, other.y + y, other.z + z);
}


Vec3 Vec3::operator - (const Vec3& other) const
{
    return Vec3(other.x - x, other.y - y, other.z - z);
}


Vec3 Vec3::operator * (const float scaler) const
{
    return Vec3(x * scaler, y * scaler, z * scaler);
}


Vec3 Vec3::operator / (const float devider) const
{

    return Vec3 (x / devider, y / devider, z / devider);
}


bool Vec3::operator == (const Vec3& other) const
{
    return x == other.x && y == other.y && z == other.z;
}


bool Vec3::operator != (const Vec3& other) const
{
    return x != other.x && y != other.y, z != other.z;
}


Vec3& Vec3::operator += (const Vec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}


Vec3& Vec3::operator -= (const Vec3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}


Vec3& Vec3::operator *= (const float scaler)
{
    x *= scaler;
    y *= scaler;
    z *= scaler;
    return *this;
}


Vec3& Vec3::operator /= (const float devider)
{
    x /= devider;
    y /= devider;
    z /= devider;
    return *this;
}


bool Vec3::operator > (const Vec3& other) const
{
    return x > other.x && y > other.y && z > other.z;
}


bool Vec3::operator < (const Vec3& other) const
{
    return x < other.x && y < other.y && z < other.z;
}


bool Vec3::operator >= (const Vec3& other) const
{
    return x >= other.x && y >= other.y && z >= other.z;
}


bool Vec3::operator <= (const Vec3& other) const
{
    return x <= other.x && y <= other.y && z <= other.z;
}


float Vec3::len() const
{
    return std::sqrt(x*x + y*y + z*z);
}


Vec3& Vec3::normalize()
{
    *this /= this->len();
    return *this;
}


Vec3 Vec3::normalized() const
{
    return Vec3(x / this->len(), y / this->len(), z / this->len());
}




