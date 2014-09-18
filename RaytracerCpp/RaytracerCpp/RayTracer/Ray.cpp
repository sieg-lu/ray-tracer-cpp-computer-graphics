#include "Ray.h"

Ray::Ray(const Ray& r)
	: mOrigin(r.mOrigin), mDirection(r.mDirection)
{

}

Ray::Ray(const Vector3D& origin, const Vector3D& direction)
	: mOrigin(origin), mDirection(direction)
{

}

Vector3D Ray::GetSpecifiedPoint(float distance)
{
	return mOrigin + Normalize(mDirection) * distance;
}

