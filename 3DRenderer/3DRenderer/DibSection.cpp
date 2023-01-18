#include "stdafx.h"
#include "DibSection.h"

DibSection::~DibSection()
{
	DeleteObject(hOldBitmap_);
	DeleteObject(hDIBBitmap_);
	ReleaseDC(hWnd_, hScreenDC_);
	ReleaseDC(hWnd_, hMemoryDC_);
}

void DibSection::DotPixel(const int& _ix, const int& _iy, const Color32& _Cl)
{
	if (_ix < 0 || _iy < 0 || _ix >= rtClient_.right || _iy >= rtClient_.bottom)
		return;

	Color32* dest = ScreenBuffer_;
	*(dest + GetScreenBufferPosition(_ix, _iy)) = _Cl;
}

void DibSection::InitializeDib(HWND _hWnd)
{
	hWnd_ = _hWnd;
	hScreenDC_ = GetDC(hWnd_);
	GetClientRect(hWnd_, &rtClient_);
	iHeight_ = rtClient_.bottom;
	iWidth_ = rtClient_.right;
	accumulate_ElapsedTime = 0;
	CountCallFps = 0;

	hMemoryDC_ = CreateCompatibleDC(hScreenDC_);

	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = rtClient_.right;
	bmi.bmiHeader.biHeight = -rtClient_.bottom;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	hDIBBitmap_ = CreateDIBSection(hMemoryDC_, &bmi, DIB_RGB_COLORS, (void**)&ScreenBuffer_, NULL, 0);
	hOldBitmap_ = (HBITMAP)SelectObject(hMemoryDC_, hDIBBitmap_);
}

void DibSection::ClearDib(const Color32& _color)
{	
	UINT32 totalCount = rtClient_.right * rtClient_.bottom;
	memset(ScreenBuffer_, _color.ColorValue, totalCount * sizeof(Color32));
}

void DibSection::BitBltDibSection()
{
	BitBlt(hScreenDC_, 0, 0, rtClient_.right, rtClient_.bottom, hMemoryDC_, 0, 0, SRCCOPY);	
	ClearDib(Color32(255, 255, 255, 255));
}

void DibSection::SetWindowsTitleFPS(const float& _elapsedTime)
{
	accumulate_ElapsedTime += _elapsedTime;
	CountCallFps++;

	if (accumulate_ElapsedTime >= 0.5f)
	{
		//_stprintf_s(Title, _T("3DRenderer : [%.f fps]"), 1.f * CountCallFps / accumulate_ElapsedTime );
		_stprintf_s(Title, _T("3DRenderer : [%d fps]"), CountCallFps*2);
		::SetWindowText(hWnd_, Title);
		accumulate_ElapsedTime = 0;
		CountCallFps = 0;
	}	
}

void DibSection::SetStaticText(std::vector<std::string>& _Text)
{
	HFONT hFont, hOldFont;
	hFont = (HFONT)GetStockObject(ANSI_VAR_FONT);
	hOldFont = (HFONT)SelectObject(hMemoryDC_, hFont);

	static const int leftPosition = 20;
	static const int topPosition = 10;
	static const int rowHeight = 20;
	int currentPosition = topPosition;

	for (std::vector<std::string>::const_iterator it = _Text.begin(); it != _Text.end(); ++it)
	{
		TextOutA(hMemoryDC_, leftPosition, currentPosition, (*it).c_str(), (int)((*it).length()));
		currentPosition += rowHeight;
	}

	SelectObject(hMemoryDC_, hOldFont);
}

