#pragma once
#include "gameNode.h"
#include "enemyTank.h"

class structrueManager;

class enemyTankManager :
	public gameNode
{

private:
	typedef vector<enemyTank*> vEnemyTank;
	typedef vector<enemyTank*>::iterator viEnemyTank;
	vector<enemyTank*>::iterator _viEnemyTank2;

	myTank* _myTank;
	vEnemyTank  _vEnemyTank;
	viEnemyTank _viEnemyTank;

public:

	vEnemyTank get_vEnemyTank(void) { return _vEnemyTank; }
	viEnemyTank get_viEnemyTank(void) { return _viEnemyTank; }

	void set_vEnemyTank(vEnemyTank vEnemyTank) { _vEnemyTank = vEnemyTank; }
	void set_viEnemyTank(viEnemyTank viEnemyTank) { _viEnemyTank = viEnemyTank; }

	virtual HRESULT init(void);
	virtual HRESULT init(int howMany);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void eraseEnemyTank(void);

	void collisionCheck();

	void setMyTankMemoryLink(myTank* myTank) { _myTank = myTank; }

	enemyTankManager();
	~enemyTankManager();
};

