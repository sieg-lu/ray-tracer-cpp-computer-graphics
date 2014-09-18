#include "SpotLight.h"

SpotLight::SpotLight(Vector3D pos, Vector3D dire, Vector3D color, float theta, float phi, float falloff)
	: mPosition(pos), mDirection(Normalize(dire)), ILight(color)
	, mTheta(theta), mPhi(phi), mFalloff(falloff)
{

}

bool SpotLight::Initialize()
{
	mInverseDirection = mDirection * -1;
	mCosTheta = cos(mTheta * PI / 180.0 / 2.0);
	mCosPhi = cos(mPhi * PI / 180.0 / 2.0);
	mBaseMultiplier = 1.0 / (mCosTheta - mCosPhi);

	return true;
}

Vector3D SpotLight::LightIntensity(Scene& scene, IntersectResult intersect, const PerspectiveCamera& cam)
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

	float spot;
	float SdotL = Dot(mInverseDirection, inverseDire);
	if (SdotL >= mCosTheta) {
		spot = 1.0;
	} else if (SdotL <= mCosPhi) {
		spot = 0.0;
	} else {
		spot = powf((SdotL - mCosPhi) * mBaseMultiplier, mFalloff);
	}

	float diffuseAttenuation = 1.0 / (mAttenuation.x + mAttenuation.y * r + mAttenuation.z * rr);
	float specularAttenuation = 1.0 / (mAttenuation.x + mAttenuation.y * r + mAttenuation.z * rr);

	// Diffuse Material
	float NdotL = Dot(intersect.mNormal, inverseDire);
	Vector3D colorRes;

	// std::cout << NdotL << std::endl;
	if (NdotL > 0) {
		colorRes = colorRes + 
			intersect.mPrimitive->GetDiffuseColor() * this->mColor * NdotL * spot * diffuseAttenuation;
	}

	Vector3D Vo = cam.GetPosition() - intersect.mPosition;
	Vector3D V = Normalize(Vo);
	Vector3D h = Normalize(V + inverseDire);
	float NdotH = Dot(intersect.mNormal, h);
	if (NdotH > 0) {
		colorRes = colorRes + 
			intersect.mPrimitive->GetSpecularColor() * this->mColor * powf(NdotH, intersect.mPrimitive->GetShininess()) * spot * specularAttenuation;
	}

	return colorRes;
}

