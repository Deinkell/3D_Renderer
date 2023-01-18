#pragma once

class Input;
struct Matrix44;
struct Vector3;

class Camera
{
private:
	Vector3 Position, LookAt, MoveLookAt;
	Vector3 Direction[3]; // 0 : Up / 1 : Right / 2 : Front
	Vector3 NormalVec;
	Matrix44 CameraMat;
	float DeltaX, DeltaY, MoveSpeed;

private:
	std::shared_ptr<Input> Input_Component;

public:
	Camera() = delete;
	~Camera() = default;
	FORCEINLINE explicit constexpr Camera(const Vector3& _Pos, const Vector3& _Lookat) 
	: Position(_Pos), LookAt(_Lookat), DeltaX(0.f), DeltaY(0.f), MoveSpeed(0.1f) {};
	//반드시 Position과 LookAt을 기입하는 생성을 유도
public:
	FORCEINLINE constexpr Vector3 GetPosition() { return Position; }
	FORCEINLINE Matrix44 GetCameraMat() { return CameraMat; }
	FORCEINLINE constexpr Vector3 GetNormal() { return NormalVec; }
	FORCEINLINE constexpr Vector3 GetFrontAxis() { return Direction[2]; }
////////////////////////Get함수
	FORCEINLINE void SetInputComponent(std::shared_ptr<Input>& _Comp) { Input_Component = _Comp; }

public:
	void Initialize();
	void MakeViewMatrix();
	void MakeViewMatrix_Inv();
	void Update(float _elapsedTime);
	void Move(float _elapsedTime);
	void UpdateAxis();
};

