#ifndef __CYLINDER_H__
#define __CYLINDER_H__

#include "IPrimitive.h"

class Cylinder : public IPrimitive {
private:
	Vector3D mPosition;
	Vector3D mAxis;
	float mRadius;
	float mLength;

public:
	Cylinder(const Cylinder& cyl);
	Cylinder(Vector3D pos, Vector3D axis, float radius, float len);

	virtual bool Initialize();
	virtual IntersectResult Intersect(Ray ray);

};


#endif