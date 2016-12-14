#pragma once
#include "gameNode.h"
class missile :
	public gameNode
{
private:
	image* _missileImage;
	image* _targetImage;
	image* _explosionImage;
	float _fireX;
	float _fireY;
	float _x;
	float _y;
	float _targetX;
	float _targetY;
	float _angle;
	float _range;
	float _speed;
	bool _fire;
	bool _explode;
	int _explosionCount = 0;
	float _scale;

	TCHAR debug[1024];

public:

	inline float getX() { return _x; }
	inline float getY() { return _y; }
	inline float getFireX() { return _fireX; }
	inline float getFireY() { return _fireY; }
	inline float getTargetX() { return _targetX; }
	inline float getTargetY() { return _targetY; }
	inline float getRange() { return _range; }

	int getExplosionFrame();


	virtual HRESULT init(void);
	virtual HRESULT init(float x, float y, float angle, float range, float speed);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void earthquake(void);

	missile();
	~missile();
};
