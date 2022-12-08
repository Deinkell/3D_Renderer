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
	Color32* dest = ScreenBuffer_;
	*(dest + GetScreenBufferPosition(_ix, _iy)) = _Cl;
}

void DibSection::InitializeDib()
{
	hWnd_ = GetActiveWindow();
	hScreenDC_ = GetDC(hWnd_);
	GetClientRect(hWnd_, &rtClient_);
	iHeight_ = rtClient_.bottom;
	iWidth_ = rtClient_.right;

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
	Color32* dest = ScreenBuffer_;
	UINT32 totalCount = rtClient_.right * rtClient_.bottom;
	memset(ScreenBuffer_, 0, totalCount * sizeof(Color32));
}

void DibSection::BitBltDibSection()
{
	BitBlt(hScreenDC_, 0, 0, rtClient_.right, rtClient_.bottom, hMemoryDC_, 0, 0, SRCCOPY);	
}

