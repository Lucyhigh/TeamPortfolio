#include "Stdafx.h"
#include "Image.h" 
#include "Animation.h"

// 알파 블렌드를 사용하기 위한 라이브러리 추가 
#pragma comment (lib,"msimg32.lib")

// 동적할당을 통해 상속받은 클래스에서 생성자 호출할때 
// 이니셜라이저 초기화를 통해 최우선적으로 초기화를 하라는 의미 . 
Image::Image() : _imageInfo(NULL)
, _fileName(NULL)
, _isTrans(FALSE)
, _transColor(RGB(0, 0, 0))
, _blendImage(NULL)
{
}

// 이미지 초기화
HRESULT Image::init(int width, int height)
{
	// 포인터를 사용하기때문에 if로 한번 더 확인한다. 
	// 재초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);//1
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);//2
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름
	_fileName = NULL;
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	// 리소스를 얻어오는데 실패했으면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	// 재초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE; //
	_imageInfo->resID = resID; // 사용할 리소스ID
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo)); // _imageInfo res에서 변경
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름 - 리소스 사용으로 없음. 
	_fileName = NULL;
	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했으면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	// 재초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // 파일로드 
	_imageInfo->resID = 0; // 리소스 아이디는 없음
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름 - 문자/문자열 확인 
	// _fileName = fileName; ->const로 그대로 사용할 수 없기때문에, 아래처럼 기재.

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // 파일 경로 뒤 공백 1칸 실수 방지용
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했으면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}


// 프레임 이미지 초기화
HRESULT Image::init(const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{

	// 재초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // 파일로드 
	_imageInfo->resID = 0; // 리소스 아이디는 없음
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	// 파일 이름 - 문자/문자열 확인 
	// _fileName = fileName; ->const로 그대로 사용할 수 없기때문에, 아래처럼 기재.

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // 파일 경로 뒤 공백 1칸 실수 방지용
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했으면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;

}

HRESULT Image::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	// 재초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // 파일로드 
	_imageInfo->resID = 0; // 리소스 아이디는 없음
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	// 파일 이름 - 문자/문자열 확인 
	// _fileName = fileName; ->const로 그대로 사용할 수 없기때문에, 아래처럼 기재.

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // 파일 경로 뒤 공백 1칸 실수 방지용
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했으면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT Image::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
{
	// 재초기화 방지 -> 이미지 정보에 값이 들어있다면 릴리즈부터 하겠다.
	if (_imageInfo != NULL) this->release();

	// DC 가져오기
	HDC hdc = GetDC(_hWnd);

	// 이미지 정보 새로 생성 후 초기화
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE; // 파일로드 
	_imageInfo->resID = 0; // 리소스 아이디는 없음
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP,
		width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	// 파일 이름 - 문자/문자열 확인 
	// _fileName = fileName; ->const로 그대로 사용할 수 없기때문에, 아래처럼 기재.

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1]; // 파일 경로 뒤 공백 1칸 실수 방지용
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	// 리소스를 얻어오는데 실패했으면
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

// 알파블렌드 초기화
HRESULT Image::initForAlphaBlend(void)
{

	HDC hdc = GetDC(_hWnd);

	_blendFunc.BlendFlags = 0; // 혼합비율 사용안함
	_blendFunc.AlphaFormat = 0; // 이미지 + 소스 제어 or 이미지 제어 여부
	_blendFunc.BlendOp = AC_SRC_OVER; // 비트맵 이미지 비트 수 24 or 32 사용함


	// 이미지 정보 새로 생성 후 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE; // 파일로드 
	_blendImage->resID = 0; // 리소스 아이디는 없음
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZE_X;
	_blendImage->height = WINSIZE_Y;


	// DC해제
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

// 투명 컬러키 셋팅
void Image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

// 해제 
void Image::release(void) // 포인터를 사용한다면 해제(release)를 신경쓰자.
{
	if (_imageInfo) // 이미지가 있으면
	{
		// 이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}


	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		SAFE_DELETE(_blendImage);
	}
}

// 렌더 (0.0에 그려짐)
void Image::render(HDC hdc)
{
	if (_isTrans) // 색이 빠질 것들. 플레이어, 오브젝트 등등...
	{
		// 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수 
		GdiTransparentBlt // 해제전까지 메모리에 상주함.
		(
			hdc,					// 복사할 장소의 DC(화면DC(화면에 보여줄))
			0, 0,					// 복사될 좌표 시작 : X, Y
			_imageInfo->width,		// 복사할 이미지 크기 : 가로, 세로
			_imageInfo->height,
			//------------------------------------------------------------------
			_imageInfo->hMemDC,		// 복사될 대상의 메모리DC
			0, 0,					// 복사 시작 지점 : X, Y
			_imageInfo->width,		// 복사 영역 크기 : 가로, 세로 
			_imageInfo->height,
			//------------------------------------------------------------------
			_transColor				// 복사할 때 제외할 색상
		);
	}

	// 복사로 인한 컴퓨터 구조(메모리)의 병목현상을 방지하기 위해 , else를 사용함
	else // 맵, 화면 전체적으로 들어가는 이미지 등 ...
	{
		// DC간의 영역끼리 서로 고속복사 해주는 함수
		// SRCCOPY : 소스 영역을 대상영역에 복사한다.
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}

// 렌더 (내가 설정한 좌표 x,y 에 그려짐)
void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) // 색이 빠질 것들. 플레이어, 오브젝트 등등...
	{
		// 비트맵을 불러올때 특정색상을 제외하고 복사해주는 함수 
		GdiTransparentBlt // 해제전까지 메모리에 상주함.
		(
			hdc,					// 복사할 장소의 DC(화면DC(화면에 보여줄))
			destX, destY,			// 복사될 좌표 시작 : X, Y
			_imageInfo->width,		// 복사할 이미지 크기 : 가로, 세로
			_imageInfo->height,
			//------------------------------------------------------------------
			_imageInfo->hMemDC,		// 복사될 대상의 메모리DC
			0, 0,					// 복사 시작 지점 : X, Y
			_imageInfo->width,		// 복사 영역 크기 : 가로, 세로 
			_imageInfo->height,
			//------------------------------------------------------------------
			_transColor				// 복사할 때 제외할 색상
		);
	}

	else // 맵, 화면 전체적으로 들어가는 이미지 등 ...
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//클리핑 렌더
void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,					// 복사할 장소의 DC(화면DC(화면에 보여줄))
			destX, destY,			// 복사될 좌표 시작 : X, Y
			sourWidth,				// 복사할 이미지 크기 : 가로, 세로
			sourHeight,
			//------------------------------------------------------------------
			_imageInfo->hMemDC,		// 복사될 대상의 메모리DC
			sourX, sourY,			// 복사 시작 지점 : X, Y
			sourWidth,				// 복사 영역 크기 : 가로, 세로 
			sourHeight,
			//------------------------------------------------------------------
			_transColor				// 복사할 때 제외할 색상
		);
	}

	else // 맵, 화면 전체적으로 들어가는 이미지 등 ...
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}


}

// 알파렌더(배경)
void Image::alphaRender(HDC hdc, BYTE alpha)
{
	// 알파블랜드를 처음 사용하는지 확인
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// 1 출력해야할 DC에 그려져 있는 내용을 블렌드 이미지에 그린다. 
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc, 0, 0, SRCCOPY);


		// 2 원본 이미지 배경을 없앤 후 블랜드 이미지에 그린다.
		GdiTransparentBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_transColor
		);

		// 3 블렌드 이미지를 화면에 그린다 
		AlphaBlend
		(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC, // 지뢰조심
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc // 지뢰조심
		);
	}
	else // 맵, 화면 전체적으로 들어가는 이미지 등 ...
	{
		AlphaBlend
		(
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC, // 지뢰조심
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc // 지뢰조심
		);
	}
}

// 알파렌더(플레이어)
void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	// 알파블랜드를 처음 사용하는지 확인
	if (!_blendImage) initForAlphaBlend();

	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		// 1 출력해야할 DC에 그려져 있는 내용을 블렌드 이미지에 그린다. 
		BitBlt
		(
			_blendImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			destX, destY, SRCCOPY
		);


		// 2 원본 이미지 배경을 없앤 후 블랜드 이미지에 그린다.
		GdiTransparentBlt
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			//------------------
			_transColor
		);

		// 3 블렌드 이미지를 화면에 그린다 
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_blendImage->hMemDC, // 지뢰조심
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}
	else {
		AlphaBlend
		(
			hdc,
			destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc);
	}

}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
}

void Image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,						// 복사할 장소의 DC(화면DC(화면에 보여줄))
			destX, destY,				// 복사될 좌표 시작 : X, Y
			_imageInfo->frameWidth,		// 복사할 이미지 크기 : 가로, 세로
			_imageInfo->frameHeight,
			//------------------------------------------------------------------
			_imageInfo->hMemDC,			// 복사될 대상의 메모리DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,			// 복사 시작 지점 : X, Y
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		// 복사 영역 크기 : 가로, 세로 
			_imageInfo->frameHeight,
			//------------------------------------------------------------------
			_transColor					// 복사할 때 제외할 색상
		);
	}

	else // 맵, 화면 전체적으로 들어가는 이미지 등 ...
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	// 이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)
	{
		GdiTransparentBlt
		(
			hdc,					// 복사할 장소의 DC(화면DC(화면에 보여줄))
			destX, destY,			// 복사될 좌표 시작 : X, Y
			_imageInfo->frameWidth,				// 복사할 이미지 크기 : 가로, 세로
			_imageInfo->frameHeight,
			//------------------------------------------------------------------
			_imageInfo->hMemDC,		// 복사될 대상의 메모리DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,			// 복사 시작 지점 : X, Y
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,				// 복사 영역 크기 : 가로, 세로 
			_imageInfo->frameHeight,
			//------------------------------------------------------------------
			_transColor				// 복사할 때 제외할 색상
		);
	}

	else // 맵, 화면 전체적으로 들어가는 이미지 등 ...
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset 값이 음수인 경우 보정을 하겠다.
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 셋팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC영역(화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면 (화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 올려주겠다.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth - rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}//end of second for
	}//end of for

}

void Image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
}

void Image::aniRender(HDC hdc, int destX, int destY, Animation * ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight());
}

