#include "stdafx.h"
#include "Render.h"

Render::Render()
{
	DibSec.InitializeDib();
	DepthBuf.Initialize(DibSec.GetClientX(), DibSec.GetClientY());
	InitializeCriticalSection(&CRSC);
}

Render::~Render()
{
	DeleteCriticalSection(&CRSC);
}

void Render::Initialize(std::shared_ptr<ObjectMNG>& _ObjMng, std::shared_ptr<ThreadPool>& _Thdpool, std::shared_ptr<Camera>& _Camera)
{
	ObjectMng_Component = _ObjMng;
	ThreadPool_Component = _Thdpool;
	Camera_Component = _Camera;
}

void Render::OnRender(float _elapsedTime)
{
	if (ThreadPool_Component == nullptr || ObjectMng_Component == nullptr)
		return;

	Vertex tmp[3];
	tmp[0].Pos = Quaternion(10.f, 10.f, 0.1f, 1.f); tmp[0].Color.G = 1.f;
	tmp[1].Pos = Quaternion(20.f, 30.f, 0.1f, 1.f);
	tmp[2].Pos = Quaternion(40.f, 20.f, 0.1f, 1.f);

	Vertex tmp1[3];
	tmp1[0].Pos = Quaternion(30.f, 10.f, 0.1f, 1.f); tmp1[0].Color.B = 1.f;
	tmp1[1].Pos = Quaternion(40.f, 30.f, 0.1f, 1.f);
	tmp1[2].Pos = Quaternion(60.f, 20.f, 0.1f, 1.f);

	ThreadPool_Component->EnqueueJob([this](Vertex tmp[]) { RasterizePolygon(tmp[0], tmp[1], tmp[2]); }, tmp);
	ThreadPool_Component->EnqueueJob([this](Vertex tmp[]) { RasterizePolygon(tmp[0], tmp[1], tmp[2]); }, tmp1);

	DibSec.BitBltDibSection();
	DepthBuf.ClearDepthBuffer();
}

void Render::BackSpaceCuling()
{
}

Vector3 Render::Geometric_centroid_VertexCalc(const Vector3& _p3p1Vec, const Vector3& _p3p2Vec, const Vector3& _W)
{
	Vector3 u = _p3p1Vec, v = _p3p2Vec;
	float udotv = MathLib::DotProduct(u.X, u.Y, v.X, v.Y),
		  wdotv = MathLib::DotProduct(_W.X, _W.Y, v.X, v.Y),
		  wdotu = MathLib::DotProduct(_W.X, _W.Y, u.X, u.Y),
		  uu = MathLib::DotProduct(u.X, u.Y, u.X, u.Y),
		  vv = MathLib::DotProduct(v.X, v.Y, v.X, v.Y);

	float t = (wdotu * udotv - wdotv * uu) / ((udotv * udotv) - uu * vv);
	float s = (wdotv*udotv - wdotu*vv) / (udotv*udotv - uu*vv);
	return std::move(Vector3(s, t, 1 - s - t));
}

void Render::RasterizePolygon(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3)
{
	/*
	std::vector<Vertex> tmpVertices{ _p1, _p2, _p3 };
	std::vector<PerspectiveTest> testPlanes = {
		{TestFuncW0, EdgeFuncW0},
		{TestFuncNY, EdgeFuncNY},
		{TestFuncPY, EdgeFuncPY},
		{TestFuncNX, EdgeFuncNX},
		{TestFuncPX, EdgeFuncPX},
		{TestFuncFar, EdgeFuncFar},
		{TestFuncNear, EdgeFuncNear}
	};

	for (auto& p : testPlanes)
		p.ClipTriangles(tmpVertices); //�ﰢ�� Ŭ����(ndc �������� �ﰢ�� ��������)

	if (tmpVertices.size() == 0)
		return;

	Vector3 Vertices[3]{ Vector3(tmpVertices[0].Pos.X, tmpVertices[0].Pos.Y, tmpVertices[0].Pos.Z),
						Vector3(tmpVertices[1].Pos.X, tmpVertices[1].Pos.Y, tmpVertices[1].Pos.Z),
						Vector3(tmpVertices[2].Pos.X, tmpVertices[2].Pos.Y, tmpVertices[2].Pos.Z)};
	*/
/**************�ӽ�****************/
	Vector3 Vertices[3]{ Vector3(_p1.Pos.X, _p1.Pos.Y, _p1.Pos.Z),
						Vector3(_p2.Pos.X, _p2.Pos.Y, _p2.Pos.Z),
						Vector3(_p3.Pos.X, _p3.Pos.Y, _p3.Pos.Z) };
/**************�ӽ�****************/
	int CorrectionX = DibSec.GetClientX() / 2, CorrectionY = DibSec.GetClientY() / 2;
	int ResultX, ResultY;

	MathLib::SortByYvalue(Vertices, Vertices);
	LineFunction2D LineFunc[3];
	MathLib::Make2DLinFunction(&LineFunc[0], Vertices[0], Vertices[2]);
	MathLib::Make2DLinFunction(&LineFunc[1], Vertices[0], Vertices[1]);
	MathLib::Make2DLinFunction(&LineFunc[2], Vertices[1], Vertices[2]);

	for (int i = Vertices[0].Y; i <= Vertices[2].Y; i++)
	{
		if (i <= Vertices[1].Y)//Y���� ũ��� ���� �� ���ؽ�����Ʈ�� �߰������� ���� ��(X,y ���� 0�� ������ ���ϱ⶧���� ���x)
		{
			float StartX = LineFunc[0].GetXValueByPoint(Vertices[0].X, i), 
					EndX = LineFunc[1].GetXValueByPoint(Vertices[0].X, i);

			if (StartX > EndX)
				MathLib::SwapElement(&StartX, &EndX);
			//���ؽ� 3���� ���� y�� ������������ �����Ͽ� �� ���������� ������ �������� ����,
			//�ּ�y���� �ִ�y������ ���̻��̿��� �� ������ �������� �̿��Ͽ� i = y ������ �� ���� ������ ���� ���ϰ�
			//�� �� ������ ��� ���ڸ��� ä��(�ﰢ�� ���ο� ������ �׸��� ������ �ﰢ���� ��� ä��)
			for (int j = StartX; j <= EndX; j++)
			{
				ResultX = j + CorrectionX; 
				ResultY = i + CorrectionY;				
				//PhongShader(������ �븻���� ���� ����Ʈ �ݻ簪 �����ġ)
				if(!DibSec.CheckIntersectClientRect(ResultX, ResultY))
					continue;

				Vector3 GeoPos = Geometric_centroid_VertexCalc(Vertices[0] - Vertices[2], 
													Vertices[1] - Vertices[2], Vector3(ResultX, ResultY, 0));

				float PixelZvalue = Vertices[0].Z * GeoPos.X + Vertices[1].Z * GeoPos.Y + Vertices[2].Z * GeoPos.Z;
				
			
				EnterCriticalSection(&CRSC);
				if (!DepthBuf.CheckDepthBuffer(ResultX, ResultY, PixelZvalue))
				{
					LeaveCriticalSection(&CRSC);
					continue;
				}
				LeaveCriticalSection(&CRSC);
				//���̹��� üũ			
				
				DibSec.DotPixel(ResultX, ResultY, _p1.Color.ToColor32());		
			}
		}
		else//Y���� ũ��� ���� �� ���ؽ�����Ʈ�� �߰������� Ŭ ��(X,y ���� 0�� ������ ���ϱ⶧���� ���x)
		{
			float StartX = LineFunc[0].GetXValueByPoint(Vertices[2].X, i),
					EndX = LineFunc[2].GetXValueByPoint(Vertices[2].X, i);

			if (StartX > EndX)
				MathLib::SwapElement(&StartX, &EndX);
			//���ؽ� 3���� ���� y�� ������������ �����Ͽ� �� ���������� ������ �������� ����,
			//�ּ�y���� �ִ�y������ ���̻��̿��� �� ������ �������� �̿��Ͽ� i = y ������ �� ���� ������ ���� ���ϰ�
			//�� �� ������ ��� ���ڸ��� ä��(�ﰢ�� ���ο� ������ �׸��� ������ �ﰢ���� ��� ä��)
			for (int j = StartX; j <= EndX; j++)
			{
				ResultX = j + CorrectionX;
				ResultY = i + CorrectionY;				
				//PhongShader(������ �븻���� ���� ����Ʈ �ݻ簪 �����ġ)
				if (!DibSec.CheckIntersectClientRect(ResultX, ResultY))
					continue;

				Vector3 GeoPos = Geometric_centroid_VertexCalc(Vertices[0] - Vertices[2],
												Vertices[1] - Vertices[2], Vector3(ResultX, ResultY, 0));

				float PixelZvalue = Vertices[0].Z * GeoPos.X + Vertices[1].Z * GeoPos.Y + Vertices[2].Z * GeoPos.Z;

				EnterCriticalSection(&CRSC);
				if (!DepthBuf.CheckDepthBuffer(ResultX, ResultY, PixelZvalue))
				{
					LeaveCriticalSection(&CRSC);
					continue;					
				}
				LeaveCriticalSection(&CRSC);
				//���̹��� üũ			
				
				DibSec.DotPixel(ResultX, ResultY, _p1.Color.ToColor32());				
			}
		}
	}
}

Color32 Render::MakePhongShader(const Vector3& _ObjPos, const Vector3& _PixelNormal)
{
	//���Ɽ�� ������ ���(�ȼ����� �������� �븻�� ���ϴµ��� ���귮�� �ʹ� �þ�� ���Ɽ���� ����)
	LightObj* Lighting = ObjectMng_Component->GetLightSun();
	Vector3 l_DirLight = _ObjPos - Lighting->GetPosition();
	Vector3 v_ObjToCamera = _ObjPos - Camera_Component->GetPosition();
	Vector3 r_ReflectVec = -1 * 2 * (MathLib::DotProduct((-1 * l_DirLight), _PixelNormal)) * _PixelNormal - l_DirLight;
	float a_Shining = LightObj::ShiningConst;

	//��ü���� Material(Ambient, Diffuse, Specular)���� �ʿ���ϴµ�, Ȯ�� �� �߰� �ʿ�

	return Color32();
}

void Render::RenderFPS(float _elapsedTime)
{
	DibSec.SetWindowsTitleFPS(_elapsedTime);
}
