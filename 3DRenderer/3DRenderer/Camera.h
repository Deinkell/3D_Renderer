#pragma once

struct Matrix44;
struct Vector3;

class Camera
{
private:
	Vector3 Position, LookAt;
	Vector3 Direction[3]; // 0 : Up / 1 : Right / 2 : Front
	Vector3 NormalVec;
	Matrix44 CameraMat;

public:
	Camera() = delete;
	~Camera() = default;
	FORCEINLINE explicit constexpr Camera(const Vector3& _Pos, const Vector3& _Lookat) : Position(_Pos), LookAt(_Lookat) {};
	//반드시 Position과 LookAt을 기입하는 생성을 유도
public:
	FORCEINLINE constexpr Vector3 GetPosition() { return Position; }
	FORCEINLINE Matrix44 GetCameraMat() { return CameraMat; }
	FORCEINLINE constexpr Vector3 GetNormal() { return NormalVec; }
	FORCEINLINE constexpr Vector3 GetFrontAxis() { return Direction[2]; }

public:
	void Initialize();
	void MakeViewMatrix();
	void Update(float _elapsedTime);
	void Move(float _elapsedTime);
	void UpdateAxis();
};

