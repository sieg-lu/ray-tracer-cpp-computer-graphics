#ifndef __I_PRIMITIVE_H__
#define __I_PRIMITIVE_H__

#include "../RayTracer/IntersectResult.h"
#include "../RayTracer/Ray.h"

class IPrimitive {
private:
	Vector3D mAmbientColor;
	Vector3D mDiffuseColor;
	Vector3D mSpecularColor;
	int mShininess;

	float mReflectiveness;

public:
	virtual bool					Initialize() = 0;
	virtual IntersectResult			Intersect(Ray ray) = 0;

	Vector3D GetAmbientColor() const { return mAmbientColor; }
	void SetAmbientColor(Vector3D val) { mAmbientColor = val; }

	Vector3D GetDiffuseColor() const { return mDiffuseColor; }
	void SetDiffuseColor(Vector3D val) { mDiffuseColor = val; }

	Vector3D GetSpecularColor() const { return mSpecularColor; }
	void SetSpecularColor(Vector3D val) { mSpecularColor = val; }

	int GetShininess() const { return mShininess; }
	void SetShininess(int val) { mShininess = val; }

	float GetReflectiveness() const { return mReflectiveness; }
	void SetReflectiveness(float val) { mReflectiveness = val; }

};


#endif