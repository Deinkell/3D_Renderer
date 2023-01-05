#include "stdafx.h"
#include "DepthBuffer.h"

void DepthBuffer::Initialize(const int& _ClientWid, const int& _ClientHgt)
{
	DepthBufferBlock = nullptr;
	ClientWidth = _ClientWid; 
	ClientHeight = _ClientHgt;
	SizeOfDepthBuffer = _ClientWid * _ClientHgt;	

	DepthBufferBlock = new float[SizeOfDepthBuffer]; 
	std::fill(DepthBufferBlock, DepthBufferBlock + SizeOfDepthBuffer, 1.0f);
}