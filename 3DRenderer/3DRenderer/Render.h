#pragma once
#include "DibSection.h"

struct Vertex;
class ObjectMNG;
class ThreadPool;
enum class FigureType;

class Render
{
private: 
	DibSection DibSec;

private:
	ObjectMNG* ObjectMng_Component;
	ThreadPool* ThreadPool_Component;

public:
	void OnRender();
	void BackSpaceCuling();
	void PlaneCulling();
	void RasterizePolygon(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, DibSection& _DibSec);
	//������ �ϳ��� �������� �ȼ������� ��Ƽ�����忡 �ñ�, Z���� ����κ� ���� �߰�
	//_Dib�� ��Ƽ������ ȯ�濡�� �׸��⸦ �����ϱ����� �Ű������� ����
};

