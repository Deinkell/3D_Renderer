#pragma once

#include "Render.h"
#include "ObjectMNG.h"
#include "ThreadPool.h"

class FrameWork
{
private:
	std::shared_ptr<Render> Unit_Render;
	std::shared_ptr<ObjectMNG> Obj_Manager;
	std::shared_ptr<ThreadPool> Unit_hreadPool;

	LARGE_INTEGER Start, End, Timer;
	double TimeScale;
	double DeltaTime;

public:
	FrameWork() = default;
	~FrameWork() = default;

public:
	FORCEINLINE float GetElapsedTime() { return DeltaTime; }

public:
	void Initialize();
	void Ontick();
	void OnRender(float _elapsedtime);
	void Update(float _elapsedtime);
	void RenderFPS(float _elapsedtime);
};
