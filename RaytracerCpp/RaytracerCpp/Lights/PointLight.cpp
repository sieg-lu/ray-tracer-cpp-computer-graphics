#include "PointLight.h"

#include <iostream>

PointLight::PointLight(Vector3D pos, Vector3D color)
	: mPosition(pos), ILight(color)
{

}

bool PointLight::Initialize()
{
	return true;
}

Vector3D PointLight::LightIntensity(Scene& scene, IntersectResult intersect, const PerspectiveCamera& cam)
{
	Vector3D delta = mPosition - intersect.mPosition;
	float rr = Length2(delta);
	float r = sqrt(rr);
	float r1 = 1.0 / r;
	Vector3D inverseDire = Normalize(delta);

	if (mIsShadow) {
		Ray shadowRay(intersect.mPosition, inverseDire);
		IntersectResult shadowResult = scene.Intersect(shadowRay);
		if (shadowResult.mIsHit && shadowResult.mDistance <= r) {
			return -(this->mColor * this->mShadowReducingFactor);
		}
	}

	float diffuseAttenuation = 1.0 / (mAttenuation.x + mAttenuation.y * r + mAttenuation.z * rr);
	float specularAttenuation = 1.0 / (mAttenuation.x + mAttenuation.y * r + mAttenuation.z * rr);
	Vector3D colorRes;

	// Diffuse Material
	float NdotL = Dot(intersect.mNormal, inverseDire);

	// std::cout << NdotL << std::endl;
	if (NdotL > 0) {
		colorRes = colorRes + 
			intersect.mPrimitive->GetDiffuseColor() * this->mColor * NdotL * diffuseAttenuation;
	}
	
	// Specular Material
	Vector3D Vo = cam.GetPosition() - intersect.mPosition;
	Vector3D V = Normalize(Vo);
	Vector3D h = Normalize(V + inverseDire);
	float NdotH = Dot(intersect.mNormal, h);
	if (NdotH > 0) {
		colorRes = colorRes + 
			intersect.mPrimitive->GetSpecularColor() * this->mColor * powf(NdotH, intersect.mPrimitive->GetShininess()) * specularAttenuation;
	}

	return colorRes;
}

