#pragma once
#include "gameNode.h"
#include "structure.h"


class enemyTankManager;
class myTank;

class structureManager :
	public gameNode
{
private:
	vector<structure*> _vStructure;
	vector<structure*>::iterator _viStructure;
	vector<structure*>::iterator _viStructure2;

	myTank* _myTank;

	enemyTankManager* _enemyTankManager;

	TCHAR debug[1024];

	TCHAR debug2[1024];

public:

	vector<structure*> get_vStructure() { return _vStructure; }
	vector<structure*>::iterator get_viStructure() { return _viStructure; }
	vector<structure*>::iterator get_viStructure2() { return _viStructure2; }

	void set_vStructure(vector<structure*> vStructure) { _vStructure = vStructure; }
	void set_viStructure(vector<structure*>::iterator viStructure) { _viStructure = viStructure; }
	void set_viStructure2(vector<structure*>::iterator viStructure2) { _viStructure2 = viStructure2; }

	virtual HRESULT init(void);
	virtual HRESULT init(int howMany);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setMyTankMemoryLink(myTank* myTank) { _myTank = myTank; }
	void setMyEnemyManagerLink(enemyTankManager* enemyTankManager);

	void addStructure(int structureType, float x, float y);

	void collisionCheck();

	structureManager();
	~structureManager();
};

