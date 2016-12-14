#include "stdafx.h"
#include "mainGame.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}

//==================================================================
//		## 초기화 ## init(void)
//==================================================================
HRESULT mainGame::init(void)
{
	gameNode::init(true);
	//이곳에서 초기화를 한다


	_startPage = new startPage;
	_startPage->init();
	_startPage->setTurnOn(true);
	_startPage->setMenu(0);

	_introductionPage = new introductionPage;
	_introductionPage->init();
	_introductionPage->setTurnOn(false);

	_missionSelect = new missionSelect;
	_missionSelect->init();

	_mission1 = new mission1;
	_mission1->init();

	
	return S_OK;
}

//==================================================================
//		## 해제 ## release(void)
//==================================================================
void mainGame::release(void)
{
	gameNode::release();
	//이미지 클래스 나갈때까진 사용할 일 없다



}

//==================================================================
//		## 업데이트 ## update(void)
//==================================================================
void mainGame::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다

	if (_pageNum == 1) {
		_startPage->update();
	}
	else if (_pageNum == 2) {
		_introductionPage->update();
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
			_pageNum = 1;
		}
	}
	else if (_pageNum == 3) {
		_missionSelect->update();
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) {
			_pageNum = 1;
		}
		if (_missionSelect->getMissionNum() == 1) {
			_pageNum = 4;
			_missionSelect->setMissionNum(0);
		}
	}
	else if (_pageNum == 4) {
		_mission1->update();
	}

	if (_startPage->getMenu() == 1) {
		_pageNum = 1;
		_startPage->setMenu(0);
	}

	else if (_startPage->getMenu() == 2) {
		_pageNum = 2;
		_startPage->setMenu(0);
	}

	else if (_startPage->getMenu() == 3) {
		_pageNum = 3;
		_startPage->setMenu(0);
	}
	else if (_startPage->getMenu() == 4) {
		PostQuitMessage(0);
	}
	
	if (_mission1->getToCollectionPage() == true) {
		_pageNum = 3;
		_mission1->setToCollectionPage(false);
	}
}

//==================================================================
//		## 렌더 ## render(HDC hdc)
//==================================================================
void mainGame::render(void)
{
	//흰색 빈 비트맵 (이것도 렌더에 그냥 그대로 둘것!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//이곳에서 WM_PAINT에서 했던것을 처리하면 된다
//==================================================================

	if (_pageNum == 1) {
		_startPage->render();
	}
	else if (_pageNum == 2) {
		_introductionPage->render();
	}
	else if (_pageNum == 3) {
		_missionSelect->render();
	}
	else if (_pageNum == 4) {
		_mission1->render();
	}

	//TIMEMANAGER->render(getMemDC());
//==================================================================
//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 둘것!!)
	this->getBackBuffer()->render(getHDC());
}

//==================================================================
//		## 일반함수 ## (너희들이 만든 함수)
//==================================================================

