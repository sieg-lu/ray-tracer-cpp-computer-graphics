#ifndef __AMBIENT_LIGHT__
#define __AMBIENT_LIGHT__

#include "ILight.h"

class AmbientLight : public ILight {
private:

public:
	AmbientLight(Vector3D color);

	virtual bool Initialize();
	virtual Vector3D LightIntensity(Scene& scene, IntersectResult intersect, const PerspectiveCamera& cam);

};


#endif