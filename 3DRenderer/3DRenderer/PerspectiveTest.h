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


static auto TestFuncPY = [](const Vertex& _InVertex)
{
	return _InVertex.Pos.Y > _InVertex.Pos.W;
};

static auto EdgeFuncPY = [](const Vertex& _InStartVertex, const Vertex& _InEndVertex)
{
	float p1 = _InStartVertex.Pos.W - _InStartVertex.Pos.Y;
	float p2 = _InEndVertex.Pos.W - _InEndVertex.Pos.Y;
	float t = p1 / (p1 - p2);
	return _InStartVertex * (1.f - t) + _InEndVertex * t;
};

static auto TestFuncNX = [](const Vertex& _InVertex) {
	return _InVertex.Pos.X < -_InVertex.Pos.W;
};

static auto EdgeFuncNX = [](const Vertex& _InStartVertex, const Vertex& _InEndVertex) {
	float p1 = _InStartVertex.Pos.W + _InStartVertex.Pos.X;
	float p2 = _InEndVertex.Pos.W + _InEndVertex.Pos.X;
	float t = p1 / (p1 - p2);
	return _InStartVertex * (1.f - t) + _InEndVertex * t;
};

static auto TestFuncPX = [](const Vertex& _InVertex) {
	return _InVertex.Pos.X > _InVertex.Pos.W;
};

static auto EdgeFuncPX = [](const Vertex& _InStartVertex, const Vertex& _InEndVertex) {
	float p1 = _InStartVertex.Pos.W - _InStartVertex.Pos.X;
	float p2 = _InEndVertex.Pos.W - _InEndVertex.Pos.X;
	float t = p1 / (p1 - p2);
	return _InStartVertex * (1.f - t) + _InEndVertex * t;
};

static auto TestFuncFar = [](const Vertex& _InVertex) {
	return _InVertex.Pos.Z > _InVertex.Pos.W;
};

static auto EdgeFuncFar = [](const Vertex& _InStartVertex, const Vertex& _InEndVertex) {
	float p1 = _InStartVertex.Pos.W - _InStartVertex.Pos.Z;
	float p2 = _InEndVertex.Pos.W - _InEndVertex.Pos.Z;
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

	void ClipTriangles(std::vector<Vertex>& _InOutVertices)
	{
		size_t triangles = _InOutVertices.size() / 3;
		for (size_t ti = 0; ti < triangles; ++ti)
		{
			size_t startIndex = ti * 3;
			size_t nonPassCount = 0;

			for (size_t ix = 0; ix < 3; ++ix)
			{
				TestResult[ix] = ClippingTestFunc(_InOutVertices[startIndex + ix]);
				
				if (TestResult[ix])
					nonPassCount++;
			}

			if (nonPassCount == 0)
				continue;
			else if (nonPassCount == 1)
				DivideIntoTwoTriangles(_InOutVertices, startIndex, nonPassCount);
			else if (nonPassCount == 2)
				ClipTriangle(_InOutVertices, startIndex, nonPassCount);
			else
			{
				_InOutVertices.erase(_InOutVertices.begin() + startIndex, _InOutVertices.begin() + startIndex + 3);
				triangles--;
				ti--;
			}
		}
	};

private:
	void DivideIntoTwoTriangles(std::vector<Vertex>& _InOutVertices, size_t _StartIndex, size_t _NonPassCout)
	{
		BYTE index = 0;
		if (!TestResult[0])
			index = TestResult[1] ? 1 : 2;

		size_t v1Index = _StartIndex + (index + 1) % 3;
		size_t v2Index = _StartIndex + (index + 2) % 3;
		Vertex v1 = _InOutVertices[v1Index];
		Vertex v2 = _InOutVertices[v2Index];
		Vertex Clipped1 = GetEdgeVertexFunc(_InOutVertices[_StartIndex + index], v1);
		Vertex Clipped2 = GetEdgeVertexFunc(_InOutVertices[_StartIndex + index], v2);
		_InOutVertices[_StartIndex] = Clipped1;
		_InOutVertices[_StartIndex + 1] = v1;
		_InOutVertices[_StartIndex + 2] = v2;
		_InOutVertices.push_back(Clipped1);
		_InOutVertices.push_back(v2);
		_InOutVertices.push_back(Clipped2);
	};

	void ClipTriangle(std::vector<Vertex>& _InOutVertices, size_t _StartIndex, size_t _NonPassCout)
	{
		BYTE index = 0;
		if (TestResult[0])
			index = !TestResult[1] ? 1 : 2;

		size_t v1Index = _StartIndex + (index + 1) % 3;
		size_t v2Index = _StartIndex + (index + 2) % 3;
		Vertex v1 = _InOutVertices[v1Index];
		Vertex v2 = _InOutVertices[v2Index];
		Vertex Clipped1 = GetEdgeVertexFunc(_InOutVertices[_StartIndex + index], v1);
		Vertex Clipped2 = GetEdgeVertexFunc(_InOutVertices[_StartIndex + index], v2);
		_InOutVertices[v1Index] = Clipped1;
		_InOutVertices[v2Index] = Clipped2;
	};
};

