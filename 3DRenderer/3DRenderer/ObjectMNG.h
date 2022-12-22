#pragma once
#include <vector>
#include "Sphere.h"


class ObjectMNG
{
private:
	std::vector<std::shared_ptr<Figure_Interface>> FlyWeightObject;
	std::vector<std::shared_ptr<Figure_Interface>> ObjectVectors;

public:
	ObjectMNG();
	~ObjectMNG() = default;

public:
	FORCEINLINE constexpr size_t GetObjectVectorSize() { return ObjectVectors.size(); }
	FORCEINLINE constexpr FigureType GetObjectType(int& _idx) { return ObjectVectors[_idx]->GetFigureType(); }
	FORCEINLINE std::shared_ptr<Figure_Interface> GetObject(int& _idx) { return ObjectVectors[_idx]; }

public:
	void CreateObject(FigureType& _type, Vector3 _Pos = Vector3());
};

