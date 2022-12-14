#pragma once
#include "DibSection.h"

struct Vertex;
class ObjectMNG;
enum class FigureType;

class Render
{
private: 
	DibSection DibSec;

private:
	ObjectMNG* ObjectMng_Component;

public:
	void OnRender();
	void BackSpaceCuling();
	void PlaneCulling();
	void RasterizePolygon(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3);
	//������ �ϳ��� �������� �ȼ������� ��Ƽ�����忡 �ñ�
};

