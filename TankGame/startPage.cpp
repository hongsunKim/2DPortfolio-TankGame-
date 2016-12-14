#include "stdafx.h"
#include "startPage.h"

HRESULT startPage::init(void)
{

	_startPage = IMAGEMANAGER->addImage("����������", "image/startPage.bmp", WINSIZEX, WINSIZEY, FALSE, RGB(0, 0, 0));

	_startButtonOn = IMAGEMANAGER->addImage("���۹�ư(��)", "image/gamestartbutton(on).bmp", 254, 36, TRUE, RGB(255, 255, 255));
	_howToPlayButtonOn = IMAGEMANAGER->addImage("�Ͽ����÷��̹�ư(��)", "image/howtoplaybutton(on).bmp", 289, 35, TRUE, RGB(255, 255, 255));
	_exitOn = IMAGEMANAGER->addImage("����Ʈ��ư(��)", "image/exitbutton(on).bmp", 98, 33, TRUE, RGB(255, 255, 255));
	_startButtonOff = IMAGEMANAGER->addImage("���۹�ư(����)", "image/gamestartbutton(off).bmp", 254, 36, TRUE, RGB(255, 255, 255));
	_howToPlayButtonOff = IMAGEMANAGER->addImage("�Ͽ����÷��̹�ư(����)", "image/howtoplaybutton(off).bmp", 289, 35, TRUE, RGB(255, 255, 255));
	_exitOff = IMAGEMANAGER->addImage("����Ʈ��ư(����)", "image/exitbutton(off).bmp", 98, 33, TRUE, RGB(255, 255, 255));


	_startButtonRect = RectMakeCenter(WINSIZEX - 200, WINSIZEY - 200, _startButtonOff->getWidth(), _startButtonOff->getHeight());
	_howToPlayButtonRect = RectMakeCenter(WINSIZEX - 200, WINSIZEY - 125, _howToPlayButtonOff->getWidth(), _howToPlayButtonOff->getHeight());
	_exitButtonRect = RectMakeCenter(WINSIZEX - 200, WINSIZEY - 50, _exitOff->getWidth(), _exitOff->getHeight());

	return S_OK;
}
void startPage::release(void)
{

}
void startPage::update(void)
{
	//Ŭ��������
	if (PtInRect(&_startButtonRect, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			_menu = 3;
			_turnOn = false;
		}
	}
	if (PtInRect(&_howToPlayButtonRect, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			_menu = 2;
			_turnOn = false;
		}
	}
	if (PtInRect(&_exitButtonRect, _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			_menu = 4;
			_turnOn = false;
		}
	}
}
void startPage::render(void)
{
	IMAGEMANAGER->render("����������", getMemDC(), 0,0);
	IMAGEMANAGER->render("���۹�ư(����)", getMemDC(), _startButtonRect.left, _startButtonRect.top);
	IMAGEMANAGER->render("�Ͽ����÷��̹�ư(����)", getMemDC(), _howToPlayButtonRect.left, _howToPlayButtonRect.top);
	IMAGEMANAGER->render("����Ʈ��ư(����)", getMemDC(), _exitButtonRect.left, _exitButtonRect.top);

	if (PtInRect(&_startButtonRect, _ptMouse)) {
		IMAGEMANAGER->render("���۹�ư(��)", getMemDC(), _startButtonRect.left, _startButtonRect.top);
	}
	if (PtInRect(&_howToPlayButtonRect, _ptMouse)) {
		IMAGEMANAGER->render("�Ͽ����÷��̹�ư(��)", getMemDC(), _howToPlayButtonRect.left, _howToPlayButtonRect.top);
	}
	if (PtInRect(&_exitButtonRect, _ptMouse)) {
		IMAGEMANAGER->render("����Ʈ��ư(��)", getMemDC(), _exitButtonRect.left, _exitButtonRect.top);
	}
	
}

startPage::startPage()
{
}


startPage::~startPage()
{
}
