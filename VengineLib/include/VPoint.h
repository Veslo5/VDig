#pragma once
#include "raylib-cpp.hpp"

namespace Vengine
{

	class VPoint
	{
	public:

		int x;
		int y;

		VPoint(const VPoint& point) { set(point); }
		VPoint(const Vector2& vec) { set(vec); }
		VPoint(int x, int y) : x(x), y(y) {}
		VPoint(int value) : VPoint{ value,value } {}
		VPoint() : VPoint{ 0,0 } {}

		~VPoint() = default;

		VPoint& operator=(const VPoint& point)
		{
			set(point);
			return *this;
		}

		bool operator==(const VPoint& other) const
		{
			return x == other.x
				&& y == other.y;
		}

		bool operator==(const Vector2& other) const
		{
			return x == other.x
				&& y == other.y;
		}

		Vector2 GetVector() const
		{
			return { static_cast<float>(x),static_cast<float>(y) };
		}

	private:
		inline void set(const VPoint& point) {
			x = point.x;
			y = point.y;
		}

		inline void set(const Vector2& vec) {
			x = static_cast<int>(vec.x);
			y = static_cast<int>(vec.y);
		}
	};

}