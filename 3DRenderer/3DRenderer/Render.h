#pragma once
#include "DibSection.h"
#include "DepthBuffer.h"

struct Vertex;
class ObjectMNG;
class ThreadPool;
class Camera;
enum class FigureType : char;

class Render
{
private:
	DibSection DibSec; //Dib�� ������Ʈ�� �ƴ� ������ �ʼ� �ɹ�����, ������ ���� �Ұ��� �ʿ䵵 ���⶧��
	DepthBuffer DepthBuf;
	CRITICAL_SECTION CRSC;

private:
	std::shared_ptr<ObjectMNG> ObjectMng_Component;
	std::shared_ptr<ThreadPool> ThreadPool_Component;
	std::shared_ptr<Camera> Camera_Component;

public:
	FORCEINLINE void SetObjectMng(std::shared_ptr<ObjectMNG>& _ref) { ObjectMng_Component = _ref; }
	FORCEINLINE void SetThreadPool(std::shared_ptr<ThreadPool>& _ref) { ThreadPool_Component = _ref; }	
	FORCEINLINE void SetCamera (std::shared_ptr<Camera>&_ref) { Camera_Component = _ref; };

public:
	Render();
	~Render();

public:
	void Initialize(std::shared_ptr<ObjectMNG>& _ObjMng, std::shared_ptr<ThreadPool>& _Thdpool, std::shared_ptr<Camera>& _Camera);
	void OnRender(float _elapsedTime);
	void BackSpaceCuling();
	Vector3 Geometric_centroid_VertexCalc(const Vector3& _p3p1Vec, const Vector3& _p3p2Vec, const Vector3& _w);
	void RasterizePolygon(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, const PhongData& _PD);
	//������ �ϳ��� �������� �ȼ������� ��Ƽ�����忡 �ñ�, Z���� ����κ� ���� �߰�	
	Color32 MakePhongShader(const Vector3& _ObjPos, const Vector3& _PixelNormal, const PhongData& _PD);
	void RenderFPS(float _elapsedTime);
};

