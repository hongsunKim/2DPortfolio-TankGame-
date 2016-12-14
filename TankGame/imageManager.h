#pragma once
#include "singletonBase.h"
#include "image.h"

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*> mapImageList;	//맵으로 만든 이미지 목록
	typedef map<string, image*>::iterator mapImageIter;

private:
	mapImageList _mImageList;	//맵으로 구현된 이미지 목록

public:
	//이미지 초기화
	HRESULT init();
	//이미지 매니져 해제
	void release();

	//키값으로 빈 비트맵 초기화
	image* addImage(string strKey, int width, int height);
	//키값으로 이미지 파일로 초기화
	image* addImage(string strKey, const char* fileName,
		int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(string strKey, const char* fileName,
		float x, float y, 
		int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	//키값으로 프레임이미지 파일 초기화
	image* addFrameImage(string strkey, const char* fileName,
		int width, int height,
		int frameX, int frameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strkey, const char* fileName,
		float x, float y, int width, int height,
		int frameX, int frameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(255, 0, 255));

	//이미지 키값으로 찾기
	image* findImage(string strKey);
	//이미지 키값으로 삭제
	BOOL deleteImage(string strKey);
	//이미지 전체 삭제
	BOOL deleteAll(void);


	//==================================================================
	//		## 일반렌더 ##
	//==================================================================
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//==================================================================
	//		## 알파렌더 ##
	//==================================================================
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//==================================================================
	//		## 프레임렌더 ##
	//==================================================================
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);


	//==================================================================
	//		## 루프 렌더 ##
	//==================================================================
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);


	imageManager();
	~imageManager();
};

//숙제
/*
1. 윈X, 또는 윈Y *2배 싸이즈 맵에서 플레이어가 이동을 하게 되면 카메라가 따라오는게임
	횡스크롤이라 해도 장애물이 있어야 한다.
	gravity = 0.1f;
	jumpSpeed = 5.0f;

	update()
	상태구문으로 아래 값을 적용한다.
	jumpSpeed -= gravity;
	_aladin->getY() += jumpSpeed;
	
	(옵션)
2.미니맵을 만든다.

*/