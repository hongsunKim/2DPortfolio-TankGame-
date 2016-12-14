#include "stdafx.h"
#include "mission1.h"
mission1::mission1()
{
}
mission1::~mission1()
{
}

//==================================================================
//		## 초기화 ## init(void)
//==================================================================
HRESULT mission1::init(void)
{
	gameNode::init(true);
	//이곳에서 초기화를 한다

	_stage1BG = IMAGEMANAGER->addImage("스테이지1배경", "image/stage1BG.bmp", 3900, 2250, FALSE, RGB(0, 0, 0));
	_wall = IMAGEMANAGER->addImage("벽", "image/wall.bmp", 537, 534, TRUE, RGB(143, 143, 143));
	_tree = IMAGEMANAGER->addImage("나무", "image/tree.bmp", 161, 162, TRUE, RGB(0, 0, 1));
	_stone1 = IMAGEMANAGER->addImage("돌1", "image/stone1.bmp", 74, 60, TRUE, RGB(0, 0, 1));
	_defender = IMAGEMANAGER->addImage("방벽", "image/defender.bmp", 53, 55, TRUE, RGB(0, 0, 1));

	//_structureManager = new structureManager;
	//_structureManager->setMyEnemyManagerLink(_enemyTankManager);

	_enemyTankManager = new enemyTankManager;

	_myTank = new myTank;



	_enemyTankManager->setMyTankMemoryLink(_myTank);
	_enemyTankManager->init(4);


	_myTank->setEnemyTankManagerMemoryLink(_enemyTankManager);
	_myTank->init();

	_structureManager = new structureManager;
	_structureManager->setMyTankMemoryLink(_myTank);
	_structureManager->setMyEnemyManagerLink(_enemyTankManager);
	for (int i = 0; i < 7; ++i) {
		_structureManager->addStructure(1, 200 + 400 * i, 3 * WINSIZEY - 200 - 400);
	}
	for (int i = 0; i < 2; ++i) {
		_structureManager->addStructure(1, 200 + 400 * (5 + i), 3 * WINSIZEY - 200 - 800);
	}

	for (int i = 0; i < 2; ++i) {
		_structureManager->addStructure(1, 200 + 400 * (5 + i), 3 * WINSIZEY - 200 - 1200);
	}

	for (int i = 0; i < 2; ++i) {
		_structureManager->addStructure(1, 600, 200 + 400 * i);
	}

	for (int i = 0; i < 8; ++i) {
		_structureManager->addStructure(3, RND->getFromfloatTo(2700, 3900), RND->getFromfloatTo(200, 3 * WINSIZEY - 200));
	}

	for (int i = 0; i < 9; ++i) {
		_structureManager->addStructure(2, RND->getFromfloatTo(2700, 3900), RND->getFromfloatTo(200, 3 * WINSIZEY - 200));
	}

	for (int i = 0; i < 6; ++i) {
		_structureManager->addStructure(3, RND->getFromfloatTo(800, 2000), RND->getFromfloatTo(0, 2 * WINSIZEY));
	}

	for (int i = 0; i < 5; ++i) {
		_structureManager->addStructure(2, RND->getFromfloatTo(800, 2000), RND->getFromfloatTo(0, 2 * WINSIZEY));
	}

	for (int i = 0; i < 10; ++i) {
		_structureManager->addStructure(4, RND->getFromfloatTo(1, 2400), RND->getFromfloatTo(3 * WINSIZEY - 400, 3 * WINSIZEY));
	}

	_complete = IMAGEMANAGER->addImage("complete", "image/complete.bmp", 800, 618, TRUE, RGB(0, 0, 1));
	_gameover = IMAGEMANAGER->addImage("gameover", "image/gameover.bmp", 450, 450, TRUE, RGB(0, 0, 1));

	//_structure1 = new structure;
	//_structure1->setEnemyTankManagerLink(_enemyTankManager);
	//_structure1->init();

	//_enemyTank = new enemyTank;
	//_enemyTank->init();



	//_structure1 = new structure;
	//_structure1->setEnemyTankManagerLink(_enemyTankManager);
	//_structure1->init();

	_targetImage = new image;
	_targetImage->init("image/target.bmp", 55, 56, TRUE, RGB(0, 0, 0));


	//_structureManager->setMyTankMemoryLink(_myTank);

	//_structureManager->init(30);




	//_myTank->setEmMemoryLink(_enemyTank);
	//_enemyTank->setMyTankMemoryLink(_myTank);

	return S_OK;
}

//==================================================================
//		## 해제 ## release(void)
//==================================================================
void mission1::release(void)
{
	gameNode::release();
	//이미지 클래스 나갈때까진 사용할 일 없다

	//SAFE_DELETE(_stage1BG);

	_myTank->release();
	//_enemyTank->release();
	_enemyTankManager->release();

	_structureManager->release();

	//_structure1->release();

}

//==================================================================
//		## 업데이트 ## update(void)
//==================================================================
void mission1::update(void)
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다

	_myTank->update();
	//_enemyTank->update();
	_enemyTankManager->update();

	//_myTank->setX(_myTank->getX() - _offsetX);

	//_structure1->update();
	_structureManager->update();

	//_structure1->update();

	collision();

	_viewPointX = _myTank->getX() - WINSIZEX / 2;
	_viewPointY = _myTank->getY() - WINSIZEY / 2;

	if (_myTank->getX() < 400 && _myTank->getY() < 400 && _enemyTankManager->get_vEnemyTank().size() == 0) {
		if (_completeAlpha < 255) {
			++_completeAlpha;
		}
	}
	if (_myTank->getHp() <= 0) {
		if (_gameoverAlpha < 255) {
			++_gameoverAlpha;
		}
	}

	if (_completeAlpha == 255 || _gameoverAlpha == 255) {
		++_waitingTime;
	}

	if (_waitingTime > 100) {
		_toCollectionPage = true;
		_gameoverAlpha = 0;
		_completeAlpha = 0;
		_waitingTime = 0;
		_myTank->setHp(100);
		_myTank->setX(200);
		_myTank->setY(3 * WINSIZEY - 200);
	}

	//_structureManager->update();
}

//==================================================================
//		## 렌더 ## render(HDC hdc)
//==================================================================
void mission1::render(void)
{
	//흰색 빈 비트맵 (이것도 렌더에 그냥 그대로 둘것!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//이곳에서 WM_PAINT에서 했던것을 처리하면 된다
	//==================================================================

	//_stage1BG->render(getMemDC());
	_stage1BG->render(getMemDC(), 0, 0, _viewPointX, _viewPointY, WINSIZEX, WINSIZEY);

	//_structureManager->render();


	//_enemyTank->render();

	_structureManager->render();

	_myTank->render();
	_enemyTankManager->render();

	//_structure1->render();

	//_structure1->render();

	if (_myTank->get_vMissile().size() != 0) {
		for (int i = 0; i < _myTank->get_vMissile().size(); ++i) {
			_myTank->get_vMissile()[i]->render();
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		_targetImage->alphaRender(getMemDC(), _myTank->getX() + cosf(_myTank->getAngle()) *(_myTank->getPower() + 65) - _viewPointX - 28, _myTank->getY() - sinf(_myTank->getAngle()) * (_myTank->getPower() + 65) - _viewPointY - 28, 60);
	}
	//_targetImage->render(getMemDC(),)

	if (_myTank->getX() < 400 && _myTank->getY() < 400 && _enemyTankManager->get_vEnemyTank().size() == 0) {
		_complete->alphaRender(getMemDC(), WINSIZEX / 2 - _complete->getWidth() / 2, WINSIZEY / 2 - _complete->getHeight() / 2, _completeAlpha);
	}

	if (_myTank->getHp() <= 0) {
		_gameover->alphaRender(getMemDC(), WINSIZEX / 2 - _gameover->getWidth() / 2, WINSIZEY / 2 - _gameover->getHeight() / 2, _gameoverAlpha);
	}

	//==================================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 둘것!!)
	this->getBackBuffer()->render(getHDC(), _earthPointX, _earthPointY);
}

//==================================================================
//		## 일반함수 ## (너희들이 만든 함수)
//==================================================================

void mission1::collision(void)
{
	RECT tempRect;

	for (int i = 0; i < _structureManager->get_vStructure().size(); i++) {
		for (int j = 0; j < _enemyTankManager->get_vEnemyTank().size(); j++) {
			if (IntersectRect(&tempRect, &_structureManager->get_vStructure()[i]->getRect(), &_enemyTankManager->get_vEnemyTank()[j]->getRect()) == true) {
				if (tempRect.bottom - tempRect.top < tempRect.right - tempRect.left) {
					if (_structureManager->get_vStructure()[i]->getY() < _enemyTankManager->get_vEnemyTank()[j]->getY()) {
						_enemyTankManager->get_vEnemyTank()[j]->setY(_enemyTankManager->get_vEnemyTank()[j]->getY() + (tempRect.bottom - tempRect.top + 2));
					}
					else {
						_enemyTankManager->get_vEnemyTank()[j]->setY(_enemyTankManager->get_vEnemyTank()[j]->getY() - (tempRect.bottom - tempRect.top + 2));
					}
				}
				else {
					if (_structureManager->get_vStructure()[i]->getX() < _enemyTankManager->get_vEnemyTank()[j]->getX()) {
						_enemyTankManager->get_vEnemyTank()[j]->setX(_enemyTankManager->get_vEnemyTank()[j]->getX() + (tempRect.right - tempRect.left + 2));
					}
					else {
						_enemyTankManager->get_vEnemyTank()[j]->setX(_enemyTankManager->get_vEnemyTank()[j]->getX() - (tempRect.right - tempRect.left + 2));
					}
				}
			}
		}
	}
}