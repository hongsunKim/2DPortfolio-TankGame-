#include "stdafx.h"
#include "introductionPage.h"

HRESULT introductionPage::init(void)
{

	_howToPlay = IMAGEMANAGER->addImage("설명화면", "image/howToPlayPage.bmp", WINSIZEX, WINSIZEY, FALSE, RGB(0, 0, 0));

	return S_OK;
}
void introductionPage::release(void)
{

}
void introductionPage::update(void)
{

}
void introductionPage::render(void)
{
	IMAGEMANAGER->render("설명화면", getMemDC());
}

introductionPage::introductionPage()
{
}


introductionPage::~introductionPage()
{
}
