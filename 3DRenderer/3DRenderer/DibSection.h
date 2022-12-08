#pragma once
#include <memory>
#include "Global_struct.h"

struct Color32;

class DibSection
{
public:
	DibSection() = default;
	~DibSection();

public:	
	FORCEINLINE void Sethwnd(const HWND& _hWnd) { hWnd_ = _hWnd; }
	FORCEINLINE void Sethwnd(HWND&& _hwnd) { hWnd_ = std::move(_hwnd); }	
	FORCEINLINE int GetScreenBufferPosition(const int& _ix, const int _iy)
	{
		return _iy * rtClient_.right + _ix;
	}
	void DotPixel(const int& _ix, const int& _iy, const Color32& _Cl);

public:	
	void InitializeDib();
	void ClearDib(const Color32& _color = Color32(255,255,255,0));
	void BitBltDibSection();	

private:
	HWND		hWnd_;
	int			iWidth_;
	int			iHeight_;

	RECT		rtClient_;

	HDC			hScreenDC_;
	HDC			hMemoryDC_;

	HBITMAP		hOldBitmap_;
	HBITMAP		hDIBBitmap_;

	Color32*    ScreenBuffer_ = nullptr;

	std::unique_ptr<BYTE*> pBits_;
};

