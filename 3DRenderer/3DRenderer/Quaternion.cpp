#include "stdafx.h"
#include "Quaternion.h"

Quaternion Quaternion::GetNormal()
{	
	return std::move(MathLib::GetNormal(*this)); 
}; //������� ���ӽ����̽� ���x