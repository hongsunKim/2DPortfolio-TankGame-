#pragma once

#include <cmath>

#define DEG_TO_RAD 0.017453f	//1도의 라디안값
#define PI 3.141592f	
#define PI2 (PI * 2)

#define PI_2	(PI / 2)
#define PI_4	(PI / 4)
#define PI_8	(PI / 8)
#define PI_16	(PI / 16)
#define PI_32	(PI / 32)

#define FLOAT_EPSILON 0.0001f	//실수의 대소비교 할때 쓸 녀석

namespace MY_UTIL
{
	//두 점사이 거리
	float getDistance(float startX, float startY, float endX, float endY);

	//두 점사이 각도
	float getAngle(float x1, float y1, float x2, float y2);
}

