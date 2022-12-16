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
	//폴리곤 하나를 기준으로 픽셀연산을 멀티스레드에 맡김, Z버퍼 연산부분 추후 추가
	//_Dib는 멀티스레드 환경에서 그리기를 수행하기위해 매개변수로 삽입
};

