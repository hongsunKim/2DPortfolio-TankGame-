#include "stdafx.h"
#include "imageManager.h"
imageManager::imageManager()
{
}
imageManager::~imageManager()
{
}

//�̹��� �ʱ�ȭ
HRESULT imageManager::init()
{
	return S_OK;
}

//�̹��� �Ŵ��� ����
void imageManager::release()
{
	deleteAll();
}

//Ű������ �� ��Ʈ�� �ʱ�ȭ
image* imageManager::addImage(string strKey, int width, int height)
{
	//�߰��Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �����ϸ� ���� �������ʰ� �ִ³� �����Ѵ�.
	if (img) return img;

	//�̹��� ���λ���
	img = new image;

	//�̹����� ����� �ʱ�ȭ �Ǿ����� Ȯ��
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
// 	image* temp = imageManager->addImage(asdfsda);
// 	imageManager->addImage(asdfsda);
}

//Ű������ �̹��� ���Ϸ� �ʱ�ȭ
image* imageManager::addImage(string strKey, const char* fileName,
	int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �����ϸ� ���� �������ʰ� �ִ³� �����Ѵ�.
	if (img) return img;

	//�̹��� ���λ���
	img = new image;

	//�̹����� ����� �ʱ�ȭ �Ǿ����� Ȯ��
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰�
	//_mImageList.insert(make_pair(strKey, img));
	_mImageList.insert(pair<string, image*>(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName,
	float x, float y,
	int width, int height, BOOL isTrans, COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �����ϸ� ���� �������ʰ� �ִ³� �����Ѵ�.
	if (img) return img;

	//�̹��� ���λ���
	img = new image;

	//�̹����� ����� �ʱ�ȭ �Ǿ����� Ȯ��
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//Ű������ �������̹��� ���� �ʱ�ȭ
image* imageManager::addFrameImage(string strkey, const char* fileName,
	int width, int height,
	int frameX, int frameY, BOOL isTrans,
	COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strkey);

	//�߰� �Ϸ��� �̹����� �����ϸ� ���� �������ʰ� �ִ³� �����Ѵ�.
	if (img) return img;

	//�̹��� ���λ���
	img = new image;

	//�̹����� ����� �ʱ�ȭ �Ǿ����� Ȯ��
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰�
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

image* imageManager::addFrameImage(string strkey, const char* fileName,
	float x, float y, int width, int height,
	int frameX, int frameY, BOOL isTrans,
	COLORREF transColor)
{
	//�߰��Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strkey);

	//�߰� �Ϸ��� �̹����� �����ϸ� ���� �������ʰ� �ִ³� �����Ѵ�.
	if (img) return img;

	//�̹��� ���λ���
	img = new image;

	//�̹����� ����� �ʱ�ȭ �Ǿ����� Ȯ��
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰�
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

//�̹��� Ű������ ã��
image* imageManager::findImage(string strKey)
{
	//�ش� Ű�˻�
	mapImageIter key = _mImageList.find(strKey);

	//�˻��� Ű�� �ִٸ�
	if (key != _mImageList.end())
	{
		image* temp = key->second;
		return temp;
	}

	//Ű�� ã�� ���ߴٸ�
	return NULL;
}

//�̹��� Ű������ ����
BOOL imageManager::deleteImage(string strKey)
{
	//�ش�Ű �˻�
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		//�̹��� ����
		key->second->release();
		//�޸� ����
		SAFE_DELETE(key->second);
		//�㿡�� �ݺ��� ����
		_mImageList.erase(key);

		return TRUE;
	}

	//Ű�� ã�� ���ߴٸ�
	return FALSE;
}

//�̹��� ��ü ����
BOOL imageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();
// 	map<string, image*>::iterator i = _mImageList.begin()
// 	for (map<string, image*>::iterator i = _mImageList.begin(); iter != _mImageList.end();)
	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			//iter->second == image* temp
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	//�� ��ü ����
	_mImageList.clear();

	return TRUE;
}


//==================================================================
//		## �Ϲݷ��� ##
//==================================================================
void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

//==================================================================
//		## ���ķ��� ##
//==================================================================
void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//����� ����
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight,  alpha);
}

//==================================================================
//		## �����ӷ��� ##
//==================================================================
void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}


//==================================================================
//		## ���� ���� ##
//==================================================================
void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}

