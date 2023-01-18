#pragma once

enum class FigureType : char
{
	None = 0,
	Sphere_type = 1,
	Light_OBJECT = 2,
};

enum class RenderType : int
{
	basic = 1,
	WireFrame = 2,
	FlatShading = 3,
	PhongShading = 4,
	LightRender = 5
};