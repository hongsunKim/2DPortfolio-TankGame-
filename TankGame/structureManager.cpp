#include "stdafx.h"
#include "structureManager.h"
#include "myTank.h"
#include "enemyTankManager.h"

HRESULT structureManager::init(void)
{


	return S_OK;
}

HRESULT structureManager::init(int howMany)
{
	for (int i = 0; i < howMany; ++i) {
		structure* tempStructure;
		tempStructure = new structure;
		tempStructure->init();
		_vStructure.push_back(tempStructure);
	}

	return S_OK;
}

void structureManager::release(void)
{
	
}
void structureManager::update(void)
{
	collisionCheck();

	if (_vStructure.size() != 0) {

		_viStructure = _vStructure.begin();
		for (_viStructure; _viStructure != _vStructure.end(); ++_viStructure) {
			(*_viStructure)->update();
			
		}
	}
}
void structureManager::render(void)
{
	if (_vStructure.size() != 0) {
		_viStructure = _vStructure.begin();
		for (_viStructure; _viStructure != _vStructure.end(); ++_viStructure) {
			(*_viStructure)->render();


			//wsprintf(debug, "(*_viStructure)->getRect().left: %d // _myTank->getRect().left: %d", (*_viStructure)->getRect().left, int(_myTank->getRect().left));
			//TextOut(getMemDC(), 10, 70, debug, lstrlen(debug));

			//RECT tempRect;
			//
			//if (IntersectRect(&tempRect, &(_myTank->getRect()), &((*_viStructure)->getRect())) == true) {
			//
			//	wsprintf(debug2, "structureMangerDebug2: collision detected!");
			//	TextOut(getMemDC(), 10, 90, debug2, lstrlen(debug2));
			//
			//}

		}
	}
}

void structureManager::collisionCheck()
{
	RECT tempRect;

	if (_vStructure.size() != 0) {
		_viStructure = _vStructure.begin();
		for (_viStructure; _viStructure != _vStructure.end(); ++_viStructure) {
			if(IntersectRect(&tempRect, &(_myTank->getRect()), &((*_viStructure)->getRect())) == true) {

				if (tempRect.bottom - tempRect.top < tempRect.right - tempRect.left) {
					if ((*_viStructure)->getY() < _myTank->getY()) {
						_myTank->setY(_myTank->getY() + (tempRect.bottom - tempRect.top));
					}
					else {
						_myTank->setY(_myTank->getY() - (tempRect.bottom - tempRect.top));
					}
				}
				else {
					if ((*_viStructure)->getX() < _myTank->getX()) {
						_myTank->setX(_myTank->getX() + (tempRect.right - tempRect.left));
					}
					else {
						_myTank->setX(_myTank->getX() - (tempRect.right - tempRect.left));
					}
				}
			}
		}
	}


	//RECT tempRect2;
	//for (_viStructure = _vStructure.begin(); _viStructure != _vStructure.end(); ++_viStructure) {
	//	for (_viStructure2 = _vStructure.begin(); _viStructure2 != _vStructure.end(); ++_viStructure2) {
	//		if (_viStructure == _viStructure2) { continue; }
	//		else {
	//			if (IntersectRect(&tempRect2, &((*(_viStructure))->getRect()), &((*(_viStructure2))->getRect())) == true) {
	//
	//				if (tempRect2.right - tempRect2.left > tempRect2.bottom - tempRect2.top) {
	//					if ((*(_viStructure))->getY() < (*(_viStructure2))->getY()) {
	//						(*(_viStructure))->setY((*(_viStructure))->getY() - (tempRect2.bottom - tempRect2.top));
	//						(*(_viStructure2))->setY((*(_viStructure2))->getY() + (tempRect2.bottom - tempRect2.top));
	//					}
	//					else {
	//						(*(_viStructure))->setY((*(_viStructure))->getY() + (tempRect2.bottom - tempRect2.top));
	//						(*(_viStructure2))->setY((*(_viStructure2))->getY() - (tempRect2.bottom - tempRect2.top));
	//					}
	//				}
	//				else if (tempRect2.right - tempRect2.left < tempRect2.bottom - tempRect2.top) {
	//					if ((*(_viStructure))->getX() < (*(_viStructure2))->getX()) {
	//						(*(_viStructure))->setX((*(_viStructure))->getX() - (tempRect2.right - tempRect2.left));
	//						(*(_viStructure2))->setX((*(_viStructure2))->getX() + (tempRect2.right - tempRect2.left));
	//					}
	//					else {
	//						(*(_viStructure))->setX((*(_viStructure))->getX() + (tempRect2.right - tempRect2.left));
	//						(*(_viStructure2))->setX((*(_viStructure2))->getX() - (tempRect2.right - tempRect2.left));
	//					}
	//				}
	//
	//			}
	//		}
	//	}
	//
	//}

	//_enemyTankManager->get_vEnemyTank().begin();
	//
	//_enemyTankManager->get_viEnemyTank();
	//
	//_enemyTankManager->set_viEnemyTank(_enemyTankManager->get_vEnemyTank().begin());
	//for (; _enemyTankManager->get_viEnemyTank() != _enemyTankManager->get_vEnemyTank().end(); _enemyTankManager->set_viEnemyTank(++_enemyTankManager->get_viEnemyTank())) {
	//	_viStructure = _vStructure.begin();
	//	for (_viStructure; _viStructure != _vStructure.end(); ++_viStructure) {
	//		if (IntersectRect(&tempRect, &((*(_enemyTankManager->get_viEnemyTank()))->getRect()), &((*_viStructure)->getRect())) == true) {
	//
	//			if (tempRect.bottom - tempRect.top < tempRect.right - tempRect.left) {
	//				if ((*_viStructure)->getY() < (*(_enemyTankManager->get_viEnemyTank()))->getY()) {
	//					(*(_enemyTankManager->get_viEnemyTank()))->setY((*(_enemyTankManager->get_viEnemyTank()))->getY() + (tempRect.bottom - tempRect.top));
	//				}
	//				else {
	//					(*(_enemyTankManager->get_viEnemyTank()))->setY((*(_enemyTankManager->get_viEnemyTank()))->getY() - (tempRect.bottom - tempRect.top));
	//				}
	//			}
	//			else {
	//				if ((*_viStructure)->getX() < (*(_enemyTankManager->get_viEnemyTank()))->getX()) {
	//					(*(_enemyTankManager->get_viEnemyTank()))->setX((*(_enemyTankManager->get_viEnemyTank()))->getX() + (tempRect.right - tempRect.left));
	//				}
	//				else {
	//					(*(_enemyTankManager->get_viEnemyTank()))->setX((*(_enemyTankManager->get_viEnemyTank()))->getX() - (tempRect.right - tempRect.left));
	//				}
	//			}
	//
	//		}
	//	}
	//}
}

void structureManager::setMyEnemyManagerLink(enemyTankManager* enemyTankManager)
{
	//if (_vStructure.size() != 0) {
	//	for (_viStructure = _vStructure.begin(); _viStructure != _vStructure.end(); ++_viStructure) {
	//		(*_viStructure)->setEnemyTankManagerLink(enemyTankManager);
	//	}
	//}
}

void structureManager::addStructure(int structureType, float x, float y)
{
	structure* tempStructure;
	tempStructure = new structure;
	tempStructure->setStructure(structureType, x, y);
	_vStructure.push_back(tempStructure);
}

structureManager::structureManager()
{
}


structureManager::~structureManager()
{
}