#include "Scene.h"

void Scene::Push(IPrimitive* prim)
{
	mPrimitiveList.push_back(prim);
}

bool Scene::Initialize()
{
	bool flag = true;
	for (int i = 0; i < mPrimitiveList.size(); i++) {
		flag &= mPrimitiveList[i]->Initialize();
	}
	return flag;
}

bool Scene::Destroy()
{
	for (int i = 0; i < mPrimitiveList.size(); i++) {
		delete mPrimitiveList[i];
	}
	mPrimitiveList.clear();

	return true;
}

IntersectResult Scene::Intersect(Ray ray)
{
	double inf = 1e30;
	float minDist = inf;
	IntersectResult minResult = IntersectResult::NoHit();

	for (int i = 0; i < mPrimitiveList.size(); i++) {
		IntersectResult res = mPrimitiveList[i]->Intersect(ray);
		if (res.mIsHit && (res.mDistance < minDist)) {
			minDist = res.mDistance;
			minResult = res;
		}
	}
	return minResult;
}

