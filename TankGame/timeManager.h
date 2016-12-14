#pragma once
#include "singletonBase.h"
#include "timer.h"
class timeManager :
	public singletonBase<timeManager>
{
private:
	timer* _timer;

public:
	HRESULT init(void);
	void release(void);
	void update(float lock);
	void render(HDC hdc);

	float getElapsedTime(void) const { return _timer->getElapsedTime(); }

	float getWorldTime(void) const { return _timer->getWorldTime(); }

	timeManager();
	~timeManager();
};

