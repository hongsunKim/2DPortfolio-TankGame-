#pragma once
#include "gameNode.h"
class missionSelect :
	public gameNode
{
private:
	image* _missionSelect;

	image* _missionDescription0;
	image* _missionDescription1;
	image* _missionDescriptionLocked;
	image* _mission1ButtonOn;
	image* _mission1ButtonOff;
	image* _missionLockedButtonOn;
	image* _missionLockedButtonOff;


	RECT _mission1Button[8];

	int _missionNum = 0;

public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	int getMissionNum() { return _missionNum; }
	void setMissionNum(int missionNum) { _missionNum = missionNum; }

	missionSelect();
	~missionSelect();
};

