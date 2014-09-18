#include "Cylinder.h"

Cylinder::Cylinder(const Cylinder& cyl)
	: mPosition(cyl.mPosition), mAxis(cyl.mAxis), mRadius(cyl.mRadius)
{

}

Cylinder::Cylinder(Vector3D pos, Vector3D axis, float radius, float len)
	: mPosition(pos), mAxis(axis), mRadius(radius), mLength(len)
{

}

bool Cylinder::Initialize()
{
	return true;
}

IntersectResult Cylinder::Intersect(Ray ray)
{
	/*
	Vector3D RC, n, D, O;
	float d, t, s, ln, iin, oout, lamda;

	RC = ray.GetOrigin() - this->mPosition;
	n = Cross(ray.GetDirection(), mAxis);
	ln = Length(n);

	if (fabs(ln) < 1e-4) {
		return IntersectResult::NoHit();
	}
	n = Normalize(n);
	d = fabs(Dot(RC, n));

	if (d <= mRadius) {
		O = Cross(RC, mAxis);
		t = -Dot(O, n) / ln;
		O = Cross(n, mAxis);
		O = Normalize(O);
		s = fabs(sqrt(mRadius * mRadius - d * d) / Dot(ray.GetDirection(), O));

		iin = t - s;
		oout = t + s;
		if (t < 0) {
			if (oout < 0) {
				return IntersectResult::NoHit();
			} else {
				lamda = oout;
			}
		} else if (oout < 0) {
			lamda = iin;
		} else if (iin < oout) {
			lamda = iin;
		} else {
			lamda = oout;
		}

		IntersectResult result(true);
		result.mPrimitive = this;
		result.mDistance = lamda;
		result.mPosition = ray.GetSpecifiedPoint(result.mDistance);
		Vector3D HB = result.mPosition - mPosition;
		result.mNormal = Normalize(HB - mAxis * Dot(HB, mAxis));

		return result;
	}
	*/

	Vector3D D = ray.GetDirection();
	Vector3D E = ray.GetOrigin() - mPosition;

	double A = D.x * D.x + D.z * D.z;
	double B = 2.0f * E.x * D.x + 2.0f * E.z * D.z;
	double C = E.x * E.x + E.z * E.z - mRadius * mRadius;

	double discr = B * B - 4.0f * A * C;

	if (discr < 0) {
		return IntersectResult::NoHit();
	}

	double t1 = (-B - sqrt(discr)) / 2.0f * A;
	double t2 = (-B + sqrt(discr)) / 2.0f * A;

	double y1 = (ray.GetOrigin() + t1*D).y;
	double y2 = (ray.GetOrigin() + t2*D).y;

	double yMin = mPosition.y - (mLength / 2.0f);
	double yMax = mPosition.y + (mLength / 2.0f);

	if (y1 < yMin || y1 > yMax || y2 < yMin || y2 > yMax) {
		return IntersectResult::NoHit();
	}

	double t = -1;

	if (fabs(y1 - yMin) < 1e-4 || fabs(y2 - yMin) < 1e-4) {
		t = (yMin - E.y) / D.y;
	} else if (fabs(y1 - yMax) < 1e-4 || fabs(y2 - yMax) < 1e-4) {
		t = (yMax - E.y) / D.y;
	}

	if (t1 > 0 && t2 >= t1) {
		t = t1;
	} else if (t2 > 0 && t1 > t2) {
		t = t2;
	}

	if (t <= 0) {
		return IntersectResult::NoHit();
	}

	IntersectResult result(true);
	result.mPrimitive = this;
	result.mDistance = t;
	result.mPosition = ray.GetSpecifiedPoint(result.mDistance);

	Vector3D middenpunt = mPosition;
	middenpunt.y =  result.mPosition.y;
	result.mNormal = Normalize(result.mPosition - middenpunt);

	return result;
}
