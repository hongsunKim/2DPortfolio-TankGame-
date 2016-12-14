#include "stdafx.h"
#include "hpBar.h"

HRESULT hpBar::init(void)
{
	_fullHpImage = new image;
	_fullHpImage->init("image/fullHpBar.bmp", 128, 17, FALSE, RGB(0, 0, 0));
	_currentHpImage = new image;
	_currentHpImage->init("image/currentHpBar.bmp", 128, 17, FALSE, RGB(0, 0, 0));
	_fullHp = 100;
	_currentHp = 100;

	return S_OK;
}
void hpBar::release(void)
{
	SAFE_DELETE(_fullHpImage);
	SAFE_DELETE(_currentHpImage);
}
void hpBar::update(void)
{
	//ü�¹ٸ� �ҷ����� ������ set�Լ����� ���ؼ� �����ġ, ü�°��� ������Ʈ ����� �Ѵ�.
}
void hpBar::render(void)
{
	_fullHpImage->render(getMemDC(), _x - 64 - _viewPointX, _y - 9 - _viewPointY);
	_currentHpImage->render(getMemDC(), _x - 64 - _viewPointX, _y - 9 - _viewPointY, 0, 0, 128 * (_currentHp / _fullHp), 17);
}

hpBar::hpBar()
{
}


hpBar::~hpBar()
{
}
