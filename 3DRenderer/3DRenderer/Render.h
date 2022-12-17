#pragma once
#include "DibSection.h"

struct Vertex;
class ObjectMNG;
class ThreadPool;
enum class FigureType;

class Render
{
private:
	DibSection DibSec; //Dib는 컴포넌트가 아닌 랜더의 필수 맴버변수, 관리를 따로 할곳도 필요도 없기때문

private:
	std::shared_ptr<ObjectMNG> ObjectMng_Component;
	std::shared_ptr<ThreadPool> ThreadPool_Component;

public:
	FORCEINLINE void SetObjectMng(std::shared_ptr<ObjectMNG>& _ref) { ObjectMng_Component = _ref; }
	FORCEINLINE void SetThreadPool(std::shared_ptr<ThreadPool>& _ref) { ThreadPool_Component = _ref; }

public:
	Render();
	~Render() = default;

public:
	void OnRender();
	void BackSpaceCuling();
	void PlaneCulling();
	void RasterizePolygon(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, DibSection& _DibSec);
	//폴리곤 하나를 기준으로 픽셀연산을 멀티스레드에 맡김, Z버퍼 연산부분 추후 추가
	//_Dib는 멀티스레드 환경에서 그리기를 수행하기위해 매개변수로 삽입
};

