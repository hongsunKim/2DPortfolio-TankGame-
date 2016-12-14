#include "stdafx.h"
#include "structure.h"
#include "enemyTankManager.h"
#include "enemyTank.h"

HRESULT structure::init(void)
{
	//_structureType =  RND->getInt(10);	//������ ���� ��

	//switch (_structureType) {
	//case 0:
	//	  IMAGEMANAGER->findImage("���")->getWidth
	//}

	//_x = RND->getFromfloatTo(1, 3 * WINSIZEX);
	//_y = RND->getFromfloatTo(1, 3 * WINSIZEY);

	//_rect = RectMakeCenter(_x, _y, 450	, 450);

	return S_OK;
}
void structure::release(void)
{

}
void structure::update(void)
{
	collisionCheck();

	if (_structureType == 1) {
		_rect = RectMakeCenter(_x, _y, 400, 400);
	}
	else if (_structureType == 2) {
		_rect = RectMakeCenter(_x, _y, IMAGEMANAGER->findImage("����")->getWidth(), IMAGEMANAGER->findImage("����")->getHeight());
	}
	else if (_structureType == 3) {
		_rect = RectMakeCenter(_x, _y, IMAGEMANAGER->findImage("��1")->getWidth(), IMAGEMANAGER->findImage("��1")->getHeight());
	}
	else if (_structureType == 4) {
		_rect = RectMakeCenter(_x, _y, IMAGEMANAGER->findImage("�溮")->getWidth() + 5, IMAGEMANAGER->findImage("�溮")->getHeight()+5);
	}
}
void structure::render(void)
{
	if (_structureType == 1) {
		IMAGEMANAGER->render("��", getMemDC(), _x - (IMAGEMANAGER->findImage("��")->getWidth() / 2) - _viewPointX, _y - (IMAGEMANAGER->findImage("��")->getHeight() / 2) - _viewPointY);
		//Rectangle(getMemDC(), _rect.left - _viewPointX, _rect.top - _viewPointY, _rect.right - _viewPointX, _rect.bottom - _viewPointY);
	}
	else if (_structureType == 2) {
		IMAGEMANAGER->render("����", getMemDC(), _x - (IMAGEMANAGER->findImage("����")->getWidth() / 2) - _viewPointX, _y - (IMAGEMANAGER->findImage("����")->getHeight() / 2) - _viewPointY);
	}
	else if (_structureType == 3) {
		IMAGEMANAGER->render("��1", getMemDC(), _x - (IMAGEMANAGER->findImage("��1")->getWidth() / 2) - _viewPointX, _y - (IMAGEMANAGER->findImage("��1")->getHeight() / 2) - _viewPointY);
	}
	else if (_structureType == 4) {
		IMAGEMANAGER->render("�溮", getMemDC(), _x - (IMAGEMANAGER->findImage("�溮")->getWidth() / 2) - _viewPointX, _y - (IMAGEMANAGER->findImage("�溮")->getHeight() / 2) - _viewPointY);
	}
}

void structure::collisionCheck(void)
{
	//_enemyTankManager->get_vEnemyTank();

	//RECT tempRect;
	//
	//_enemyTankManager->set_viEnemyTank(_enemyTankManager->get_vEnemyTank().begin());
	//for (; _enemyTankManager->get_viEnemyTank() != _enemyTankManager->get_vEnemyTank().end(); _enemyTankManager->set_viEnemyTank(_enemyTankManager->get_viEnemyTank() + 1)) {
	//	if (IntersectRect(&tempRect, &_rect, &((*(_enemyTankManager->get_viEnemyTank()))->getRect())) == true) {
	//
	//		if (tempRect.bottom - tempRect.top < tempRect.right - tempRect.left) {
	//			if ((*(_enemyTankManager->get_viEnemyTank()))->getY() < _y) {
	//				(*(_enemyTankManager->get_viEnemyTank()))->setY((*(_enemyTankManager->get_viEnemyTank()))->getY() - (tempRect.bottom - tempRect.top));
	//			}
	//			else {
	//				(*(_enemyTankManager->get_viEnemyTank()))->setY((*(_enemyTankManager->get_viEnemyTank()))->getY() + (tempRect.bottom - tempRect.top));
	//			}
	//		}
	//		else {
	//			if (_x < (*(_enemyTankManager->get_viEnemyTank()))->getX()) {
	//				(*(_enemyTankManager->get_viEnemyTank()))->setX((*(_enemyTankManager->get_viEnemyTank()))->getX() - (tempRect.right - tempRect.left));
	//			}
	//			else {
	//				(*(_enemyTankManager->get_viEnemyTank()))->setX((*(_enemyTankManager->get_viEnemyTank()))->getX() + (tempRect.right - tempRect.left));
	//			}
	//		}
	//
	//	}
	//}
	
}

void setStructure(int sturctureType, float x, float y, RECT rect)
{

}

structure::structure()
{
}


structure::~structure()
{
}
