#include "stdafx.h"
#include "Render.h"

Render::Render()
{
	DibSec.InitializeDib();
}

void Render::OnRender()
{
	if (ThreadPool_Component == nullptr || ObjectMng_Component == nullptr)
		return;


}

void Render::BackSpaceCuling()
{
}

void Render::PlaneCulling()
{
}

void Render::RasterizePolygon(const Vertex& _p1, const Vertex& _p2, const Vertex& _p3, DibSection& _DibSec)
{
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
	MathLib::SortByYvalue(Vertices, Vertices);
	LineFunction2D LineFunc[3];
	MathLib::Make2DLinFunction(&LineFunc[0], Vertices[0], Vertices[2]);
	MathLib::Make2DLinFunction(&LineFunc[1], Vertices[0], Vertices[1]);
	MathLib::Make2DLinFunction(&LineFunc[2], Vertices[1], Vertices[2]);

	for (int i = Vertices[2].Y; i <= Vertices[0].Y; i++)
	{
		if (i <= Vertices[1].Y)//Y���� ũ��� ���� �� ���ؽ�����Ʈ�� �߰������� ���� ��(X,y ���� 0�� ������ ���ϱ⶧���� ���x)
		{
			float StartX = LineFunc[0].GetXValueByPoint(Vertices[0].X, i), 
					EndX = LineFunc[1].GetXValueByPoint(Vertices[0].X, i);

			if (StartX < EndX)
				MathLib::SwapElement(&StartX, &EndX);
			//���ؽ� 3���� ���� y�� ������������ �����Ͽ� �� ���������� ������ �������� ����,
			//�ּ�y���� �ִ�y������ ���̻��̿��� �� ������ �������� �̿��Ͽ� i = y ������ �� ���� ������ ���� ���ϰ�
			//�� �� ������ ��� ���ڸ��� ä��(�ﰢ�� ���ο� ������ �׸��� ������ �ﰢ���� ��� ä��)
			for (int j = StartX; j <= EndX; j++)
			{
				//Zbuffer �׸��� Ȯ����ġ
				//PhongShader(������ �븻���� ���� ����Ʈ �ݻ簪 �����ġ)
		
				_DibSec.DotPixel(j, i, _p1.Color.ToColor32());
			}
		}
		else//Y���� ũ��� ���� �� ���ؽ�����Ʈ�� �߰������� Ŭ ��(X,y ���� 0�� ������ ���ϱ⶧���� ���x)
		{
			float StartX = LineFunc[0].GetXValueByPoint(Vertices[2].X, i),
					EndX = LineFunc[2].GetXValueByPoint(Vertices[2].X, i);

			if (StartX < EndX)
				MathLib::SwapElement(&StartX, &EndX);
			//���ؽ� 3���� ���� y�� ������������ �����Ͽ� �� ���������� ������ �������� ����,
			//�ּ�y���� �ִ�y������ ���̻��̿��� �� ������ �������� �̿��Ͽ� i = y ������ �� ���� ������ ���� ���ϰ�
			//�� �� ������ ��� ���ڸ��� ä��(�ﰢ�� ���ο� ������ �׸��� ������ �ﰢ���� ��� ä��)
			for (int j = StartX; j <= EndX; j++)
			{
				//Zbuffer �׸��� Ȯ����ġ
				//PhongShader(������ �븻���� ���� ����Ʈ �ݻ簪 �����ġ)

				_DibSec.DotPixel(j, i, _p1.Color.ToColor32());
			}
		}
	}
}
