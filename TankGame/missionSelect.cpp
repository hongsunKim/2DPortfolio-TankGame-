#include "stdafx.h"
#include "missionSelect.h"

HRESULT missionSelect::init(void)
{

	_missionSelect = IMAGEMANAGER->addImage("미션선택", "image/missionSelectPage.bmp", WINSIZEX, WINSIZEY, FALSE, RGB(0, 0, 0));

	_missionDescription0 = IMAGEMANAGER->addImage("미션0", "image/mission0.bmp", 1272, 250, TRUE, RGB(255, 255, 255));
	_missionDescription1 = IMAGEMANAGER->addImage("미션1", "image/mission1.bmp", 1272, 250, TRUE, RGB(255, 255, 255));
	_missionDescriptionLocked = IMAGEMANAGER->addImage("미션잠김", "image/missionLocked.bmp", 1272, 250, TRUE, RGB(255, 255, 255));
	_mission1ButtonOn = IMAGEMANAGER->addImage("미션1버튼온", "image/mission1Button(on).bmp", 84, 84, TRUE, RGB(255, 255, 255));
	_mission1ButtonOff = IMAGEMANAGER->addImage("미션1버튼오프", "image/mission1Button(off).bmp", 84, 84, TRUE, RGB(255, 255, 255));
	_missionLockedButtonOn = IMAGEMANAGER->addImage("미션잠김버튼온", "image/missionLockedButtonOn.bmp", 84, 84, TRUE, RGB(255, 255, 255));
	_missionLockedButtonOff = IMAGEMANAGER->addImage("미션잠김버튼오프", "image/missionLockedButtonOff.bmp", 84, 84, TRUE, RGB(255, 255, 255));

	for (int i = 0; i < 8; i++) {
		_mission1Button[i] = RectMakeCenter(235 + i * 120, WINSIZEY - 450, 84, 84);
	}

	return S_OK;
}
void missionSelect::release(void)
{

}
void missionSelect::update(void)
{
	if (PtInRect(&_mission1Button[0], _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			_missionNum = 1;
		}
	}
}
void missionSelect::render(void)
{
	IMAGEMANAGER->render("미션선택", getMemDC());
	IMAGEMANAGER->render("미션0", getMemDC(), 14, WINSIZEY - 330);
	IMAGEMANAGER->render("미션1버튼오프", getMemDC(), _mission1Button[0].left, _mission1Button[0].top);
	for (int i = 1; i < 8; i++) {
		IMAGEMANAGER->render("미션잠김버튼오프", getMemDC(), _mission1Button[i].left, _mission1Button[i].top);
	}

	if (PtInRect(&_mission1Button[0], _ptMouse)) {
		IMAGEMANAGER->render("미션1버튼온", getMemDC(), _mission1Button[0].left, _mission1Button[0].top);
		IMAGEMANAGER->render("미션1", getMemDC(), 14, WINSIZEY - 330);
	}
	for (int i = 1; i < 8; i++) {
		if (PtInRect(&_mission1Button[i], _ptMouse)) {
			IMAGEMANAGER->render("미션잠김버튼온", getMemDC(), _mission1Button[i].left, _mission1Button[i].top);
			IMAGEMANAGER->render("미션잠김", getMemDC(), 14, WINSIZEY - 330);
		}
	}

}

missionSelect::missionSelect()
{
}


missionSelect::~missionSelect()
{
}
