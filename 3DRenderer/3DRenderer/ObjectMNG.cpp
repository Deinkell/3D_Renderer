#include "stdafx.h"
#include "ObjectMNG.h"

ObjectMNG::~ObjectMNG()
{
	int Size = FlyWeightObject.size();
	for(int i = Size-1; i >= 0; i--)
		delete FlyWeightObject[i];
}

ObjectMNG::ObjectMNG()
{
	FlyWeightObject.push_back(new Sphere());
	int Size = FlyWeightObject.size();
	for (auto& i : FlyWeightObject)
		i->Init();

	Lighting_Sun = std::make_shared<LightObj>(0.4f, 0.4f, 0.4f);
	Lighting_Sun->Init();
	Lighting_Sun->SetRenderType(RenderType::LightRender);
	ObjectVectors.push_back(Lighting_Sun);
}

void ObjectMNG::CreateObject(const FigureType& _type, const Vector3 _Pos)
{
	size_t Size = FlyWeightObject.size();

	switch (_type)
	{
		case FigureType::Sphere_type:
		{
			for (int i = 0; i < Size; i++)
			{
				if (_type == FlyWeightObject[i]->GetFigureType())
				{
					FlyWeightObject[i]->SetPosition(_Pos);
					auto tmp(std::make_shared<Sphere>(*FlyWeightObject[i]));
					tmp->SetPosition(Vector3(0.f, 0.f, 0.f));
					ObjectVectors.push_back(std::move(tmp));
					//프로토타입패턴 이용					
				}
			}
			break;
		}
		default:
			return;		
	}
}

void ObjectMNG::Update(float _elapsedTime)
{
	for (auto i : ObjectVectors)
		i->Ontick(_elapsedTime);
}

void ObjectMNG::PrepareRender_MakeMat(const Matrix44& _CameraMat, const Matrix44& _ProjMat)
{	
	for (auto& i : ObjectVectors)
		i->MakeMatrix_Inv(_CameraMat, _ProjMat);
}

