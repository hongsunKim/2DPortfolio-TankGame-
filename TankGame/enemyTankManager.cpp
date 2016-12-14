#include "stdafx.h"
#include "enemyTankManager.h"

HRESULT enemyTankManager::init(void)
{

	return S_OK;
}
HRESULT enemyTankManager::init(int howMany)
{

	for (int i = 0; i < howMany; ++i) {
		enemyTank* tempEnemyTank;
		tempEnemyTank = new enemyTank;
		tempEnemyTank->setMyTankMemoryLink(_myTank);
		tempEnemyTank->init();
		_vEnemyTank.push_back(tempEnemyTank);
	}

	return S_OK;
}
void enemyTankManager::release(void)
{

}
void enemyTankManager::update(void)
{
	collisionCheck();
	eraseEnemyTank();

	if (_vEnemyTank.size() != 0) {

		_viEnemyTank = _vEnemyTank.begin();
		for (_viEnemyTank; _viEnemyTank != _vEnemyTank.end(); ++_viEnemyTank) {
			(*_viEnemyTank)->update();

		}
	}
}
void enemyTankManager::render(void)
{
	if (_vEnemyTank.size() != 0) {

		_viEnemyTank = _vEnemyTank.begin();
		for (_viEnemyTank; _viEnemyTank != _vEnemyTank.end(); ++_viEnemyTank) {
			(*_viEnemyTank)->render();
		}
	}
}

void enemyTankManager::collisionCheck()
{
	RECT tempRect;
	for (_viEnemyTank = _vEnemyTank.begin(); _viEnemyTank != _vEnemyTank.end(); ++_viEnemyTank) {
		for (_viEnemyTank2 = _vEnemyTank.begin(); _viEnemyTank2 != _vEnemyTank.end(); ++_viEnemyTank2) {
			if (_viEnemyTank == _viEnemyTank2) { continue; }
			else {
				if (IntersectRect(&tempRect, &((*(_viEnemyTank))->getRect()), &((*(_viEnemyTank2))->getRect())) == true) {

					if (tempRect.right - tempRect.left > tempRect.bottom - tempRect.top) {
						if ((*(_viEnemyTank))->getY() < (*(_viEnemyTank2))->getY()) {
							(*(_viEnemyTank))->setY((*(_viEnemyTank))->getY() - (tempRect.bottom - tempRect.top));
							(*(_viEnemyTank2))->setY((*(_viEnemyTank2))->getY() + (tempRect.bottom - tempRect.top));
						}
						else {
							(*(_viEnemyTank))->setY((*(_viEnemyTank))->getY() + (tempRect.bottom - tempRect.top));
							(*(_viEnemyTank2))->setY((*(_viEnemyTank2))->getY() - (tempRect.bottom - tempRect.top));
						}
					}
					else if (tempRect.right - tempRect.left < tempRect.bottom - tempRect.top) {
						if ((*(_viEnemyTank))->getX() < (*(_viEnemyTank2))->getX()) {
							(*(_viEnemyTank))->setX((*(_viEnemyTank))->getX() - (tempRect.right - tempRect.left));
							(*(_viEnemyTank2))->setX((*(_viEnemyTank2))->getX() + (tempRect.right - tempRect.left));
						}
						else {
							(*(_viEnemyTank))->setX((*(_viEnemyTank))->getX() + (tempRect.right - tempRect.left));
							(*(_viEnemyTank2))->setX((*(_viEnemyTank2))->getX() - (tempRect.right - tempRect.left));
						}
					}

				}
			}
		}

	}

}

void enemyTankManager::eraseEnemyTank(void)
{
	if (_vEnemyTank.size() != 0) {
		_viEnemyTank = _vEnemyTank.begin();
		for (; _viEnemyTank != _vEnemyTank.end();) {
			if ((*_viEnemyTank)->getHp() <= 0) {
				_viEnemyTank = _vEnemyTank.erase(_viEnemyTank);
			}
			else {
				++_viEnemyTank;
			}
		}
	}
}

enemyTankManager::enemyTankManager()
{
}


enemyTankManager::~enemyTankManager()
{
}