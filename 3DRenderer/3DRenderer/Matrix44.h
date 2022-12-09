#pragma once
#include <span>

struct Matrix44
{
public:
	float mat44[4][4];
	
public:
	FORCEINLINE constexpr Matrix44(){ memset(mat44, 0.f, 64); }
	FORCEINLINE constexpr Matrix44(const Matrix44& _ref){ memcpy(mat44, _ref.mat44, 64); }

	FORCEINLINE constexpr Matrix44& operator=(const Matrix44& _ref);
	FORCEINLINE constexpr void operator+=(const Matrix44& _ref);
};

FORCEINLINE Matrix44& Matrix44::operator=(const Matrix44& _ref)
{
	if (this == &_ref)
		return *this;

	memcpy(mat44, _ref.mat44, 64);

	return *this;
}

FORCEINLINE void Matrix44::operator+=(const Matrix44& _ref)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			mat44[i][j] += _ref.mat44[i][j];
	}
}