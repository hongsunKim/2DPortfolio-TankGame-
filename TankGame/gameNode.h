#pragma once
#include "image.h"

//����� �̹����� ����ƽ���� ����� �α�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);



class gameNode
{
protected:
	static float _viewPointX;
	static float _viewPointY;

	static float _earthPointX;
	static float _earthPointY;

private:
	//image* _backBuffer;				//����� �̹���
	//void setBackBuffer(void);		//����� �����ϱ�

	HDC _hdc;					//HDC
	bool _managerInit;		//�Ŵ�ó �ʱ�ȭ �ߴ���?

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//����� �̹��� ���
	image* getBackBuffer(void) { return _backBuffer; }
	//�޸� DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC ���
	HDC getHDC() { return _hdc; }
	

	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode();
	virtual ~gameNode();
};

