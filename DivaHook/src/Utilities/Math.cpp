#define _USE_MATH_DEFINES
#include "Math.h"

namespace DivaHook::Utilities
{
	float ToDegrees(float radians)
	{
		return radians * (180.0f / M_PI);
	}

	float ToRadians(float degrees)
	{
		return (degrees * M_PI) / 180.0f;
	}

	Vec2 GetDirection(float degrees)
	{
		float radians = ToRadians(degrees);
		return Vec2(cos(radians), sin(radians));
	}

	Vec2 PointFromAngle(float degrees, float distance)
	{
		return Vec2(-1 * std::cos(ToRadians(degrees + 90)) * distance, -1 * std::sin(ToRadians(degrees + 90)) * distance);
	}

	float AngleFromPoints(Vec2 p0, Vec2 p1)
	{
		return (float)(std::atan2(p1.Y - p0.Y, p1.X - p0.X) * 180.0 / M_PI) + 90.0f;
	}
}