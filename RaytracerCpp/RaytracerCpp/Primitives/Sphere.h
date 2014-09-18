#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "IPrimitive.h"

class Sphere : public IPrimitive {
private:
	Vector3D				mPosition;
	float					mRadius;

public:
	Sphere(const Sphere& s);
	Sphere(const Vector3D& pos, const float& radius);

	virtual bool			Initialize();
	virtual IntersectResult Intersect(Ray ray);

};

#endif