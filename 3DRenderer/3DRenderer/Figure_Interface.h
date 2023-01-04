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
	// Z��� Y���� �����͸� �ٲ㼭 �̿��Ͽ� Z��� Y���� ��ü, upVector�� Z���� �ǵ��� ��
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
	//������Ʈ�� ���ؽ�����Ʈ�� �����ͷ� ����, �淮����(��ü �ϳ��� ����, ������)�̿�
	FORCEINLINE constexpr void SetIndices(const auto _Indices) { Indices = _Indices; }
	//������Ʈ�� �ε�������Ʈ�� �����ͷ� ����, �淮����(��ü �ϳ��� ����, ������)�̿�
	FORCEINLINE constexpr void SetFigureType(const auto _type) { Figure_type = _type; }
	FORCEINLINE constexpr void SetPosition(const auto _Pos) { Position = _Pos; }
	FORCEINLINE constexpr void SetRotation(const auto _Rot) { Rotation = _Rot; }
	FORCEINLINE constexpr void SetScale(const auto _Scale) { Scale = _Scale; }
	FORCEINLINE constexpr void SetMatrix44(const auto _Mat) { FigureMat44 = _Mat; }
	// Set�Լ�
	FORCEINLINE decltype(auto) GetVertices() { return Vertices; }
	FORCEINLINE decltype(auto) GetIndices() { return Indices; }
	FORCEINLINE constexpr decltype(auto) GetFigureType() { return Figure_type; }
	FORCEINLINE constexpr decltype(auto) GetPosition() { return Position; }
	FORCEINLINE constexpr decltype(auto) GetRotation() { return Rotation; }
	FORCEINLINE constexpr decltype(auto) GetScale() { return Scale; }
	FORCEINLINE decltype(auto) GetMatrix44() { return FigureMat44; }
	// Get�Լ�
public:
	void MakeWorldMatrix();
	void MakeViewMatrix(const Matrix44& _CameraMatrix);
	void MakeProjMatrix();
	//�������� ���� ��Ʈ���� �����Լ�

public:
	virtual void Init() abstract = 0;
	virtual void Move(time_t _time) abstract = 0;
	virtual void MakeRenderData() abstract = 0;
	virtual void Ontick(time_t _time) abstract = 0;
};

