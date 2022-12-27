#include "stdafx.h"
#include "FrustumCulling.h"

BoundCheck FrustumCulling::CheckBound(const Vector3& _ref)
{
	auto P = Planes.begin();
	while(P != Planes.end())	
	{
		if (P->IsOutSide(_ref))
			return BoundCheck::Outside;
		else if (P->GetDistance(_ref) == 0)
			return BoundCheck::Intersect;

		P++;
	}

	return BoundCheck::Inside;
}
