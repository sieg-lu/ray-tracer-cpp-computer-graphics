#ifndef __INTERSECT_RESULT_H__
#define __INTERSECT_RESULT_H__

#include <cstdio>
#include "../VMath/VMath.h"

class IPrimitive;

class IntersectResult {
public:
//private:
	bool					mIsHit;

	IPrimitive*				mPrimitive;
	float					mDistance;
	Vector3D				mPosition;
	Vector3D				mNormal;

	IntersectResult(bool isHit);

	static inline IntersectResult NoHit() { return IntersectResult(false); }
};

#endif