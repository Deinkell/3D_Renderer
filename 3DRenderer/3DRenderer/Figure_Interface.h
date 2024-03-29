#pragma once
#include <vector>
#include "Figure_define.h"
#include "PhongData.h"

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
	PhongData PhongD{ Vector3(30.0f, 30.0f, 30.0f), Vector3(255.0f, 0.0f, 0.0f), Vector3(255.0f, 255.0f, 255.0f)};
	Matrix44 FigureMat44, WorldMat, MatWrdView;
	std::shared_ptr<std::vector<Vertex>> Vertices = std::make_shared<std::vector<Vertex>>();
	std::shared_ptr<std::vector<Index>> Indices = std::make_shared<std::vector<Index>>();
	FigureType Figure_type;
	RenderType Render_type = RenderType::PhongShading;	

public:
	Figure_Interface() = default;
	FORCEINLINE Figure_Interface(const std::shared_ptr<std::vector<Vertex>> _Vertices, 
		std::shared_ptr<std::vector<Index>> _Indices, FigureType _type)
	: Vertices(_Vertices), Indices(_Indices), Figure_type(_type){};
	FORCEINLINE Figure_Interface(const Vector3& _Pos, const FigureType& _type) 
	: Position(_Pos), Figure_type(_type) {}
	FORCEINLINE Figure_Interface(const FigureType& _type) : Figure_type(_type) {}
	FORCEINLINE Figure_Interface(const Figure_Interface& _ref)
	: Position(_ref.Position), Rotation(_ref.Rotation), Scale(_ref.Scale),
		FigureMat44(_ref.FigureMat44), Vertices(_ref.Vertices), 
		Indices(_ref.Indices), Figure_type(_ref.Figure_type) {};
	FORCEINLINE Figure_Interface(Figure_Interface&& _ref) noexcept
	:	Position(std::move(_ref.Position)), Rotation(std::move(_ref.Rotation)), Scale(std::move(_ref.Scale)),
		FigureMat44(std::move(_ref.FigureMat44)), Vertices(std::move(_ref.Vertices)),
		Indices(std::move(_ref.Indices)), Figure_type(std::move(_ref.Figure_type)), Render_type(std::move(_ref.Render_type)) {};
	
	virtual ~Figure_Interface();

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
	FORCEINLINE constexpr void SetAmbient(const Vector3& _amb) { PhongD.Ambient = _amb; }
	FORCEINLINE constexpr void SetDiffuse(const Vector3& _dif) { PhongD.Diffuse = _dif; }
	FORCEINLINE constexpr void SetSpecular(const Vector3& _spc) { PhongD.Specular = _spc; }
	FORCEINLINE constexpr void SetRenderType(const RenderType& _Type) {	Render_type = _Type; }
	// Set함수
	FORCEINLINE decltype(auto) GetVertices() { return Vertices; }
	FORCEINLINE decltype(auto) GetVerticesSize() { return Vertices->size(); }
	FORCEINLINE decltype(auto) GetVertex(const int& _idx) { return (*Vertices)[_idx]; }
	FORCEINLINE decltype(auto) GetIndices() { return Indices; }
	FORCEINLINE constexpr decltype(auto) GetFigureType() { return Figure_type; }
	FORCEINLINE constexpr decltype(auto) GetRenderType() { return Render_type; }
	FORCEINLINE constexpr decltype(auto) GetPosition() { return Position; }
	FORCEINLINE constexpr decltype(auto) GetRotation() { return Rotation; }
	FORCEINLINE constexpr decltype(auto) GetScale() { return Scale; }
	FORCEINLINE decltype(auto) GetMatrix44() { return FigureMat44; }
	FORCEINLINE decltype(auto) GetWrdViewMat() { return MatWrdView; }
	FORCEINLINE decltype(auto) GetPhongData() { return PhongD; }
	FORCEINLINE decltype(auto) GetWorldMat() { return WorldMat; }
	// Get함수
public:
	void MakeWorldMatrix(Matrix44* _Out);
	void MakeWorldMatrix_Inv(Matrix44* _Out);
	void MakeViewMatrix(Matrix44* _Out, const Matrix44& _CameraMatrix);
	void MakeViewMatrix_Inv(Matrix44* _Out, const Matrix44& _CameraMatrix);
	void MakeProjMatrix(Matrix44* _Out, const Matrix44& _ProjMat);
	void MakeProjMatrix_Inv(Matrix44* _Out, const Matrix44& _ProjMat);
	void MatXspin(Matrix44* _Out, const float& _Xspin);
	void MatYspin(Matrix44* _Out, const float& _Yspin);
	void MatZspin(Matrix44* _Out, const float& _Zspin);
	//공용으로 쓰는 매트릭스 생성함수
	FORCEINLINE void MakeMatrix(const Matrix44& _CameraMatrix, const Matrix44& _ProjMat)
	{
		MakeWorldMatrix(&WorldMat);		
		MakeViewMatrix(&FigureMat44,_CameraMatrix);
		MakeProjMatrix(&FigureMat44, _ProjMat);
		MakeViewMatrix(&MatWrdView,_CameraMatrix);		
	}
	FORCEINLINE void MakeMatrix_Inv(const Matrix44& _CameraMatrix, const Matrix44& _ProjMat)
	{
		MakeWorldMatrix_Inv(&WorldMat);
		MakeViewMatrix_Inv(&MatWrdView, _CameraMatrix);
		MakeViewMatrix_Inv(&FigureMat44, _CameraMatrix);		
		MakeProjMatrix_Inv(&FigureMat44, _ProjMat);
	}
public:
	virtual void Init() abstract = 0;
	virtual void Move(float _time) abstract = 0;
	virtual void MakeRenderData() abstract = 0;
	virtual void Ontick(float _time) abstract = 0;
};

