#include "stdafx.h"
#include "introductionPage.h"

HRESULT introductionPage::init(void)
{

	_howToPlay = IMAGEMANAGER->addImage("����ȭ��", "image/howToPlayPage.bmp", WINSIZEX, WINSIZEY, FALSE, RGB(0, 0, 0));

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
	IMAGEMANAGER->render("����ȭ��", getMemDC());
}

introductionPage::introductionPage()
{
}


introductionPage::~introductionPage()
{
}
