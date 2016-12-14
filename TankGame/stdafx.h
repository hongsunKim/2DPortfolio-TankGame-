// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>


// C++ 런타임 헤더 파일입니다.
#include <iostream>
// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>


//==================================================================
//		## 내가 만든 헤더파일을 이곳에 추가한다 ##
//==================================================================
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "imageManager.h"
#include "utils.h"
#include "timeManager.h"

//==================================================================
//		## 네임스페이스을 추가한다 ##
//==================================================================
using namespace MY_UTIL;

//==================================================================
//		## 싱글톤을 추가한다 ##
//==================================================================
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()

//==================================================================
//		## 디파인문 ## (윈도우창 초기화)
//==================================================================
#define WINNAME (LPTSTR)(TEXT("2D 포트폴리오"))
#define WINSTARTX 20
#define WINSTARTY 20
#define WINSIZEX	1300
#define WINSIZEY	750
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//==================================================================
//		## 메크로함수 ## (클래스에서 동적할당된 부분 해제시 사용한다)
//==================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p); (p) = NULL;}}

//==================================================================
//		## 전역변수 ## (클래스에서 동적할당된 부분 해제시 사용한다)
//==================================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
