#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include "ILight.h"

class SpotLight : public ILight {
private:
	Vector3D mPosition;
	Vector3D mDirection;
	float mTheta;
	float mPhi;
	float mFalloff;

	Vector3D mInverseDirection;
	float mCosTheta;
	float mCosPhi;
	float mBaseMultiplier;

public:
	SpotLight(Vector3D pos, Vector3D dire, Vector3D color, float theta, float phi, float falloff);

	virtual bool Initialize();
	virtual Vector3D LightIntensity(Scene& scene, IntersectResult intersect, const PerspectiveCamera& cam);

};


#endif