#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3D direction, Vector3D color)
	: mDirection(Normalize(direction)), mInverseDirection(mDirection * -1), ILight(color)
{

}

bool DirectionalLight::Initialize()
{
	return true;
}

Vector3D DirectionalLight::LightIntensity(Scene& scene, IntersectResult intersect, const PerspectiveCamera& cam)
{
	if (mIsShadow) {
		Ray shadowRay(intersect.mPosition, mInverseDirection);
		IntersectResult shadowResult = scene.Intersect(shadowRay);
		if (shadowResult.mIsHit) {
			return -(this->mColor * this->mShadowReducingFactor);
		}
	}

	Vector3D colorRes;
	float NdotL = Dot(intersect.mNormal, mInverseDirection);
	if (NdotL > 0) {
		colorRes = colorRes + 
			intersect.mPrimitive->GetDiffuseColor() * this->mColor * NdotL;
	}

	Vector3D V = Normalize(cam.GetPosition() - intersect.mPosition);
	Vector3D h = Normalize(V + mInverseDirection);
	float NdotH = Dot(intersect.mNormal, h);
	if (NdotH > 0) {
		colorRes = colorRes + 
			intersect.mPrimitive->GetSpecularColor() * this->mColor * powf(NdotH, intersect.mPrimitive->GetShininess());
	}

	return colorRes;
}


