#ifndef __PLANE_H__
#define __PLANE_H__

#include "IPrimitive.h"

class Plane : public IPrimitive {
private:
	Vector3D mNormal;
	float mDepth;

	Vector3D mPosition;

public:
	Plane(const Plane& pl);
	Plane(const Vector3D& normal, const float& depth);
	Plane(const Vector3D& normal, const Vector3D& position);

	virtual bool Initialize();
	virtual IntersectResult Intersect(Ray ray);

};

#endif