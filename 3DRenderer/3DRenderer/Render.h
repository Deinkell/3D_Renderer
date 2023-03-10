#pragma once
#include "DibSection.h"
#include "DepthBuffer.h"
#include "Figure_define.h"
#include "Input.h"

struct Vertex;
class ObjectMNG;
class ThreadPool;
class Camera;
class Proj;

class Render
{
private:
	DibSection DibSec; 
	DepthBuffer DepthBuf;
	std::unique_ptr<Proj> Projection;	
	CRITICAL_SECTION CRSC;
	Matrix44 ViewPortMat;
	int ClientX, ClientY;	
	RenderType Render_Type = RenderType::PhongShading;
	bool Thread_Render = false;
	bool wireFrame = false;
	std::vector<std::string> StaticText;

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
	FORCEINLINE constexpr int GetClientX() { return ClientX; }
	FORCEINLINE constexpr int GetClientY() { return ClientY; }

public:
	FORCEINLINE void BitBltDib();
	FORCEINLINE void SetRenderType(int _input);
	FORCEINLINE RenderType GetRenderType(RenderType _Type);

public:
	void Initialize(std::shared_ptr<ObjectMNG>& _ObjMng, std::shared_ptr<ThreadPool>& _Thdpool, std::shared_ptr<Camera>& _Camera);
	void MakeViewPortMat();
	void OnRender(float _elapsedTime);
	void PrepareObj_for_Render();
	void MakePolygonNDCData(Vertex* _Polygon);
	void MakePolygonViewPortData(std::vector<Vertex>& _vt);
	void RenderObj();
	bool BackFaceCuling(const Vector3& _Normal);
	Vector3 Geometric_centroid_VertexCalc(const Vector3& _p1, const Vector3& _p2, const Vector3& _p3, const Vector3& _w);
	void SwithRenderType(const Vector3& _ObjPos, const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, const PhongData& _PD);
	//////////////래스터라이즈 함수들(폴리곤 하나를 기준으로 픽셀연산을 멀티스레드에 맡김)/////////////////////
	void RasterizePolygon_Phong(const Vector3& _ObjPos, const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, const PhongData& _PD);
	void RasterizePolygon_wire(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3);
	void RasterizePolygon_Flat(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, const Color32& _Color);
	void RasterizePolygon_Test(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3);//뷰월드까지 진행한 결과 출력용
	void RasterizePolygon_Light(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, const Color32& _Color);
	Color32 MakePhongShader(const Vector3& _ObjPos, const Vector3& _PixelNormal, const PhongData& _PD);	
	void LineDraw(int _x1, int _y1, int _x2, int _y2, const Color32& _color);
	void RenderFPS(float _elapsedTime);
	void RenderStaticText(std::vector<std::string>& _TextVec);
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

FORCEINLINE void Render::SetRenderType(int _input)
{
	if (VK_NUM1 == _input)	wireFrame = true;	
	if (VK_NUM2 == _input)	wireFrame = false;
}

FORCEINLINE RenderType Render::GetRenderType(RenderType _Type)
{
	return wireFrame ? RenderType::WireFrame : _Type;
}