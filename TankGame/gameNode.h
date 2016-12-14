#pragma once
#include "image.h"

//백버퍼 이미지를 스태틱으로 만들어 두기
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);



class gameNode
{
protected:
	static float _viewPointX;
	static float _viewPointY;

	static float _earthPointX;
	static float _earthPointY;

private:
	//image* _backBuffer;				//백버퍼 이미지
	//void setBackBuffer(void);		//백버퍼 셋팅하기

	HDC _hdc;					//HDC
	bool _managerInit;		//매니처 초기화 했는지?

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//백버퍼 이미지 얻기
	image* getBackBuffer(void) { return _backBuffer; }
	//메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC 얻기
	HDC getHDC() { return _hdc; }
	

	//메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode();
	virtual ~gameNode();
};

