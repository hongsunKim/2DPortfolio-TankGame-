#pragma once
#include "gameNode.h"
class introductionPage :
	public gameNode
{
	image* _howToPlay;

	bool _turnOn = false;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	bool getTurnOn() { return _turnOn; }
	void setTurnOn(bool turnOn) { _turnOn = turnOn; }

	introductionPage();
	~introductionPage();
};

