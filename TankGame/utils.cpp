#include "stdafx.h"
#include "utils.h"

namespace MY_UTIL
{
	//두 점사이 거리
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//두 점사이 각도
	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float dist = sqrtf(x*x + y*y);
		float angle = acos(x / dist);

		if (y > 0) angle = PI2 - angle;

		return angle;
	}
}
