#pragma once
#include "singletonBase.h"
#include <time.h>

//==================================================================
//		## randomFunction ## (rand()�Լ�)
//==================================================================
class randomFunction : public singletonBase <randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction() {}

	//getInt
	inline int getInt(int num) { return rand() % num; }
	//getFromIntTo => ���ǻ��� 0�� ������ ������
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	//getFloat
	inline float getFloat(float num)
	{
		//(0~32767 / 32767) * �ڱ��ڽ� =  �ڱ��ڽ� ���� �Ҽ�����
		return ((float)rand() / (float)RAND_MAX) * num;
	}
	//getFromFloatTo
	inline float getFromfloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}
};
