#ifndef __I_LIGHT_H__
#define __I_LIGHT_H__

#include "../VMath/VMath.h"
#include "../RayTracer/Scene.h"
#include "../RayTracer/PerspectiveCamera.h"
#include "../RayTracer/IntersectResult.h"

class ILight {
protected:
	Vector3D mColor;
	// mAttenuation[0] = a, mAttenuation[1] = b, mAttenuation[2] = c
	Vector3D mAttenuation;
	bool mIsShadow;
	float mShadowReducingFactor;

public:
	ILight(Vector3D color, bool shadow = true) : mColor(color), mIsShadow(shadow)
	{
		mAttenuation.x = 1;
		mAttenuation.y = 0;
		mAttenuation.z = 0;
		mShadowReducingFactor = 0.08;
	}
	virtual ~ILight() { }

	virtual bool Initialize() = 0;
	virtual Vector3D LightIntensity(Scene& scene, IntersectResult intersect, const PerspectiveCamera& cam) = 0;

	void SetAttenuationA(float t) { mAttenuation.x = t; }
	void SetAttenuationB(float t) { mAttenuation.y = t; }
	void SetAttenuationC(float t) { mAttenuation.z = t; }

	bool GetShadow() const { return mIsShadow; }
	void SetShadow(bool val) { mIsShadow = val; }
};


#endif