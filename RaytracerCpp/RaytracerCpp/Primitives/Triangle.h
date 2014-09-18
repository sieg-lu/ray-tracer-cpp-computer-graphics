#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "IPrimitive.h"

class Triangle : public IPrimitive {
private:
	Vector3D mPointA, mPointB, mPointC;

public:
	Triangle(const Triangle& t);
	Triangle(const Vector3D& a, const Vector3D& b, const Vector3D& c);

	virtual bool					Initialize();
	virtual IntersectResult			Intersect(Ray ray);

};


#endif