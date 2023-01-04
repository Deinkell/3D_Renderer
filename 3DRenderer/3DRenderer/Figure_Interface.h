#pragma once
#include <vector>
#include "Figure_define.h"

struct Vector3;
struct Vertex;
struct Index;
struct Matrix44;

class Figure_Interface
{
protected:
	Vector3 Position{0.f, 0.f, 0.f};
	Vector3 Rotation{0.f, 0.f, 0.f};
	Vector3 Scale{1.f, 1.f, 1.f};
	// Z축과 Y축의 데이터를 바꿔서 이용하여 Z축과 Y축을 교체, upVector는 Z축이 되도록 함
	Matrix44 FigureMat44;
	std::shared_ptr<std::vector<Vertex>> Vertices = std::make_shared<std::vector<Vertex>>();
	std::shared_ptr<std::vector<Index>> Indices = std::make_shared<std::vector<Index>>();
	FigureType Figure_type;

public:
	Figure_Interface() = default;
	FORCEINLINE Figure_Interface(const std::shared_ptr<std::vector<Vertex>> _Vertices, 
		std::shared_ptr<std::vector<Index>> _Indices, FigureType _type)
	: Vertices(_Vertices), Indices(_Indices), Figure_type(_type){};
	FORCEINLINE Figure_Interface(const Vector3& _Pos, const FigureType& _type) : Position(_Pos), Figure_type(Figure_type) {}
	FORCEINLINE Figure_Interface(const FigureType& _type) : Figure_type(Figure_type) {}
	FORCEINLINE Figure_Interface(const Figure_Interface& _ref)
	: Position(_ref.Position), Rotation(_ref.Rotation), Scale(_ref.Scale),
		FigureMat44(_ref.FigureMat44), Vertices(_ref.Vertices), 
		Indices(_ref.Indices), Figure_type(_ref.Figure_type) {};
	FORCEINLINE Figure_Interface(Figure_Interface&& _ref) noexcept
	:	Position(std::move(_ref.Position)), Rotation(std::move(_ref.Rotation)), Scale(std::move(_ref.Scale)),
		FigureMat44(std::move(_ref.FigureMat44)), Vertices(std::move(_ref.Vertices)),
		Indices(std::move(_ref.Indices)), Figure_type(std::move(_ref.Figure_type)) {};
	~Figure_Interface() = default;

public:	
	FORCEINLINE constexpr void SetVertices(const auto _Vertices) { Vertices = _Vertices; };
	//오브젝트의 버텍스리스트를 포인터로 삽입, 경량패턴(본체 하나만 존재, 복사사용)이용
	FORCEINLINE constexpr void SetIndices(const auto _Indices) { Indices = _Indices; }
	//오브젝트의 인덱스리스트를 포인터로 삽입, 경량패턴(본체 하나만 존재, 복사사용)이용
	FORCEINLINE constexpr void SetFigureType(const auto _type) { Figure_type = _type; }
	FORCEINLINE constexpr void SetPosition(const auto _Pos) { Position = _Pos; }
	FORCEINLINE constexpr void SetRotation(const auto _Rot) { Rotation = _Rot; }
	FORCEINLINE constexpr void SetScale(const auto _Scale) { Scale = _Scale; }
	FORCEINLINE constexpr void SetMatrix44(const auto _Mat) { FigureMat44 = _Mat; }
	// Set함수
	FORCEINLINE decltype(auto) GetVertices() { return Vertices; }
	FORCEINLINE decltype(auto) GetIndices() { return Indices; }
	FORCEINLINE constexpr decltype(auto) GetFigureType() { return Figure_type; }
	FORCEINLINE constexpr decltype(auto) GetPosition() { return Position; }
	FORCEINLINE constexpr decltype(auto) GetRotation() { return Rotation; }
	FORCEINLINE constexpr decltype(auto) GetScale() { return Scale; }
	FORCEINLINE decltype(auto) GetMatrix44() { return FigureMat44; }
	// Get함수
public:
	void MakeWorldMatrix();
	void MakeViewMatrix(const Matrix44& _CameraMatrix);
	void MakeProjMatrix();
	//공용으로 쓰는 매트릭스 생성함수

public:
	virtual void Init() abstract = 0;
	virtual void Move(time_t _time) abstract = 0;
	virtual void MakeRenderData() abstract = 0;
	virtual void Ontick(time_t _time) abstract = 0;
};

