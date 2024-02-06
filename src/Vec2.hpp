#pragma once
#include<cmath>
#include<iostream>
#include<SFML/Graphics.hpp>

namespace kr
{

	namespace math
	{

		class Vec2
		{
			public:
				float x = 0;
				float y = 0;
			public:
				Vec2();
				Vec2(float x, float y);
				sf::Vector2f toSfVec() const;
				Vec2 operator + (const Vec2& other) const;
				Vec2 operator - (const Vec2& other) const;
				Vec2 operator * (const float scaler) const;
				Vec2 operator / (const float devider) const;
				bool operator == (const Vec2& other) const;
				bool operator != (const Vec2& other) const;
				Vec2& operator += (const Vec2& other);
				Vec2& operator -= (const Vec2& other);
				Vec2& operator *= (const float scaler);
				Vec2& operator /= (const float devider);
				bool operator > (const Vec2& other) const;
				bool operator < (const Vec2& other) const;
				bool operator >= (const Vec2& other) const;
				bool operator <= (const Vec2& other) const;
				float len() const;
				Vec2& normalize();
				Vec2 normalized() const;
				float dist(const Vec2& other) const;
				float angle() const;
				float angleDeg() const;

		};

	}

}



