#include "stdafx.h"
#include "Input.h"

void Input::MouseMoveCheck()
{
	GetCursorPos(&MouseXY);
	MouseXY.x = ClientX - MouseXY.x;
	MouseXY.y = ClientY - MouseXY.y;

	SetCursorPos(ClientX, ClientY);
}

void Input::Update()
{
	if (GetNum1Pressd()) LastKey = VK_NUM1;
	if (GetNum2Pressd()) LastKey = VK_NUM2;
	
	if (GetRBUTTONPressing()) MouseMoveCheck();
}
