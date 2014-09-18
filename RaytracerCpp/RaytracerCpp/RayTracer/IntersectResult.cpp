#include "IntersectResult.h"

IntersectResult::IntersectResult(bool isHit)
	: mIsHit(isHit), mPrimitive(NULL), mDistance(0), mPosition(Vector3D()), mNormal(Vector3D())
{

}
