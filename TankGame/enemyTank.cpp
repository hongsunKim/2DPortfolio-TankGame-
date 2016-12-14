#include "stdafx.h"
#include "enemyTank.h"
#include "myTank.h"
#include "structureManager.h"

HRESULT enemyTank::init(void)
{

	_cannonImage = new image;
	_cannonImage->init("image/cannon.bmp", 128 * 45, 128 * 4, 45, 4, TRUE, RGB(0, 0, 0));
	_bodyImage = new image;
	_bodyImage->init("image/body.bmp", 128 * 45, 128 * 4, 45, 4, TRUE, RGB(0, 0, 0));
	_cannonAngle = PI / 2;
	_bodyAngle = RND->getFromfloatTo(0.01, PI * 2);
	_speed = 0;
	_speedDst = 0;
	_angle = 0;
	_angleDst = 0;
	_power = 0;
	_x = RND->getFromfloatTo(1, 3 * WINSIZEX);	//전체 맵에서의 절대좌표
	_y = RND->getFromfloatTo(1, 3 * WINSIZEY);	//전체 맵에서의 절대좌표	

	_fireCount = 0;

	_fullHp = 100;
	_currentHp = 100;

	_hpBar = new hpBar;
	_hpBar->init();

	_rect = { 0,0,0,0 };

	return S_OK;
}

void enemyTank::release(void)
{
	SAFE_DELETE(_cannonImage);
	SAFE_DELETE(_bodyImage);

	//SAFE_DELETE(_rect);
	_hpBar->release();
}

void enemyTank::update(void)
{
	move();
	damageCheck();
	collisionCheck();

	//몸체 움직임
	if (_speed < _speedDst) {
		//가속도효과
		_speed += 0.05f;
	}
	else if (_speed > _speedDst) {
		_speed -= 0.05f;
	}

	if (_angle < _angleDst) {
		//가속도효과
		_angle += 0.025;
	}
	else if (_angle > _angleDst) {
		_angle -= 0.025;
	}

	_x = _x + cosf(_bodyAngle) * _speed;
	_y = _y - sinf(_bodyAngle) * _speed;

	if (-0.05 < _speed && _speed < 0.05) {
		_speed = 0;
	}

	if (-0.025 < _angle && _angle < 0.025) {
		_angle = 0;
	}


	_bodyImage->setFrameY(BODYDEGREE / 90);
	_bodyImage->setFrameX(BODYDEGREE % 90 / 2);

	_cannonImage->setFrameY(CANNONDEGREE / 90);
	_cannonImage->setFrameX(CANNONDEGREE % 90 / 2);


	if (_vMissile.size() != 0) {
		_viMissile = _vMissile.begin();
		for (; _viMissile != _vMissile.end();) {
			(*_viMissile)->update();
			if ((*_viMissile)->getExplosionFrame() == 23) {
				_viMissile = _vMissile.erase(_viMissile);
			}
			else {
				++_viMissile;
			}
		}
	}

	_hpBar->setCurrentHp(_currentHp);
	_hpBar->setFullHp(_fullHp);
	_hpBar->setX(_x);
	_hpBar->setY(_y + 64);
	_hpBar->update();

	_rect = (RectMakeCenter(_x, _y, 40, 40));
}

void enemyTank::render(void)
{
	_hpBar->render();

	_bodyImage->frameRender(getMemDC(), _x - _viewPointX - 64, _y - _viewPointY - 64);
	_cannonImage->frameRender(getMemDC(), _x - _viewPointX - 64, _y - _viewPointY - 64);

	//wsprintf(debug, "x: %d // y: %d", int(_x), int(_y));
	//TextOut(getMemDC(), 10, 10, debug, lstrlen(debug));

	//Rectangle(getMemDC(), _rect.left - _viewPointX , _rect.top - _viewPointY, _rect.right - _viewPointX, _rect.bottom - _viewPointY);

	if (_vMissile.size() != 0) {
		_viMissile = _vMissile.begin();
		for (_viMissile; _viMissile != _vMissile.end(); ++_viMissile) {
			(*_viMissile)->render();
		}
	}

}

void enemyTank::move(void)
{
	////포신 오른쪽으로 돌리기
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	//{
	//	_cannonAngle -= 1 * (PI / 180);
	//	if (_cannonAngle < 0) {
	//		_cannonAngle += 2 * PI;
	//	}
	//}
	//
	////포신 왼쪽으로 돌리기
	//if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//{
	//	_cannonAngle += 1 * (PI / 180);
	//	if (_cannonAngle > 2 * PI) {
	//		_cannonAngle -= 2 * PI;
	//	}
	//}

	_cannonAngle = getAngle(_x, _y, _myTank->getX(), _myTank->getY());


	//if(getDistance(_myTan))

	if (getDistance(_x, _y, _myTank->getX(), _myTank->getY()) > 800) { _speedDst = 0; _angleDst = 0;}


	else if (600 < getDistance(_x, _y, _myTank->getX(), _myTank->getY()) && getDistance(_x, _y, _myTank->getX(), _myTank->getY()) <= 800) {

		_bodyAngle -= _angle * (PI / 180);
		if (_bodyAngle < 0) {
			_bodyAngle += 2 * PI;
		}
		_cannonAngle -= _angle * (PI / 180);
		if (_cannonAngle < 0) {
			_cannonAngle += 2 * PI;
		}
		_angleDst = 0.5;

	}

	else if (400 < getDistance(_x, _y, _myTank->getX(), _myTank->getY()) && getDistance(_x, _y, _myTank->getX(), _myTank->getY()) <= 600) {

		_bodyAngle -= _angle * (PI / 180);
		if (_bodyAngle < 0) {
			_bodyAngle += 2 * PI;
		}

		_speedDst = 1;
	}

	else if (100 < getDistance(_x, _y, _myTank->getX(), _myTank->getY()) && getDistance(_x, _y, _myTank->getX(), _myTank->getY()) <= 200)
	{
		_fireCount+=1;
	}

	else if (getDistance(_x, _y, _myTank->getX(), _myTank->getY()) <= 100) {
		_fireCount += 2;
	}

	//if (KEYMANAGER->isStayKeyDown('W')) {
	//
	//	if (KEYMANAGER->isStayKeyDown('D')) {
	//		_bodyAngle -= _angle * (PI / 180);
	//		if (_bodyAngle < 0) {
	//			_bodyAngle += 2 * PI;
	//		}
	//		_cannonAngle -= _angle * (PI / 180);
	//		if (_cannonAngle < 0) {
	//			_cannonAngle += 2 * PI;
	//		}
	//		_angleDst = 0.5;
	//	}
	//
	//	if (KEYMANAGER->isStayKeyDown('A')) {
	//		_bodyAngle += _angle * (PI / 180);
	//		if (_bodyAngle > 2 * PI) {
	//			_bodyAngle -= 2 * PI;
	//		}
	//		_cannonAngle += _angle * (PI / 180);
	//		if (_cannonAngle > 2 * PI) {
	//			_cannonAngle -= 2 * PI;
	//		}
	//
	//		_angleDst = 0.5;
	//	}
	//
	//	_speedDst = 1.5;
	//
	//
	//}
	//
	//if (KEYMANAGER->isOnceKeyUp('W')) {
	//	_speedDst = 0.0f;
	//	_angleDst = 0.0;
	//}
	//
	//if (KEYMANAGER->isStayKeyDown('S')) {
	//
	//	if (KEYMANAGER->isStayKeyDown('D')) {
	//		_bodyAngle -= _angle * (PI / 180);
	//		if (_bodyAngle < 0) {
	//			_bodyAngle += 2 * PI;
	//		}
	//		_cannonAngle -= _angle * (PI / 180);
	//		if (_cannonAngle < 0) {
	//			_cannonAngle += 2 * PI;
	//		}
	//		_angleDst = 0.5;
	//	}
	//
	//	if (KEYMANAGER->isStayKeyDown('A')) {
	//		_bodyAngle += _angle * (PI / 180);
	//		if (_bodyAngle > 2 * PI) {
	//			_bodyAngle -= 2 * PI;
	//		}
	//		_cannonAngle += _angle * (PI / 180);
	//		if (_cannonAngle > 2 * PI) {
	//			_cannonAngle -= 2 * PI;
	//		}
	//		_angleDst = 0.5;
	//	}
	//
	//	_speedDst = -1.5;
	//}
	//
	//if (KEYMANAGER->isOnceKeyUp('S')) {
	//	_speedDst = 0.0f;
	//	_angleDst = 0.0;
	//}

	_power = getDistance(_x, _y, _myTank->getX(), _myTank->getY()) - 165 + RND->getFromIntTo(1,200);

	if (_power < 500 && _fireCount > 100)
	{
		missile* tempMissile;
		tempMissile = new missile;
		tempMissile->init(_x + cosf(_cannonAngle) * 65, _y - sinf(_cannonAngle) * 65, _cannonAngle, _power, 5);
		_vMissile.push_back(tempMissile);
		_power = 0;

		_fireCount = 0;
	}

	++_fireCount;
}

void enemyTank::damageCheck(void) {

	if (_vMissile.size() != 0) {
		_viMissile = _vMissile.begin();
		for (_viMissile; _viMissile < _vMissile.end(); ++_viMissile) {
			if ((*_viMissile)->getExplosionFrame() == 1) {
				if (getDistance((*_viMissile)->getX(), (*_viMissile)->getY(), _myTank->getX(), _myTank->getY()) < 80) {
					_myTank->setHp(_myTank->getHp() - ((80 - getDistance((*_viMissile)->getX(), (*_viMissile)->getY(), _myTank->getX(), _myTank->getY())) * 5 / 8));
				}
			}
		}
	}
}

void enemyTank::collisionCheck(void)
{
	//RECT tempRect;
	//_structureManager->set_viStructure(_structureManager->get_vStructure()->begin());
	//for(;_structureManager->get_viStructure() != _structureManager->get_vStructure()->end();)
	//
	//if (IntersectRect(&tempRect, &_rect, &_enemyTank->getRect())) {
	//	if (tempRect.right - tempRect.left > tempRect.bottom - tempRect.top) {
	//		if (_y < _enemyTank->getY()) {
	//			_y -= (tempRect.bottom - tempRect.top);
	//		}
	//		else {
	//			_y += (tempRect.bottom - tempRect.top);
	//		}
	//	}
	//	else if (tempRect.right - tempRect.left < tempRect.bottom - tempRect.top) {
	//		if (_x < _enemyTank->getX()) {
	//			_x -= (tempRect.right - tempRect.left);
	//		}
	//		else {
	//			_x += (tempRect.right - tempRect.left);
	//		}
	//	}
	//}

	RECT tempRect;

	if (IntersectRect(&tempRect, &_rect, &_myTank->getRect())) {
		if (tempRect.right - tempRect.left > tempRect.bottom - tempRect.top) {
			if (_y < _myTank->getY()) {
				_y -= (tempRect.bottom - tempRect.top);
				_myTank->setY(_myTank->getY() + (tempRect.bottom - tempRect.top));
			}
			else {
				_y += (tempRect.bottom - tempRect.top);
				_myTank->setY(_myTank->getY() - (tempRect.bottom - tempRect.top));
			}
		}
		else if (tempRect.right - tempRect.left < tempRect.bottom - tempRect.top) {
			if (_x < _myTank->getX()) {
				_x -= (tempRect.right - tempRect.left);
				_myTank->setX(_myTank->getX() + (tempRect.right - tempRect.left));
			}
			else {
				_x += (tempRect.right - tempRect.left);
				_myTank->setX(_myTank->getX() - (tempRect.right - tempRect.left));
			}
		}
	}

	if (_x < 0) {
		_x += 2;
	}
	else if (3 * WINSIZEX < _x) {
		_x -= 2;
	}
	else if (_y < 0) {
		_y += 2;
	}
	else if (3 * WINSIZEY < _y) {
		_y -= 2;
	}

	//_structureManager->get_vStructure().begin();
	//if(IntersectRect(&tempRect, &_rect, &))



}

enemyTank::enemyTank()
{
}


enemyTank::~enemyTank()
{
}
