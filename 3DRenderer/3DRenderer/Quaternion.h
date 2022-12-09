#pragma once

struct Quaternion
{
public:
	float X, Y, Z, W;
	
public:
	FORCEINLINE constexpr Quaternion() : X(0.f), Y(0.f), Z(0.f), W(0.f) {};

	template<typename T> requires std::is_fundamental_v<T>
	FORCEINLINE Quaternion(T&& _x, T&& _y, T&& _z, T&& _w)
	: X(std::forward<float>(_x)), Y(std::forward<float>(_y)), Z(std::forward<float>(_z)), W(std::forward<float>(_w))
	{};
	//�Ϻ����� ������(�Ű������� �� ������ ����)
	template<typename T> requires std::is_same<Quaternion, T>::value
	FORCEINLINE Quaternion(T&& _ref) noexcept
	: X(std::forward<float>(_ref.X)), Y(std::forward<float>(_ref.Y)), Z(std::forward<float>(_ref.Z)), W(std::forward<float>(_ref.W))
	{};
	//�Ϻ����� ���������(�������, �̵��������)

	~Quaternion() = default;
	//�Ҹ���

	template<typename T> requires std::is_same<Quaternion, T>::value
	FORCEINLINE T& operator= (T&& _ref) noexcept
	{
		if (this == &_ref)
			return *this;

		X = std::forward<float>(_ref.X);
		Y = std::forward<float>(_ref.Y);
		Z = std::forward<float>(_ref.Z);
		W = std::forward<float>(_ref.W);

		return *this;
	}
	FORCEINLINE constexpr void operator+=(const Quaternion& _ref);
	FORCEINLINE constexpr bool operator==(const Quaternion& _ref);		
};

FORCEINLINE constexpr void Quaternion::operator+=(const Quaternion& _ref)
{
	X += _ref.X;
	Y += _ref.Y;
	Z += _ref.Z;
	W += _ref.W;
}

FORCEINLINE constexpr bool Quaternion::operator==(const Quaternion& _ref)
{
	return !(X == _ref.X) ? false : !(Y == _ref.Y) ? false : !(Z == _ref.Z) ? false : !(W == _ref.W) ? false : true;
}

////////////////Quaternion global operator/////////////////
FORCEINLINE constexpr Quaternion operator+(const Quaternion& _ref1, const Quaternion& _ref2)
{
	return Quaternion((_ref1.X + _ref2.X), (_ref1.Y + _ref2.Y), (_ref1.Z + _ref2.Z), (_ref1.W + _ref2.W));
}//Quaternion ������� ���۷�����, ����� ���ÿ� ����(�ζ��� �Լ�)

FORCEINLINE constexpr Quaternion operator-(const Quaternion& _ref1, const Quaternion& _ref2)
{
	return Quaternion((_ref1.X - _ref2.X), (_ref1.Y - _ref2.Y), (_ref1.Z - _ref2.Z), (_ref1.W - _ref2.W));
}//Quaternion ������� ���۷�����, ����� ���ÿ� ����(�ζ��� �Լ�)
FORCEINLINE Quaternion operator* (const Quaternion& _ref, const float& _ratio)
{
	return std::move(Quaternion(_ref.X * _ratio, _ref.Y * _ratio, _ref.Z * _ratio, _ref.W * _ratio));
}//Quaternion ������� ���۷�����, ����� ���ÿ� ����(�ζ��� �Լ�)

FORCEINLINE Quaternion operator* (const float& _ratio, const Quaternion& _ref)
{
	return std::move(Quaternion(_ref.X * _ratio, _ref.Y * _ratio, _ref.Z * _ratio, _ref.W * _ratio));
}//Quaternion ������� ���۷�����, ����� ���ÿ� ����(�ζ��� �Լ�)
