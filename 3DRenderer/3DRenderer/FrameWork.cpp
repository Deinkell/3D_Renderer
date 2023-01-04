#include "stdafx.h"
#include <timeapi.h>
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

	QueryPerformanceFrequency(&Timer);
	TimeScale = 1.0 / Timer.QuadPart;
	QueryPerformanceCounter(&End);
};

void FrameWork::Ontick()
{
	QueryPerformanceCounter(&Start);
	DeltaTime = (Start.QuadPart - End.QuadPart) * TimeScale;

	Update(DeltaTime);
	OnRender(DeltaTime);
	RenderFPS(DeltaTime);

	End = Start;
};

void FrameWork::Update(float _elapsedtime)
{
	Obj_Manager->Update(_elapsedtime);
};

void FrameWork::OnRender(float _elapsedtime)
{
	Unit_Render->OnRender(_elapsedtime);
};

void FrameWork::RenderFPS(float _elapsedtime)
{
	Unit_Render->RenderFPS(_elapsedtime);
}


