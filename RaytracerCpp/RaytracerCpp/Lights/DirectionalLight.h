#ifndef __DIRECTIONAL_LIGHT_H__
#define __DIRECTIONAL_LIGHT_H__

#include "ILight.h"

class DirectionalLight : public ILight {
private:
	Vector3D mDirection;
	Vector3D mInverseDirection;

public:
	DirectionalLight(Vector3D direction, Vector3D color);

	virtual bool Initialize();
	virtual Vector3D LightIntensity(Scene& scene, IntersectResult intersect, const PerspectiveCamera& cam);

};

#endif