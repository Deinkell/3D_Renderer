#include "stdafx.h"
#include "Quaternion.h"

Quaternion Quaternion::GetNormal()
{	
	return std::move(MathLib::GetNormal(*this)); 
}; //헤더에서 네임스페이스 사용x