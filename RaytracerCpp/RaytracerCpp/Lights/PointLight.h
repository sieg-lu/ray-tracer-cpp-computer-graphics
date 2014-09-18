#ifndef __POINT_LIGHT_H__
#define __POINT_LIGHT_H__

#include "ILight.h"

class PointLight : public ILight {
private:
	Vector3D mPosition;

public:
	PointLight(Vector3D pos, Vector3D color);

	virtual bool Initialize();
	virtual Vector3D LightIntensity(Scene& scene, IntersectResult intersect, const PerspectiveCamera& cam);

};

#endif