#pragma once

#include <cmath>

class Vector2
{
public:

	union
	{
		struct
		{
			float x;
			float y;
		};
		float v[2];
	};

	inline Vector2(void)
		: x(0.0f)
		, y(0.0f)
	{
	}

	/// copy scalar s to all elements of this vector
	inline explicit Vector2(float s)
		: x(s)
		, y(s)
	{
	}

	/// copy the four scalars into the four elements of this vector
	inline Vector2(float _x, float _y)
		: x(_x)
		, y(_y)
	{
	}

	inline float Length(void) const
	{
		return sqrtf(x * x + y * y);
	}

	inline Vector2& Normalize(void)
	{
		const float length = Length();

		x /= length;
		y /= length;

		return *this;
	}

	inline Vector2 Inverse(void) const
	{
		return Vector2(-x, -y);
	}

	inline bool operator==(const Vector2& rhs)
	{
		return (this->x == rhs.x && this->y == rhs.y);
	}

	inline Vector2& operator=(const Vector2& rhs)
	{
		if (this == &rhs)
			return *this;

		x = rhs.x;
		y = rhs.y;

		return *this;
	}

	/// returns the ith component of this vector
	inline float operator[](size_t i) const
	{
		return v[i];
	}

	/// returns the ith component of this vector
	inline float& operator[](size_t i)
	{
		return v[i];
	}

	/// returns the sum of this vector and rhs
	inline Vector2 operator+(const Vector2& rhs) const
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}

	/// returns the difference between this and rhs
	inline Vector2 operator-(const Vector2& rhs) const
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}

	/// returns the element-wise product of this and rhs
	inline Vector2 operator*(const Vector2& rhs) const
	{
		return Vector2(x * rhs.x, y * rhs.y);
	}

	/// returns the quotient of this and rhs
	inline Vector2 operator/(const Vector2& rhs) const
	{
		return Vector2(x / rhs.x, y / rhs.y);
	}

	/// returns the sum of this and scalar s
	inline Vector2 operator+(float s) const
	{
		return Vector2(x + s, y + s);
	}

	/// returns the difference of this and scalar s
	inline Vector2 operator-(float s) const
	{
		return Vector2(x - s, y - s);
	}

	/// returns the product of this and scalar s
	inline Vector2 operator*(float s) const
	{
		return Vector2(x * s, y * s);
	}

	/// returns the quotient of this and scalar s
	inline Vector2 operator/(float s) const
	{
		return Vector2(x / s, y / s);
	}

	/// returns an unary inverted vector of this
	inline Vector2 operator-(void) const
	{
		return Inverse();
	}

	/// adds rhs to this
	inline Vector2& operator+=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	/// subtracts rhs from this
	inline Vector2& operator-=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	/// multiplies this with rhs
	inline Vector2& operator*=(const Vector2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;

		return *this;
	}

	/// divides this by rhs
	inline Vector2& operator/=(const Vector2& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;

		return *this;
	}

	/// adds scalar s to this
	inline Vector2& operator+=(float s)
	{
		x += s;
		y += s;

		return *this;
	}

	/// subtracts scalar s from this
	inline Vector2& operator-=(float s)
	{
		x -= s;
		y -= s;

		return *this;
	}

	/// multiplies this with scalar s
	inline Vector2& operator*=(float s)
	{
		x *= s;
		y *= s;

		return *this;
	}

	/// divides this by scalar s
	inline Vector2& operator/=(float s)
	{
		x /= s;
		y /= s;

		return *this;
	}

	static inline Vector2 Lerp(Vector2 v0, Vector2 v1, float t)
	{
		return v0 * (1 - t) + v1 * t;
	}
};