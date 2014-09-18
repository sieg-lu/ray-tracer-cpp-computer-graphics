#include "Plane.h"
#include "Triangle.h"

Triangle::Triangle(const Triangle& t)
	: mPointA(t.mPointA), mPointB(t.mPointB), mPointC(t.mPointC)
{

}

Triangle::Triangle(const Vector3D& a, const Vector3D& b, const Vector3D& c)
	: mPointA(a), mPointB(b), mPointC(c)
{

}

bool Triangle::Initialize()
{
	return true;
}

IntersectResult Triangle::Intersect(Ray ray)
{
	/*
	Vector3D u, v, n;
	Vector3D w;
	u = mPointB - mPointA;
	v = mPointC - mPointA;
	n = Cross(u, v);

	Plane plane(n, mPointA);
//	plane.Initialize();
	IntersectResult tmpRes = plane.Intersect(ray);
	if (tmpRes.mIsHit) {
		Vector3D hitPoint = tmpRes.mPosition;

		float uu, uv, vv, wu, wv, D;
		uu = Dot(u, u);
		uv = Dot(u, v);
		vv = Dot(v, v);
		w = hitPoint - mPointA;
		wu = Dot(w, u);
		wv = Dot(w, v);
		D = uv * uv - uu * vv;

		float s, t;
		s = (uv * wv - vv * wu) / D;
		if (s < 0.0 || s > 1.0) {
			return IntersectResult::NoHit();
		}
		t = (uv * wu - uu * wv) / D;
		if (t < 0.0 || (s + t) > 1.0) {
			return IntersectResult::NoHit();
		}

		tmpRes.mPrimitive = this;
		return tmpRes;
	}
	return IntersectResult::NoHit();
	*/
	
	Vector3D u, v, n;
	Vector3D w0, w;
	double r, a, b;
	static const float epsilon = 1e-4;

	u = mPointB - mPointA;
	v = mPointC - mPointA;
	n = Cross(u, v);

	w0 = ray.GetOrigin() - mPointA;
	a = -Dot(n, w0);
	b = Dot(n, ray.GetDirection());

	if (b > -epsilon && b < epsilon) {
		return IntersectResult::NoHit();
	}

	r = a / b;
	if (r < 1.0) {
		return IntersectResult::NoHit();
	}

//	Vector3D hitPoint = ray.GetOrigin() + r * ray.GetDirection();
	Vector3D hitPoint = ray.GetSpecifiedPoint(r);

	double uu, uv, vv, wu, wv, D;
	uu = Dot(u, u);
	uv = Dot(u, v);
	vv = Dot(v, v);
	w = hitPoint - mPointA;
	wu = Dot(w, u);
	wv = Dot(w, v);
	D = 1.0 / (uv * uv - uu * vv);

	double s, t;
	s = (uv * wv - vv * wu) * D;
	if (s < 0.0 || s > 1.0) {
		return IntersectResult::NoHit();
	}
	t = (uv * wu - uu * wv) * D;
	if (t < 0.0 || (s + t) > 1.0) {
		return IntersectResult::NoHit();
	}

	IntersectResult result(true);
	result.mPrimitive = this;
	result.mDistance = Length(hitPoint - ray.GetOrigin());
	result.mPosition = hitPoint;
	result.mNormal = Normalize(n);

	return result;

	/*
	static const float epsilon = 1e-6;
	Vector3D e1, e2;
	e1 = mPointB - mPointA;
	e2 = mPointC - mPointA;

	Vector3D PN = Cross(ray.GetDirection(), e2);

	float temp = Dot(PN, e1);
	if (temp > -epsilon && temp < epsilon) {
		return IntersectResult::NoHit();
	}

	temp = 1.0f / temp;
	Vector3D s = ray.GetOrigin() - mPointA;
	float u = temp * Dot(s, PN);
	if (u < 0.0f || u > 1.0f) {
		return IntersectResult::NoHit();
	}

	Vector3D q = Cross(s, e1);
	float v = temp * Dot(ray.GetDirection(), q);
	if (v < 0.0f || v > 1.0f) {
		return IntersectResult::NoHit();
	}

	if (u + v > 1.0f) {
		return IntersectResult::NoHit();
	}
	float tHit = temp * Dot(e2, q);
	if (tHit <= epsilon) {
		return IntersectResult::NoHit();
	}

	IntersectResult result(true);
	result.mPrimitive = this;
	result.mDistance = tHit;
	result.mPosition = ray.GetSpecifiedPoint(tHit);
	result.mNormal = Normalize(Cross(e1, e2));

	return result;
	*/
}