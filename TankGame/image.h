#pragma once
//==================================================================
//		## image ## (앞으로 계속 업데이트 된다)
//==================================================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		//리소스로 로딩
		LOAD_FILE,				//파일로 로딩
		LOAD_EMPTY,				//빈비트맵 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;		//리소스 ID
		HDC			hMemDC;		//메모리 DC
		HBITMAP		hBit;		//비트맵
		HBITMAP		hOBit;		//올드비트맵
		int			width;		//이미지 가로크기
		int			height;		//이미지 세로크기
		BYTE		loadType;	//이미지 로드타입

		//프레임렌더 추가하면서
		float		x;			//이미지 x좌표(센터)
		float		y;			//이미지 y좌표(센터)

		int			currentFrameX;	//현재 프레임x
		int			currentFrameY;	//현재 프레임y
		int			maxFrameX;		//최대 프레임x
		int			maxFrameY;		//최대 프레임y
		int			frameWidth;		//1프레임 가로크기
		int			frameHeight;	//1프레임 세로크기

		//RECT _rc; //불필요한 인자들은 줄인다.
	
		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;

			x = 0;
			y = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//이미지 이름
	BOOL			_isTrans;		//배경색 없앨거냐? (마젠타)
	COLORREF		_transColor;	//배경색 없앨 RGB (마젠타 = RGB(255, 0, 255))

	BLENDFUNCTION	_blendFunc;		//알파블렌드 기능
	LPIMAGE_INFO	_blendImage;	//알파블렌드 이미지

public:
	image();
	~image();

	//빈 비트맵으로 초기화
	HRESULT init(int width, int height);
	//이미지 리소스로 초기화 (사용안함)
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//이미지 파일로 초기화 (주 사용)
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//센터로 초기화
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//알파블렌드 초기화
	HRESULT initForAlphaBlend(void);

	//프레임렌더용 초기화
	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, 
		BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y,
		int width, int height,
		int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));


	//투명키 셋팅
	void setTransColor(BOOL isTrans, COLORREF transColor);

	void setImageSize(int width, int height) { _imageInfo->width = width; _imageInfo->height = height; }

	//해제
	void release(void);

//==================================================================
//		## 일반렌더 ##
//==================================================================
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

//==================================================================
//		## 알파렌더 ##
//==================================================================
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

//==================================================================
//		## 프레임렌더 ##
//==================================================================
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, float scale);
	void frameRender(HDC hdc, int destX, int destY, int currentX, int currentY);
	void frameRender(HDC hdc, int destX, int destY, int currentX, int currentY, float scale);


//==================================================================
//		## 루프 렌더 ##
//==================================================================
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

//==================================================================
//		## inline 함수 ## imageInfo의 맴버 겟터, 셋터
//==================================================================
	//DC 얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//이미지 좌표 x
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	//이미지 좌표 y
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//이미지 센터 좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//이미지 가로, 세로 크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	//프레임 x
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		//숫자를 ++으로 쓰다 멕스가 넘어갔다.
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}//프레임 y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		//숫자를 ++으로 쓰다 멕스가 넘어갔다.
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//1프레임 가로, 세로 크기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	//맥스 프레임 x, y
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }


	//바운딩박스(충돌용)
	inline RECT getBoundingBox(void)
	{
		/*RECT rc = (RectMakeCenter(_imageInfo->x, _imageInfo->y,
			_imageInfo->width, _imageInfo->height));*/
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height };

		return rc;
	}

	inline RECT getBoundingBoxWithFrame(void)
	{
		//프레임렌더 사용시 1프레임의 랙트를 반환 시키기
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight };

		return rc;
	}
};

