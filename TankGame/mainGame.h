#pragma once
#include "gameNode.h"
#include "startPage.h"
#include "mission1.h"
#include "introductionPage.h"
#include "missionSelect.h"
#include "mission1.h"

class mainGame : public gameNode
{
private:
	startPage* _startPage;
	
	introductionPage* _introductionPage;

	missionSelect* _missionSelect;

	mission1* _mission1;

	int _pageNum = 1;


public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


	mainGame();
	~mainGame();
};

