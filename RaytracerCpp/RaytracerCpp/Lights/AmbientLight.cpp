#include "AmbientLight.h"


AmbientLight::AmbientLight(Vector3D color)
	: ILight(color)
{

}

bool AmbientLight::Initialize()
{
	return true;
}

Vector3D AmbientLight::LightIntensity(Scene& scene, IntersectResult intersect, const PerspectiveCamera& cam)
{
	return intersect.mPrimitive->GetAmbientColor() * this->mColor;
}

