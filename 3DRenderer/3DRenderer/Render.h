#pragma once
#include "DibSection.h"
#include "DepthBuffer.h"

struct Vertex;
class ObjectMNG;
class ThreadPool;
enum class FigureType : char;

class Render
{
private:
	DibSection DibSec; //Dib는 컴포넌트가 아닌 랜더의 필수 맴버변수, 관리를 따로 할곳도 필요도 없기때문
	DepthBuffer DepthBuf;
	CRITICAL_SECTION CRSC;

private:
	std::shared_ptr<ObjectMNG> ObjectMng_Component;
	std::shared_ptr<ThreadPool> ThreadPool_Component;

public:
	FORCEINLINE void SetObjectMng(std::shared_ptr<ObjectMNG>& _ref) { ObjectMng_Component = _ref; }
	FORCEINLINE void SetThreadPool(std::shared_ptr<ThreadPool>& _ref) { ThreadPool_Component = _ref; }	

public:
	Render();
	~Render();

public:
	void OnRender(float _elapsedTime);
	void BackSpaceCuling();
	Vector3 Geometric_centroid_VertexCalc(const Vector3& _p3p1Vec, const Vector3& _p3p2Vec, const Vector3& _w);
	void RasterizePolygon(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3);
	//폴리곤 하나를 기준으로 픽셀연산을 멀티스레드에 맡김, Z버퍼 연산부분 추후 추가	
};

