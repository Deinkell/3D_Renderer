#pragma once

#include "Render.h"
#include "ObjectMNG.h"
#include "ThreadPool.h"
#include "Input.h"

class FrameWork
{
private:
	std::shared_ptr<Render> Unit_Render = nullptr;
	std::shared_ptr<ObjectMNG> Obj_Manager = nullptr;
	std::shared_ptr<ThreadPool> Unit_threadPool = nullptr;
	std::shared_ptr<Camera > Unit_Camera = nullptr;
	std::shared_ptr<Input> Unit_Input = nullptr;

	LARGE_INTEGER Start{0}, End{0}, Timer{0};
	double TimeScale{0.0};
	double DeltaTime{0.0};

public:
	FrameWork() = default;
	~FrameWork() = default;

public:
	FORCEINLINE float GetElapsedTime() { return DeltaTime; }

public:
	void Initialize(HWND _hWnd);
	void Ontick();
	void OnRender(float _elapsedtime);
	void Update(float _elapsedtime);
	void RenderFPS(float _elapsedtime);
};
