#pragma once

enum class FigureType : char
{
	None = 0,
	Sphere_type = 1,
	Light_OBJECT = 2,
};

enum class RenderType : char
{
	basic,
	WireFrame,
	FlatShading,
	PhongShading,
	LightRender
};