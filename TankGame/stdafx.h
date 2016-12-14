// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <Windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>


// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
// ���ֻ���ϴ� STL
#include <string>
#include <vector>
#include <map>


//==================================================================
//		## ���� ���� ��������� �̰��� �߰��Ѵ� ##
//==================================================================
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "imageManager.h"
#include "utils.h"
#include "timeManager.h"

//==================================================================
//		## ���ӽ����̽��� �߰��Ѵ� ##
//==================================================================
using namespace MY_UTIL;

//==================================================================
//		## �̱����� �߰��Ѵ� ##
//==================================================================
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()

//==================================================================
//		## �����ι� ## (������â �ʱ�ȭ)
//==================================================================
#define WINNAME (LPTSTR)(TEXT("2D ��Ʈ������"))
#define WINSTARTX 20
#define WINSTARTY 20
#define WINSIZEX	1300
#define WINSIZEY	750
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//==================================================================
//		## ��ũ���Լ� ## (Ŭ�������� �����Ҵ�� �κ� ������ ����Ѵ�)
//==================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p); (p) = NULL;}}

//==================================================================
//		## �������� ## (Ŭ�������� �����Ҵ�� �κ� ������ ����Ѵ�)
//==================================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
