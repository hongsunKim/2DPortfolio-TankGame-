#include "stdafx.h"
#include "gameNode.h"

float gameNode::_viewPointX = 0;
float gameNode::_viewPointY = 0;

float gameNode::_earthPointX = 0;
float gameNode::_earthPointY = 0;

gameNode::gameNode()
{
}
gameNode::~gameNode()
{
}
//==================================================================
//		## ���̻� ������, �Ҹ��ڴ� ������� �ʴ´� ##
//==================================================================

//==================================================================
//		## �ʱ�ȭ ## init(void)
//==================================================================
HRESULT gameNode::init(void)
{
	SetTimer(_hWnd, 1, 10, NULL);			//Ÿ�̸� �ʱ�ȭ
	_managerInit = false;
	
	return S_OK;
}

//==================================================================
//		## �ʱ�ȭ ## init(bool managerInit)
//==================================================================
HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);			//Ÿ�̸� �ʱ�ȭ
		KEYMANAGER->init();						//Ű�Ŵ��� �ʱ�ȭ
		IMAGEMANAGER->init();					//�̹����Ŵ��� �ʱ�ȭ
		TIMEMANAGER->init();
	}

	return S_OK;
}

//==================================================================
//		## ���� ## release(void)
//==================================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//Ÿ�̸� ����
		KillTimer(_hWnd, 1);

		//Ű�Ŵ��� ����
		KEYMANAGER->releaseSingleton();
		//�̹����Ŵ��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		TIMEMANAGER->release();
	}
	
	//DC ����
	ReleaseDC(_hWnd, _hdc);
}

//==================================================================
//		## ������Ʈ ## update(void)
//==================================================================
void gameNode::update(void)
{
	//���ΰ�ħ(���߿� ���� Ÿ�̸Ӹ� ������ �����Ѵ�)
	//InvalidateRect(_hWnd, NULL, FALSE);
}

//==================================================================
//		## ���� ## render(void)//�Ű����� HDC hdc�� ����� ����ƽ���� ���鼭 ����.
//==================================================================
void gameNode::render(void)
{
}

//==================================================================
//		## ���� ���ν��� ## 
//==================================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	//case WM_TIMER:
	//	this->update();
	//	break;
	//case WM_PAINT:
	//	hdc = BeginPaint(hWnd, &ps);
	//	this->render();
	//	EndPaint(hWnd, &ps);
	//	break;
	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}