#pragma once

#define VK_NUM1 0x31
#define VK_NUM2 0x32
#define VK_RBUTTON 0x02

class Input
{
private:
	int LastKey;
	POINT MouseXY;
	int ClientX, ClientY;

public:
	template<typename T> requires std::is_fundamental_v<T>
	Input(T&& _ClientX, T&& _ClientY)
	: LastKey(0), MouseXY(0), ClientX(std::forward<int>(_ClientX)), ClientY(std::forward<int>(_ClientY)) {};
	~Input() = default;

public:
	FORCEINLINE constexpr int GetLastKey() { return LastKey; }
	FORCEINLINE constexpr POINT GetMouseXY() { return MouseXY; }
	FORCEINLINE bool GetKeyPressed(int _PressKey){ return GetAsyncKeyState(_PressKey) & 0x0001; }
	FORCEINLINE bool GetKeyPressing(int _PressKey) { return GetAsyncKeyState(_PressKey) & 0x8000; }

public:
	FORCEINLINE bool GetNum1Pressd() { return GetKeyPressed(VK_NUM1); }
	FORCEINLINE bool GetNum2Pressd() { return GetKeyPressed(VK_NUM2); }
	FORCEINLINE bool GetRBUTTONPressing() { return GetKeyPressing(VK_RBUTTON); }

public:
	void MouseMoveCheck();

public:
	void Update();
};

