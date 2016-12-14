#pragma once
#include "gameNode.h"
#include "missile.h"
#include "hpBar.h"

#define BODYDEGREE (int(_bodyAngle / (PI / 180)))
#define CANNONDEGREE (int(_cannonAngle / (PI / 180)))

class structureManager;
class enemyTankManager;

class myTank : public gameNode
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
	RECT _rect;//�浹�� �簢��... �簢�簢

	hpBar* _hpBar;

	vector<missile*> _vMissile;
	vector<missile*>::iterator _viMissile;

	structureManager* _structureManager;
	enemyTankManager* _enemyTankManager;


	TCHAR debug[1024];

	float _fullHp;
	float _currentHp;


	//�����˿� ���� Ŭ������ ���ԵǾ����

public:

	inline void setHp(float currentHp) { _currentHp = currentHp; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	inline float getPower() { return _power; }
	inline float getAngle() { return _cannonAngle; }
	inline float getX() { return _x; }
	inline float getY() { return _y; }
	inline float getHp() { return _currentHp; }
	inline float getSpeed() { return _speed; }

	vector<missile*> get_vMissile() { return _vMissile; }
	vector<missile*>::iterator get_viMissile() { return _viMissile; }
	void set_viMissile(vector<missile*>::iterator viMissile) { _viMissile = viMissile; }

	RECT getRect() { return _rect; }

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move(void);

	void setEnemyTankManagerMemoryLink(enemyTankManager* enemyTankManager) { _enemyTankManager = enemyTankManager; }

	void damageCheck(void);

	void collisionCheck(void);

	myTank();
	~myTank();
};