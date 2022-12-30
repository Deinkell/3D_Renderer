#include "stdafx.h"
#include "Render.h"

Render::Render()
{
	DibSec.InitializeDib();
}

void Render::OnRender(float _elapsedTime)
{
	if (ThreadPool_Component == nullptr || ObjectMng_Component == nullptr)
		return;

	//ThreadPool_Component->EnqueueJob(&RasterizePolygon, , , , DibSec);
	Vertex tmp[3];
	tmp[0].Pos = Quaternion(10.f, 10.f, 0.f, 1.f); tmp[0].Color.G = 1.f;
	tmp[1].Pos = Quaternion(20.f, 30.f, 0.f, 1.f);
	tmp[2].Pos = Quaternion(40.f, 20.f, 0.f, 1.f);

	ThreadPool_Component->EnqueueJob([this](Vertex tmp[]) { RasterizePolygon(tmp[0], tmp[1], tmp[2]); }, tmp);
	DibSec.BitBltDibSection();
}

void Render::BackSpaceCuling()
{
}

void Render::PlaneCulling()
{
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
	int CorrectionX = DibSec.GetClientX() / 2;
	int CorrectionY = DibSec.GetClientY() / 2;

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
				//Zbuffer �׸��� Ȯ����ġ
				//PhongShader(������ �븻���� ���� ����Ʈ �ݻ簪 �����ġ)
		
				DibSec.DotPixel(j + CorrectionX, i + CorrectionY, _p1.Color.ToColor32());
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
				//Zbuffer �׸��� Ȯ����ġ
				//PhongShader(������ �븻���� ���� ����Ʈ �ݻ簪 �����ġ)

				DibSec.DotPixel(j + CorrectionX, i + CorrectionY, _p1.Color.ToColor32());
			}
		}
	}
}
