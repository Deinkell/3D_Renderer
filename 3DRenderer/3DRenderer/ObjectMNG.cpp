#include "stdafx.h"
#include "ObjectMNG.h"

ObjectMNG::ObjectMNG()
{
	FlyWeightObject.push_back(std::make_shared<Sphere>());
}

void ObjectMNG::CreateObject(const FigureType& _type, const Vector3 _Pos)
{	
	size_t Size = FlyWeightObject.size();
	
	for(int i = 0; i < Size; i++)
	{
		if (_type == FlyWeightObject[i]->GetFigureType())
		{
			FlyWeightObject[i]->SetPosition(_Pos);
			auto tmp(FlyWeightObject[i]);
			ObjectVectors.push_back(std::move(tmp));
			//프로토타입패턴 이용->텍스쳐를 입히게되면 경량패턴으로 교체
		}
	}
}

void ObjectMNG::Update(float _elapsedTime)
{
}
