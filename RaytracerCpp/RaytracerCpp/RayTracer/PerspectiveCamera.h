#ifndef __PERSPECTIVE_CAMERA_H__
#define __PERSPECTIVE_CAMERA_H__

#include "../VMath/VMath.h"
#include "Ray.h"

class PerspectiveCamera {
private:
	Vector3D				mPosition;
	Vector3D				mFront;
	Vector3D				mRefUp;
	float					mFovHorizontal;
	float					mFovVertical;

	Vector3D				mRight;
	Vector3D				mUp;
	float					mFovScaleHorizontal;
	float					mFovScaleVertical;

public:
	PerspectiveCamera() { }
	PerspectiveCamera(const Vector3D& pos, const Vector3D& front, const Vector3D& up, float fov);

	bool Initialize(int width, int height);
	Ray	GenerateRay(float x, float y);

	Vector3D GetPosition() const { return mPosition; }
	void SetPosition(Vector3D val) { mPosition = val; }

	Vector3D GetFront() const { return mFront; }
	void SetFront(Vector3D val) { mFront = val; }

};


#endif