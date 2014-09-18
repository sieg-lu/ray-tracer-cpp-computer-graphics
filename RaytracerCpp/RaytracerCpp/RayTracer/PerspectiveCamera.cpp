#include "PerspectiveCamera.h"

#include <cmath>

PerspectiveCamera::PerspectiveCamera(const Vector3D& pos, const Vector3D& front, const Vector3D& up, float fov)
	: mPosition(pos), mFront(Normalize(front)), mRefUp(up), mFovHorizontal(fov), mRight(Vector3D()), mUp(Vector3D())
{

}

bool PerspectiveCamera::Initialize(int width, int height)
{
	mRight = Cross(mFront, mRefUp);
	mUp = Cross(mRight, mFront);
	mFovScaleHorizontal = mFovHorizontal * (PI / 180.0f);
	mFovVertical = mFovHorizontal / ((float)width / (float)height);
	mFovScaleVertical = mFovVertical * (PI / 180.0f);

	return true;
}

Ray PerspectiveCamera::GenerateRay(float x, float y)
{
	Vector3D r = mRight * ((x - 0.5f) * mFovScaleHorizontal);
	Vector3D u = mUp * ((y - 0.5f) * mFovScaleVertical);
	return Ray(mPosition, Normalize(mFront + r + u));
}

