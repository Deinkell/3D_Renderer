#pragma once

#include <memory>
#include <vector>
#include "Color32.h"

class DibSection
{
private:
	HWND		hWnd_;
	int			iWidth_;
	int			iHeight_;

	RECT		rtClient_;

	HDC			hScreenDC_;
	HDC			hMemoryDC_;

	HBITMAP		hOldBitmap_;
	HBITMAP		hDIBBitmap_;

	Color32* ScreenBuffer_ = nullptr;

	std::unique_ptr<BYTE*> pBits_;
	TCHAR Title[128];
	double accumulate_ElapsedTime;
	int CountCallFps;

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
	FORCEINLINE int GetClientX() { return rtClient_.right; }
	FORCEINLINE int GetClientY() { return rtClient_.bottom; }
	FORCEINLINE bool CheckIntersectClientRect(const int& _x, const int& _y)
	{	return (_x < 0 || _x > rtClient_.right || _y < 0 || _y > rtClient_.bottom) ? false : true;	}
	void DotPixel(const int& _ix, const int& _iy, const Color32& _Cl);

public:	
	void InitializeDib(HWND _hWnd);
	void ClearDib(const Color32& _color = Color32(255,255,255,0));
	void BitBltDibSection();	
	void SetWindowsTitleFPS(const float& _elapsedTime);
	void SetStaticText(std::vector<std::string>& _Text);
};

