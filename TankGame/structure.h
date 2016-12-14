#pragma once
#include "gameNode.h"

class enemyTankManager;
class enemyTank;

class structure :
	public gameNode
{
private:

	int _structureType;
	float _x;
	float _y;
	RECT _rect;

	enemyTankManager* _enemyTankManager;

	TCHAR debug[1024];

public:

	inline float getX() { return _x; }
	inline float getY() { return _y; }
	RECT getRect() { return _rect; }

	inline void setX(float x) { _x = x; }
	inline void setY(float y) { _y = y; }

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setEnemyTankManagerLink(enemyTankManager* enemyTankManager){_enemyTankManager = enemyTankManager;}

	void setStructure(int sturctureType, float x, float y) { _structureType = sturctureType, _x = x, _y = y; }

	void collisionCheck(void);

	structure();
	~structure();
};

