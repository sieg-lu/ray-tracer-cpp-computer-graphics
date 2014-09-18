#include "Plane.h"

Plane::Plane(const Plane& pl)
	: mNormal(Normalize(pl.mNormal)), mDepth(pl.mDepth)
{

}

Plane::Plane(const Vector3D& normal, const float& depth)
	: mNormal(Normalize(normal)), mDepth(depth)
{

}

Plane::Plane(const Vector3D& normal, const Vector3D& position)
	: mNormal(Normalize(normal)), mPosition(position)
{

}

bool Plane::Initialize()
{
	mPosition = mNormal * mDepth;

	return true;
}

IntersectResult Plane::Intersect(Ray ray)
{
	float a = Dot(ray.GetDirection(), mNormal);
	if (a >= 0) {
		return IntersectResult::NoHit();
	}

	float b = Dot(mNormal, ray.GetOrigin() - mPosition);
	IntersectResult result(true);
	result.mPrimitive = this;
	result.mDistance = -b / a;
	result.mPosition = ray.GetSpecifiedPoint(result.mDistance);
	result.mNormal = mNormal;

	return result;
}

