#pragma once
#include "DibSection.h"
#include "DepthBuffer.h"
#include "RenderData.h"

struct Vertex;
class ObjectMNG;
class ThreadPool;
class Camera;
class Proj;
enum class FigureType : char;

class Render
{
private:
	DibSection DibSec; //Dib는 컴포넌트가 아닌 랜더의 필수 맴버변수, 관리를 따로 할곳도 필요도 없기때문
	DepthBuffer DepthBuf;
	std::unique_ptr<Proj> Projection;	
	CRITICAL_SECTION CRSC;
	float ClientX, ClientY;	
	bool WireFrame = false, Thread_Render = false;

private:
	std::shared_ptr<ObjectMNG> ObjectMng_Component;
	std::shared_ptr<ThreadPool> ThreadPool_Component;
	std::shared_ptr<Camera> Camera_Component;

public:
	FORCEINLINE void SetObjectMng(std::shared_ptr<ObjectMNG>& _ref) { ObjectMng_Component = _ref; }
	FORCEINLINE void SetThreadPool(std::shared_ptr<ThreadPool>& _ref) { ThreadPool_Component = _ref; }	
	FORCEINLINE void SetCamera (std::shared_ptr<Camera>&_ref) { Camera_Component = _ref; };

public:
	Render(HWND _hWnd);
	~Render();

public:
	FORCEINLINE void BitBltDib();

public:
	void Initialize(std::shared_ptr<ObjectMNG>& _ObjMng, std::shared_ptr<ThreadPool>& _Thdpool, std::shared_ptr<Camera>& _Camera);
	void OnRender(float _elapsedTime);
	void PrepareObj_for_Render();
	void MakePolygonNDCData(Vertex* _Polygon);
	void MakePolygonViewPortData(std::vector<Vertex>& _vt);
	void RenderObj();
	bool BackFaceCuling(const Vector3& _Normal);
	Vector3 Geometric_centroid_VertexCalc(const Vector3& _p1, const Vector3& _p2, const Vector3& _p3, const Vector3& _w);
	void RasterizePolygon_Phong(const Vector3& _ObjPos, const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, const PhongData& _PD);
	//폴리곤 하나를 기준으로 픽셀연산을 멀티스레드에 맡김
	void RasterizePolygon_wire(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3);
	Color32 MakePhongShader(const Vector3& _ObjPos, const Vector3& _PixelNormal, const PhongData& _PD);	
	void LineDraw(int _x1, int _y1, int _x2, int _y2, const Color32& _color);
	void RenderFPS(float _elapsedTime);
};

FORCEINLINE void Render::BitBltDib()
{
	while(1)
	{
		if (ThreadPool_Component->AllThreadWait())
		{
			DibSec.BitBltDibSection();
			break;
		}
	}

	DepthBuf.ClearDepthBuffer();
}