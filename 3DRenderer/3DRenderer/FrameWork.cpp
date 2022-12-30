#include "stdafx.h"
#include "FrameWork.h"
#include "Figure_Interface.h"

void FrameWork::Initialize()
{
	Unit_Render = std::make_shared<Render>();
	Obj_Manager = std::make_shared<ObjectMNG>();
	Unit_hreadPool = std::make_shared<ThreadPool>(4);

	Unit_Render->SetObjectMng(Obj_Manager);
	Unit_Render->SetThreadPool(Unit_hreadPool);
	Obj_Manager->CreateObject(FigureType::Sphere_type);
};

void FrameWork::Ontick()
{
	QueryPerformanceFrequency(&timer);
	QueryPerformanceCounter(&start);	
	DeltaTime = (start.QuadPart - end.QuadPart) / (float)timer.QuadPart;

	if (DeltaTime <= 0)
		DeltaTime = 0;

	Update(DeltaTime);
	OnRender(DeltaTime);

	QueryPerformanceCounter(&end);
};

void FrameWork::Update(float _elapsedtime)
{
	Obj_Manager->Update(_elapsedtime);
};

void FrameWork::OnRender(float _elapsedtime)
{
	Unit_Render->OnRender(_elapsedtime);
};


