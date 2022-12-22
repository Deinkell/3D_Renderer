#include "stdafx.h"
#include "ObjectMNG.h"

ObjectMNG::ObjectMNG()
{
	FlyWeightObject.push_back(std::make_shared<Sphere>());
}

void ObjectMNG::CreateObject(FigureType& _type, Vector3 _Pos)
{	
	size_t Size = FlyWeightObject.size();
	
	for(int i = 0; i < Size; i++)
	{
		if (_type == FlyWeightObject[i]->GetFigureType())
		{
			FlyWeightObject[i]->SetPosition(_Pos);
			auto tmp(FlyWeightObject[i]);
			ObjectVectors.push_back(std::move(tmp));
			//������Ÿ������ �̿�->�ؽ��ĸ� �����ԵǸ� �淮�������� ��ü
		}
	}
}
