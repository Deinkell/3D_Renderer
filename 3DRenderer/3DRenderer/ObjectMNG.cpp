#include "stdafx.h"
#include "ObjectMNG.h"

ObjectMNG::ObjectMNG()
{
	FlyWeightObject.push_back(Sphere());
}

void ObjectMNG::CreateObject(FigureType& _type, Vector3 _Pos = Vector3())
{
	size_t Size = FlyWeightObject.size();
	for(int i = 0; i < Size; i++)
	{
		if (_type == FlyWeightObject[i].GetFigureType())
		{
			FlyWeightObject[i].SetPosition(_Pos);
			ObjectVectors.push_back(FlyWeightObject[i]);
			//프로토타입패턴 이용->텍스쳐를 입히게되면 경량패턴으로 교체
		}
	}
}
