#pragma once
#include<cmath>
#include<SFML/Graphics.hpp>

namespace kr
{

	namespace math
	{

		class Vec3
		{
			public:
				float x = 0;
				float y = 0;
				float z = 0;
			public:
				Vec3();
				Vec3(float x, float y, float z);
				sf::Vector3f toSfVec() const;
				Vec3 operator + (const Vec3& other) const;
				Vec3 operator - (const Vec3& other) const;
				Vec3 operator * (const float scaler) const;
				Vec3 operator / (const float devider) const;
				bool operator == (const Vec3& other) const;
				bool operator != (const Vec3& other) const;
				Vec3& operator += (const Vec3& other);
				Vec3& operator -= (const Vec3& other);
				Vec3& operator *= (const float scaler);
				Vec3& operator /= (const float devider);
				bool operator > (const Vec3& other) const;
				bool operator < (const Vec3& other) const;
				bool operator >= (const Vec3& other) const;
				bool operator <= (const Vec3& other) const;
				float len() const;
				Vec3& normalize();
				Vec3 normalized() const;

		};

	}

}



