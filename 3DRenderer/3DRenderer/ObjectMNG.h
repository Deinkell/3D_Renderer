#pragma once
#include <vector>
#include "Sphere.h"
#include "LightObj.h"

class Camera;
class Proj;

class ObjectMNG
{
private:
	std::vector<Figure_Interface*> FlyWeightObject;
	std::vector<std::shared_ptr<Figure_Interface>> ObjectVectors;
	std::shared_ptr<LightObj> Lighting_Sun;

public:
	ObjectMNG();
	~ObjectMNG();

public:
	FORCEINLINE constexpr size_t GetObjectVectorSize() { return ObjectVectors.size(); }
	FORCEINLINE constexpr FigureType GetObjectType(int& _idx) { return ObjectVectors[_idx]->GetFigureType(); }
	FORCEINLINE std::shared_ptr<Figure_Interface> GetObject(const int& _idx) { return ObjectVectors[_idx]; }
	FORCEINLINE std::shared_ptr<LightObj> GetLightSun() { return Lighting_Sun; }
	FORCEINLINE decltype(auto) GetPhongData(const int& _idx) {return ObjectVectors[_idx]->GetPhongData();}
	FORCEINLINE decltype(auto) GetObj_Vertices(const int& _idx) { return ObjectVectors[_idx]->GetVertices(); }
	FORCEINLINE decltype(auto) GetObj_Indicies(const int& _idx) { return ObjectVectors[_idx]->GetIndices(); }
	FORCEINLINE decltype(auto) GetObj_FinalMatrix(const int& _idx) { return ObjectVectors[_idx]->GetMatrix44(); }
	FORCEINLINE decltype(auto) GetObj_WrdViewMat(const int& _idx) { return ObjectVectors[_idx]->GetWrdViewMat(); }
	FORCEINLINE decltype(auto) GetObj_WrdMat(const int& _idx) { return ObjectVectors[_idx]->GetWorldMat(); }
	FORCEINLINE decltype(auto) GetObj_Position(const int& _idx) { return ObjectVectors[_idx]->GetPosition(); }
	FORCEINLINE decltype(auto) GetRenderType(const int& _idx) { return ObjectVectors[_idx]->GetRenderType(); }

public:
	void CreateObject(const FigureType& _type, const Vector3 _Pos = Vector3());
	void Update(float _elapsedTime);
	void PrepareRender_MakeMat(const Matrix44& _CameraMat, const Matrix44& _ProjMat);	
};



