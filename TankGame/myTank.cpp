#include "stdafx.h"
#include "myTank.h"
#include "structureManager.h"
#include "enemyTankManager.h"

HRESULT myTank::init(void)
{

	_cannonImage = new image;
	_cannonImage->init("image/cannon.bmp", 128 * 45, 128 * 4, 45, 4, TRUE, RGB(0, 0, 0));
	_bodyImage = new image;
	_bodyImage->init("image/body.bmp", 128 * 45, 128 * 4, 45, 4, TRUE, RGB(0, 0, 0));
	_cannonAngle = PI / 2;
	_bodyAngle = PI / 2;
	_speed = 0;
	_speedDst = 0;
	_angle = 0;
	_angleDst = 0;
	_power = 0;
	_x = 200;
	_y = 500;
	//_x = 200;	//전체 맵에서의 절대좌표
	//_y = 3 * WINSIZEY - 200;	//전체 맵에서의 절대좌표
	_fullHp = 1000;
	_currentHp = 1000;

	_hpBar = new hpBar;
	_hpBar->init();

	_rect = { 0,0,0,0 };

	_structureManager = new structureManager;

	return S_OK;
}

void myTank::release(void)
{
	SAFE_DELETE(_cannonImage);
	SAFE_DELETE(_bodyImage);

	//SAFE_DELETE(_rect);
	_hpBar->release();
}

void myTank::update(void)
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

void myTank::render(void)
{

	_hpBar->render();

	_bodyImage->frameRender(getMemDC(), WINSIZEX/2 - 64, WINSIZEY/2 - 64);
	_cannonImage->frameRender(getMemDC(), WINSIZEX / 2 - 64, WINSIZEY / 2 - 64);

	//wsprintf(debug, "x: %d // y: %d", int(_x), int(_y));
	//TextOut(getMemDC(), 10, 10, debug, lstrlen(debug));

	//Rectangle(getMemDC(), _rect.left - _viewPointX , _rect.top - _viewPointY, _rect.right - _viewPointX, _rect.bottom - _viewPointY);

	//if (_vMissile.size() != 0) {
	//	_viMissile = _vMissile.begin();
	//	for (_viMissile; _viMissile != _vMissile.end(); ++_viMissile) {
	//		(*_viMissile)->render();
	//	}
	//}

	

}

void myTank::move(void)
{
	//포신 오른쪽으로 돌리기
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_cannonAngle -= 1 * (PI / 180);
		if (_cannonAngle < 0) {
			_cannonAngle += 2 * PI;
		}
	}

	//포신 왼쪽으로 돌리기
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_cannonAngle += 1 * (PI / 180);
		if (_cannonAngle > 2 * PI) {
			_cannonAngle -= 2 * PI;
		}
	}

	if (KEYMANAGER->isStayKeyDown('W')) {

		if (KEYMANAGER->isStayKeyDown('D')) {
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

		if (KEYMANAGER->isStayKeyDown('A')) {
			_bodyAngle += _angle * (PI / 180);
			if (_bodyAngle > 2 * PI) {
				_bodyAngle -= 2 * PI;
			}
			_cannonAngle += _angle * (PI / 180);
			if (_cannonAngle > 2 * PI) {
				_cannonAngle -= 2 * PI;
			}

			_angleDst = 0.5;
		}

		_speedDst = 1.5;


	}

	if (KEYMANAGER->isOnceKeyUp('W')) {
		_speedDst = 0.0f;
		_angleDst = 0.0;
	}

	if (KEYMANAGER->isStayKeyDown('S')) {

		if (KEYMANAGER->isStayKeyDown('D')) {
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

		if (KEYMANAGER->isStayKeyDown('A')) {
			_bodyAngle += _angle * (PI / 180);
			if (_bodyAngle > 2 * PI) {
				_bodyAngle -= 2 * PI;
			}
			_cannonAngle += _angle * (PI / 180);
			if (_cannonAngle > 2 * PI) {
				_cannonAngle -= 2 * PI;
			}
			_angleDst = 0.5;
		}

		_speedDst = -1.5;
	}

	if (KEYMANAGER->isOnceKeyUp('S')) {
		_speedDst = 0.0f;
		_angleDst = 0.0;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		{
			_power += 10;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		missile* tempMissile;
		tempMissile = new missile;
		tempMissile->init(_x + cosf(_cannonAngle) * 65, _y - sinf(_cannonAngle) * 65, _cannonAngle, _power, 5);
		_vMissile.push_back(tempMissile);
		_power = 0;
	}
}

void myTank::damageCheck(void) {

	if (_vMissile.size() != 0) {
		for (int i = 0; i < _vMissile.size(); i++) {
			if (_vMissile[i]->getExplosionFrame() == 1) {

				for (int j = 0; j < _enemyTankManager->get_vEnemyTank().size(); j++) {
					if (getDistance(_vMissile[i]->getX(), _vMissile[i]->getY(), _enemyTankManager->get_vEnemyTank()[j]->getX(), _enemyTankManager->get_vEnemyTank()[j]->getY()) < 80) {
						_enemyTankManager->get_vEnemyTank()[j]->setHp(_enemyTankManager->get_vEnemyTank()[j]->getHp() - ((80 - getDistance(_vMissile[i]->getX(), _vMissile[i]->getY(), _enemyTankManager->get_vEnemyTank()[j]->getX(), _enemyTankManager->get_vEnemyTank()[j]->getY())) * 5 / 8));
					}

					
				}
			}
		}
	}
	
	//if (_vMissile.size() != 0) {
	//	_viMissile = _vMissile.begin();
	//	for (_viMissile; _viMissile < _vMissile.end(); ++_viMissile) {
	//		if ((*_viMissile)->getExplosionFrame() == 1) {
	//			for(_enemyTankManager->get)
	//			if (getDistance((*_viMissile)->getX(), (*_viMissile)->getY(), _enemyTank->getX(), _enemyTank->getY()) < 80) {
	//				_enemyTank->setHp(_enemyTank->getHp() - ((80 - getDistance(_viMissile->getX(), _viMissile->getY(), _enemyTank->getX(), _enemyTank->getY())) * 5 / 8));
	//			}
	//		}
	//	}
	//}
}


void myTank::collisionCheck(void)
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

	//_structureManager->get_vStructure().size();

	//(_enemyTankManager->get_vEnemyTank()).begin();

	//if (_enemyTankManager->get_vEnemyTank().size() != 0) {
	//	RECT tempRect;
	//	_enemyTankManager->set_viEnemyTank(_enemyTankManager->get_vEnemyTank().begin());
	//	for (; _enemyTankManager->get_viEnemyTank() != _enemyTankManager->get_vEnemyTank().end(); _enemyTankManager->set_viEnemyTank(_enemyTankManager->get_viEnemyTank()+1)) {
	//		if (IntersectRect(&tempRect, &_rect, &((*_enemyTankManager->get_viEnemyTank())->getRect()))) {
	//			if (tempRect.right - tempRect.left > tempRect.bottom - tempRect.top) {
	//
	//				if (_y < (*_enemyTankManager->get_viEnemyTank())->getY()) {
	//					_y -= (tempRect.bottom - tempRect.top);
	//				}
	//				else {
	//					_y += (tempRect.bottom - tempRect.top);
	//				}
	//			}
	//			else {
	//				if (_x < (*_enemyTankManager->get_viEnemyTank())->getX()) {
	//					_x -= (tempRect.right - tempRect.left);
	//				}
	//				else {
	//					_x += (tempRect.right - tempRect.left);
	//				}
	//			}
	//		}
	//	}
	//}
}

myTank::myTank()
{
}


myTank::~myTank()
{
}
