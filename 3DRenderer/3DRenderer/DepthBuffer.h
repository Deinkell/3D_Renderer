#pragma once

class DepthBuffer
{
private:
	float* DepthBufferBlock;
	int SizeOfDepthBuffer;
	int ClientWidth, ClientHeight;	

public:
	DepthBuffer() = default;
	~DepthBuffer() { if (DepthBufferBlock != nullptr) delete[] DepthBufferBlock; }

public:
	FORCEINLINE bool CheckDepthBuffer(const int& _x, const int& _y, const float& _Depth)
	{
		if (_x < 0 || _x >= ClientWidth || _y < 0 || _y >= ClientHeight)
			return false;

		float* depth = DepthBufferBlock;
		depth += (_x + ClientHeight * _y);
		
		if (*depth <= _Depth || _Depth < -1.f || _Depth > 0.f)
			return false;

		*depth = _Depth;
		return true;
	}
	FORCEINLINE void ClearDepthBuffer() { std::fill(DepthBufferBlock, DepthBufferBlock + SizeOfDepthBuffer, 1.0f); }

public:
	void Initialize(const int& _ClientWid, const int& _ClientHgt);
};

