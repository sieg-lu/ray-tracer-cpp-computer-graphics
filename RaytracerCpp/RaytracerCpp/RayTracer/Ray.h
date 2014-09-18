#ifndef __RAY_H__
#define __RAY_H__

#include "../VMath/VMath.h"

class Ray {
private:
	Vector3D				mOrigin;
	Vector3D				mDirection;

public:
	Ray(const Ray& r);
	Ray(const Vector3D& origin, const Vector3D& direction);

	Vector3D				GetSpecifiedPoint(float distance);

	Vector3D				GetOrigin() const							{ return mOrigin; }
	void					SetOrigin(Vector3D val)						{ mOrigin = val; }

	Vector3D				GetDirection() const						{ return mDirection; }
	void					SetDirection(Vector3D val)					{ mDirection = val; }

};


#endif