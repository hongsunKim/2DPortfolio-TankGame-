#pragma once
#include "gameNode.h"
class hpBar :
	public gameNode
{
private:
	image* _fullHpImage;
	image* _currentHpImage;

	float _fullHp;
	float _currentHp;

	float _x;
	float _y;
public:

	inline void setFullHp(float fullHp) { _fullHp = fullHp; }
	inline void setCurrentHp(float currentHp) { _currentHp = currentHp; }
	inline void setX(float x) { _x = x; }
	inline void setY(float y) { _y = y; }

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	hpBar();
	~hpBar();
};

