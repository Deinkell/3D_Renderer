#include "stdafx.h"
#include <timeapi.h>
#include "FrameWork.h"
#include "Figure_Interface.h"

void FrameWork::Initialize(HWND _hWnd)
{
	Unit_Render = std::make_shared<Render>(_hWnd);
	Obj_Manager = std::make_shared<ObjectMNG>();
	Unit_Camera = std::make_shared<Camera>(Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 1000.f));
	Unit_threadPool = std::make_shared<ThreadPool>(4);

	Unit_Render->Initialize(Obj_Manager, Unit_threadPool, Unit_Camera);
	Obj_Manager->CreateObject(FigureType::Sphere_type);
	Unit_Camera->Initialize();

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


