#pragma once
#include <vector>
#include "Sphere.h"

class ObjectMNG
{
private:
	std::vector<std::shared_ptr<Figure_Interface>> FlyWeightObject;
	std::vector<std::shared_ptr<Figure_Interface>> ObjectVectors;
	LightObj Lighting_Sun{1.f, 1.f, 1.f};

public:
	ObjectMNG();
	~ObjectMNG() = default;

public:
	FORCEINLINE constexpr size_t GetObjectVectorSize() { return ObjectVectors.size(); }
	FORCEINLINE constexpr FigureType GetObjectType(int& _idx) { return ObjectVectors[_idx]->GetFigureType(); }
	FORCEINLINE std::shared_ptr<Figure_Interface> GetObject(const int& _idx) { return ObjectVectors[_idx]; }
	FORCEINLINE LightObj* GetLightSun() { return &Lighting_Sun; }

public:
	void CreateObject(const FigureType& _type, const Vector3 _Pos = Vector3());
	void Update(float _elapsedTime);
};

