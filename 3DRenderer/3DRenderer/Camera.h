#pragma once

struct Matrix44;
struct Vector3;

class Camera
{
private:
	Vector3 Position, LookAt;
	Vector3 Direction[3]; // 0 : Up / 1 : Right / 2 : Front
	Matrix44 CameraMat;

public:
	Camera() = delete;
	~Camera() = default;
	FORCEINLINE explicit constexpr Camera(const Vector3& _Pos, const Vector3& _Lookat) : Position(_Pos), LookAt(_Lookat) {};
	//�ݵ�� Position�� LookAt�� �����ϴ� ������ ����
public:
	void Initialize();
	void MakeViewMatrix();
};
