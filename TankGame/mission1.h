#pragma once
#include "gameNode.h"
#include "myTank.h"
#include "enemyTank.h"
#include "structureManager.h"
#include "structure.h"
#include "enemyTankManager.h"

class mission1 : public gameNode
{
private:

	image* _stage1BG;
	image* _wall;
	image* _tree;
	image* _stone1;
	image* _defender;

	image* _complete;
	image* _gameover;

	myTank* _myTank;

	//enemyTank* _enemyTank;
	enemyTankManager* _enemyTankManager;


	//structure* _structure1;


	image* _targetImage;

	structureManager* _structureManager;

	TCHAR debug[1024];

	int _offsetX = 0;
	int _offsetY = 0;

	int _completeAlpha = 0;
	int _gameoverAlpha = 0;

	int _waitingTime = 0;
	bool _toCollectionPage = false;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//충돌함수
	void collision(void);

	bool getToCollectionPage() { return _toCollectionPage; }
	void setToCollectionPage(bool toCollectionPage) { _toCollectionPage = toCollectionPage; }


	mission1();
	~mission1();
};