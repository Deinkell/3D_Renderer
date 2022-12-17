#pragma once
#include "DibSection.h"

struct Vertex;
class ObjectMNG;
class ThreadPool;
enum class FigureType;

class Render
{
private:
	DibSection DibSec; //Dib�� ������Ʈ�� �ƴ� ������ �ʼ� �ɹ�����, ������ ���� �Ұ��� �ʿ䵵 ���⶧��

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
	//������ �ϳ��� �������� �ȼ������� ��Ƽ�����忡 �ñ�, Z���� ����κ� ���� �߰�
	//_Dib�� ��Ƽ������ ȯ�濡�� �׸��⸦ �����ϱ����� �Ű������� ����
};

