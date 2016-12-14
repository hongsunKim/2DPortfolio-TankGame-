#include "stdafx.h"
#include "missile.h"

HRESULT missile::init(void)
{

	return S_OK;
}

HRESULT missile::init(float x, float y, float angle, float range, float speed)
{

	_missileImage = new image;
	_missileImage->init("image/missile.bmp", 1088, 16, 68, 1, TRUE, RGB(0, 0, 0));
	_targetImage = new image;
	_targetImage->init("image/target.bmp", 55, 56, TRUE, RGB(0, 0, 0));
	_explosionImage = new image;
	_explosionImage->init("image/explosion.bmp", 1536, 64, 24, 1, TRUE, RGB(0, 0, 0));
	_x = _fireX = x;
	_y = _fireY = y;
	_angle = angle;
	_range = range;
	_speed = speed;
	_targetX = _fireX + cosf(_angle)* _range;
	_targetY = _fireY + -sinf(_angle)* _range;
	_fire = true;
	_explode = false;
	_scale = 1;

	_missileImage->setFrameX((int(angle / (PI / 180))) / 5);

	return S_OK;
}
void missile::release(void)
{
	SAFE_DELETE(_missileImage);
	SAFE_DELETE(_targetImage);
	SAFE_DELETE(_explosionImage);
}
void missile::update(void)
{
	if (_fire == true && _explode == false) {
		_x = _x + cosf(_angle)* _speed;
		_y = _y + -sinf(_angle)* _speed;
	}

	if (_range < getDistance(_fireX, _fireY, _x, _y)) {
		_explode = true;
	}

	if (_explode == true) {
		_explosionCount++;
		_explosionImage->setFrameX(_explosionCount);
	}

}
void missile::render(void)
{
	float originX = _earthPointX;
	float originY = _earthPointY;

	if (_explode == false) {
		_missileImage->frameRender(getMemDC(), _x - _missileImage->getFrameWidth() / 2 - _viewPointX, _y - _missileImage->getFrameHeight() / 2 - _viewPointY);
		_targetImage->alphaRender(getMemDC(), _targetX - 28 - _viewPointX, _targetY - 28 - _viewPointY, 150 * (getDistance(_fireX, _fireY, _x, _y)) / (getDistance(_fireX, _fireY, _targetX, _targetY)));
	}
	else {
		_explosionImage->frameRender(getMemDC(), _targetX - 32 - _viewPointX, _targetY - 32 - _viewPointY);
		//if (_explosionCount == 1) {
		//	_earthPointX += 10;
		//}
		//else if (_explosionCount == 2) {
		//
		//	_earthPointX -= 10;
		//
		//}
		//else if (_explosionCount == 3) {
		//	_earthPointX -= 6;
		//}
		//else if (_explosionCount == 4) {
		//	_earthPointX += 6;
		//}
		//else if (_explosionCount == 5) {
		//	_earthPointX += 2;
		//}
		//else if (_explosionCount == 6) {
		//	_earthPointX -= 2;
		//}
		//
		//else {
		//	_earthPointX == originX;
		//	_earthPointY == originY;
		//}
	}

	//wsprintf(debug, "πÃªÁ¿œ x: %d // y: %d", int(_x), int(_y));
	//TextOut(getMemDC(), 10, 30, debug, lstrlen(debug));

}

int missile::getExplosionFrame(void)
{
	return _explosionCount;
}

missile::missile()
{
}


missile::~missile()
{
}