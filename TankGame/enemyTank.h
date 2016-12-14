#pragma once
#include "gameNode.h"
#include "missile.h"
#include "hpBar.h"

#define BODYDEGREE (int(_bodyAngle / (PI / 180)))
#define CANNONDEGREE (int(_cannonAngle / (PI / 180)))

class myTank;
class structureManager;

class enemyTank : public gameNode
{
private:

	image* _cannonImage;
	image* _bodyImage;
	float _cannonAngle;
	float _bodyAngle;
	float _power;//ĳ�� range
	float _speed;
	float _speedDst;
	float _angle;
	float _angleDst;
	float _x;	//�߽���
	float _y;	//�߽���

	int _fireCount;

	hpBar* _hpBar;

	RECT _rect;//�浹�� �簢��... �簢�簢

	vector<missile*> _vMissile;
	vector<missile*>::iterator _viMissile;

	TCHAR debug[1024];

	float _fullHp;
	float _currentHp;


	myTank* _myTank;
	structureManager* _structureManager;


	//�����˿� ���� Ŭ������ ���ԵǾ����

public:

	inline void setHp(float currentHp) { _currentHp = currentHp; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	inline float getPower() { return _power; }
	inline float getCannonAngle() { return _cannonAngle; }
	inline float getX() { return _x; }
	inline float getY() { return _y; }
	inline float getHp() { return _currentHp; }
	inline float getSpeed() { return _speed; }

	RECT getRect() { return _rect; }

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move(void);

	void damageCheck(void);

	void collisionCheck(void);

	void setMyTankMemoryLink(myTank* myTank) { _myTank = myTank; }
	void setStructManagerMemoryLink(structureManager* structureManager) { _structureManager = structureManager; }

	enemyTank();
	~enemyTank();
};