#pragma once
#include <span>

struct Matrix44
{
public:
	float mat44[4][4] = { {1.f, 0.0f, 0.f, 0.f}, {0.f, 1.0f, 0.f, 0.f}, 
							{0.f, 0.0f, 1.f, 0.f}, {0.f, 0.0f, 0.f, 1.f} };
	
public:
	FORCEINLINE Matrix44() = default;
	FORCEINLINE Matrix44(const Matrix44& _ref){ memcpy(mat44, _ref.mat44, 64); }
	FORCEINLINE Matrix44(Matrix44&& _ref) noexcept
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				mat44[i][j] += std::move(_ref.mat44[i][j]);
		}
	};
	~Matrix44() = default;

	FORCEINLINE Matrix44& operator=(const Matrix44& _ref);
	FORCEINLINE constexpr void operator+=(const Matrix44& _ref);
};

FORCEINLINE Matrix44& Matrix44::operator=(const Matrix44& _ref)
{
	if (this == &_ref)
		return *this;

	memcpy(mat44, _ref.mat44, 64);

	return *this;
}

FORCEINLINE constexpr void Matrix44::operator+=(const Matrix44& _ref)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			mat44[i][j] += _ref.mat44[i][j];
	}
}

////////////////Matrix44 global operator/////////////////
FORCEINLINE Matrix44 operator+ (const Matrix44& _ref1, const Matrix44& _ref2)
{
	Matrix44 tmp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			tmp.mat44[i][j] = _ref1.mat44[i][j] + _ref2.mat44[i][j];		
	}
	return tmp;
}//Matrix44 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)

FORCEINLINE Matrix44 operator- (const Matrix44& _ref1, const Matrix44& _ref2)
{
	Matrix44 tmp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			tmp.mat44[i][j] = _ref1.mat44[i][j] - _ref2.mat44[i][j];
	}
	return tmp;
}//Matrix44 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)

FORCEINLINE Matrix44 operator* (const Matrix44& _ref, const float& _ratio)
{
	Matrix44 tmp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			tmp.mat44[i][j] = _ref.mat44[i][j] * _ratio;
	}
	return tmp;
}//Matrix44 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)

FORCEINLINE Matrix44 operator* (const float& _ratio, const Matrix44& _ref)
{
	Matrix44 tmp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			tmp.mat44[i][j] = _ref.mat44[i][j] * _ratio;
	}
	return tmp;
}//Matrix44 연산관련 오퍼레이터, 선언과 동시에 정의(인라인 함수)