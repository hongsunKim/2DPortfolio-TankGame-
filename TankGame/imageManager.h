#pragma once
#include "singletonBase.h"
#include "image.h"

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*> mapImageList;	//������ ���� �̹��� ���
	typedef map<string, image*>::iterator mapImageIter;

private:
	mapImageList _mImageList;	//������ ������ �̹��� ���

public:
	//�̹��� �ʱ�ȭ
	HRESULT init();
	//�̹��� �Ŵ��� ����
	void release();

	//Ű������ �� ��Ʈ�� �ʱ�ȭ
	image* addImage(string strKey, int width, int height);
	//Ű������ �̹��� ���Ϸ� �ʱ�ȭ
	image* addImage(string strKey, const char* fileName,
		int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(255, 0, 255));
	image* addImage(string strKey, const char* fileName,
		float x, float y, 
		int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	//Ű������ �������̹��� ���� �ʱ�ȭ
	image* addFrameImage(string strkey, const char* fileName,
		int width, int height,
		int frameX, int frameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strkey, const char* fileName,
		float x, float y, int width, int height,
		int frameX, int frameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(255, 0, 255));

	//�̹��� Ű������ ã��
	image* findImage(string strKey);
	//�̹��� Ű������ ����
	BOOL deleteImage(string strKey);
	//�̹��� ��ü ����
	BOOL deleteAll(void);


	//==================================================================
	//		## �Ϲݷ��� ##
	//==================================================================
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//==================================================================
	//		## ���ķ��� ##
	//==================================================================
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//==================================================================
	//		## �����ӷ��� ##
	//==================================================================
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);


	//==================================================================
	//		## ���� ���� ##
	//==================================================================
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);


	imageManager();
	~imageManager();
};

//����
/*
1. ��X, �Ǵ� ��Y *2�� ������ �ʿ��� �÷��̾ �̵��� �ϰ� �Ǹ� ī�޶� ������°���
	Ⱦ��ũ���̶� �ص� ��ֹ��� �־�� �Ѵ�.
	gravity = 0.1f;
	jumpSpeed = 5.0f;

	update()
	���±������� �Ʒ� ���� �����Ѵ�.
	jumpSpeed -= gravity;
	_aladin->getY() += jumpSpeed;
	
	(�ɼ�)
2.�̴ϸ��� �����.

*/