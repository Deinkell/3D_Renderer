#include "stdafx.h"
#include "FrameWork.h"

void FrameWork::Initialize()
{
	Dib.InitializeDib();
}

void FrameWork::Ontick()
{
	static Color32 Cor(255,255,0,0);

	for (int i = 0; i < 100; i++)
		Dib.DotPixel(200 + i, 200 + i, test());	

	Dib.BitBltDibSection();
}
