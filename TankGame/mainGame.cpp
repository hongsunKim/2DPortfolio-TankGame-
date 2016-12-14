#include "stdafx.h"
#include "mainGame.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}

//==================================================================
//		## �ʱ�ȭ ## init(void)
//==================================================================
HRESULT mainGame::init(void)
{
	gameNode::init(true);
	//�̰����� �ʱ�ȭ�� �Ѵ�


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
//		## ���� ## release(void)
//==================================================================
void mainGame::release(void)
{
	gameNode::release();
	//�̹��� Ŭ���� ���������� ����� �� ����



}

//==================================================================
//		## ������Ʈ ## update(void)
//==================================================================
void mainGame::update(void)
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�

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
//		## ���� ## render(HDC hdc)
//==================================================================
void mainGame::render(void)
{
	//��� �� ��Ʈ�� (�̰͵� ������ �׳� �״�� �Ѱ�!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//�̰����� WM_PAINT���� �ߴ����� ó���ϸ� �ȴ�
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
//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �Ѱ�!!)
	this->getBackBuffer()->render(getHDC());
}

//==================================================================
//		## �Ϲ��Լ� ## (������� ���� �Լ�)
//==================================================================

