#include "Sphere.h"

Sphere::Sphere(const Sphere& s)
	: mPosition(s.mPosition), mRadius(s.mRadius)
{

}

Sphere::Sphere(const Vector3D& pos, const float& radius)
	: mPosition(pos), mRadius(radius)
{

}

bool Sphere::Initialize()
{
	return true;
}

IntersectResult Sphere::Intersect(Ray ray)
{
	Vector3D v = ray.GetOrigin() - mPosition;
	float a0 = Length2(v) - (mRadius * mRadius);
	float DdotV = Dot(ray.GetDirection(), v);

	if (DdotV <= 0) {
		float discr = DdotV * DdotV - a0;
		if (discr >= 0) {
			IntersectResult result(true);
			result.mPrimitive = this;
			result.mDistance = -DdotV - sqrt(discr);
			result.mPosition = ray.GetSpecifiedPoint(result.mDistance);
			result.mNormal = Normalize(result.mPosition - this->mPosition);
			return result;
		}
	}
	return IntersectResult::NoHit();
}

