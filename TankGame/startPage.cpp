#include "stdafx.h"
#include "startPage.h"

HRESULT startPage::init(void)
{

	_startPage = IMAGEMANAGER->addImage("시작페이지", "image/startPage.bmp", WINSIZEX, WINSIZEY, FALSE, RGB(0, 0, 0));

	_startButtonOn = IMAGEMANAGER->addImage("시작버튼(온)", "image/gamestartbutton(on).bmp", 254, 36, TRUE, RGB(255, 255, 255));
	_howToPlayButtonOn = IMAGEMANAGER->addImage("하우투플레이버튼(온)", "image/howtoplaybutton(on).bmp", 289, 35, TRUE, RGB(255, 255, 255));
	_exitOn = IMAGEMANAGER->addImage("엑시트버튼(온)", "image/exitbutton(on).bmp", 98, 33, TRUE, RGB(255, 255, 255));
	_startButtonOff = IMAGEMANAGER->addImage("시작버튼(오프)", "image/gamestartbutton(off).bmp", 254, 36, TRUE, RGB(255, 255, 255));
	_howToPlayButtonOff = IMAGEMANAGER->addImage("하우투플레이버튼(오프)", "image/howtoplaybutton(off).bmp", 289, 35, TRUE, RGB(255, 255, 255));
	_exitOff = IMAGEMANAGER->addImage("엑시트버튼(오프)", "image/exitbutton(off).bmp", 98, 33, TRUE, RGB(255, 255, 255));


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
	//클릭했을시
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
	IMAGEMANAGER->render("시작페이지", getMemDC(), 0,0);
	IMAGEMANAGER->render("시작버튼(오프)", getMemDC(), _startButtonRect.left, _startButtonRect.top);
	IMAGEMANAGER->render("하우투플레이버튼(오프)", getMemDC(), _howToPlayButtonRect.left, _howToPlayButtonRect.top);
	IMAGEMANAGER->render("엑시트버튼(오프)", getMemDC(), _exitButtonRect.left, _exitButtonRect.top);

	if (PtInRect(&_startButtonRect, _ptMouse)) {
		IMAGEMANAGER->render("시작버튼(온)", getMemDC(), _startButtonRect.left, _startButtonRect.top);
	}
	if (PtInRect(&_howToPlayButtonRect, _ptMouse)) {
		IMAGEMANAGER->render("하우투플레이버튼(온)", getMemDC(), _howToPlayButtonRect.left, _howToPlayButtonRect.top);
	}
	if (PtInRect(&_exitButtonRect, _ptMouse)) {
		IMAGEMANAGER->render("엑시트버튼(온)", getMemDC(), _exitButtonRect.left, _exitButtonRect.top);
	}
	
}

startPage::startPage()
{
}


startPage::~startPage()
{
}
