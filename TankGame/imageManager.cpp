#include "stdafx.h"
#include "imageManager.h"
imageManager::imageManager()
{
}
imageManager::~imageManager()
{
}

//이미지 초기화
HRESULT imageManager::init()
{
	return S_OK;
}

//이미지 매니져 해제
void imageManager::release()
{
	deleteAll();
}

//키값으로 빈 비트맵 초기화
image* imageManager::addImage(string strKey, int width, int height)
{
	//추가하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가 하려는 이미지가 존재하면 새로 만들지않고 있는놈 리턴한다.
	if (img) return img;

	//이미지 새로생성
	img = new image;

	//이미지가 제대로 초기화 되었는지 확인
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
// 	image* temp = imageManager->addImage(asdfsda);
// 	imageManager->addImage(asdfsda);
}

//키값으로 이미지 파일로 초기화
image* imageManager::addImage(string strKey, const char* fileName,
	int width, int height, BOOL isTrans, COLORREF transColor)
{
	//추가하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가 하려는 이미지가 존재하면 새로 만들지않고 있는놈 리턴한다.
	if (img) return img;

	//이미지 새로생성
	img = new image;

	//이미지가 제대로 초기화 되었는지 확인
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가
	//_mImageList.insert(make_pair(strKey, img));
	_mImageList.insert(pair<string, image*>(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char* fileName,
	float x, float y,
	int width, int height, BOOL isTrans, COLORREF transColor)
{
	//추가하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가 하려는 이미지가 존재하면 새로 만들지않고 있는놈 리턴한다.
	if (img) return img;

	//이미지 새로생성
	img = new image;

	//이미지가 제대로 초기화 되었는지 확인
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

//키값으로 프레임이미지 파일 초기화
image* imageManager::addFrameImage(string strkey, const char* fileName,
	int width, int height,
	int frameX, int frameY, BOOL isTrans,
	COLORREF transColor)
{
	//추가하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strkey);

	//추가 하려는 이미지가 존재하면 새로 만들지않고 있는놈 리턴한다.
	if (img) return img;

	//이미지 새로생성
	img = new image;

	//이미지가 제대로 초기화 되었는지 확인
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

image* imageManager::addFrameImage(string strkey, const char* fileName,
	float x, float y, int width, int height,
	int frameX, int frameY, BOOL isTrans,
	COLORREF transColor)
{
	//추가하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strkey);

	//추가 하려는 이미지가 존재하면 새로 만들지않고 있는놈 리턴한다.
	if (img) return img;

	//이미지 새로생성
	img = new image;

	//이미지가 제대로 초기화 되었는지 확인
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return NULL;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가
	_mImageList.insert(make_pair(strkey, img));

	return img;
}

//이미지 키값으로 찾기
image* imageManager::findImage(string strKey)
{
	//해당 키검색
	mapImageIter key = _mImageList.find(strKey);

	//검색한 키가 있다면
	if (key != _mImageList.end())
	{
		image* temp = key->second;
		return temp;
	}

	//키를 찾지 못했다면
	return NULL;
}

//이미지 키값으로 삭제
BOOL imageManager::deleteImage(string strKey)
{
	//해당키 검색
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		//이미지 해제
		key->second->release();
		//메모리 해제
		SAFE_DELETE(key->second);
		//멥에서 반복자 삭제
		_mImageList.erase(key);

		return TRUE;
	}

	//키를 찾지 못했다면
	return FALSE;
}

//이미지 전체 삭제
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

	//맵 전체 삭제
	_mImageList.clear();

	return TRUE;
}


//==================================================================
//		## 일반렌더 ##
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
//		## 알파렌더 ##
//==================================================================
void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//만들어 봐라
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight,  alpha);
}

//==================================================================
//		## 프레임렌더 ##
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
//		## 루프 렌더 ##
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

