#pragma once
#include "gameNode.h"
class startPage :
	public gameNode
{
private:
	image* _startPage;

	image* _startButtonOn;
	image* _howToPlayButtonOn;
	image* _exitOn;
	image* _startButtonOff;
	image* _howToPlayButtonOff;
	image* _exitOff;

	RECT _startButtonRect;
	RECT _howToPlayButtonRect;
	RECT _exitButtonRect;

	bool _turnOn = true;

	int _menu;

public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	inline bool getTurnOn() { return _turnOn; }
	inline void setTurnOn(bool turnOn) { _turnOn = turnOn; }

	inline int getMenu() { return _menu; }
	inline void setMenu(int menu) { _menu = menu; }

	startPage();
	~startPage();
};

