#pragma once
#include <array>

static auto TestFuncW0 = [](const Vertex& _InVertex)
{
	return _InVertex.Pos.W < 0.f;
};

static auto EdgeFuncW0 = [](const Vertex& _InStartVertex, const Vertex& _InEndVertex)
{
	float p1 = _InStartVertex.Pos.W;
	float p2 = _InEndVertex.Pos.W;
	float t = p1 / (p1 - p2);
	return _InStartVertex * (1.f - t) + _InEndVertex * t;
};

static auto TestFuncNY = [](const Vertex& _InVertex)
{
	return _InVertex.Pos.Y < -_InVertex.Pos.W;
};

static auto EdgeFuncNY = [](const Vertex& _InStartVertex, const Vertex& _InEndVertex)
{
	float p1 = _InStartVertex.Pos.W + _InStartVertex.Pos.Y;
	float p2 = _InEndVertex.Pos.W + _InEndVertex.Pos.Y;
	float t = p1 / (p1 - p2);
	return _InStartVertex * (1.f - t) + _InEndVertex * t;
};

static auto TestFuncNear = [](const Vertex& _InVertex)
{
	return _InVertex.Pos.Z <-_InVertex.Pos.W;
};

static auto EdgeFuncNear = [](const Vertex& _InStartVertex, const Vertex& _InEndVertx)
{
	float p1 = _InStartVertex.Pos.W + _InStartVertex.Pos.Z;
	float p2 = _InEndVertx.Pos.W + _InEndVertx.Pos.Z;
	float t = p1 / (p1 - p2);
	return _InStartVertex * (1.f - t) + _InEndVertx * t;
};

struct PerspectiveTest
{
	std::function<bool(const Vertex& InVertex)> ClippingTestFunc;
	std::function<Vertex(const Vertex& InStartVertex, const Vertex& InEndVertex)> GetEdgeVertexFunc;
	std::array<bool, 3> TestResult;


};

