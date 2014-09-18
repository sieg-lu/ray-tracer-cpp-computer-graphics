#include <ctime>
#include "Raytracer.h"

Raytracer::Raytracer(string infilename)
	: mInFileName(infilename), mOutFileName(string("default"))
{

}

bool Raytracer::Initialize()
{
	mParser.Initialize();

	if (!mParser.Parse(mInFileName)) {
		cout << "No such file existed.\n";
		return false;
	}

	mWidth = mParser.mImageRes.width;
	mHeight = mParser.mImageRes.height;

	mPixelBuffer.resizeFast(mWidth, mHeight);
	mPixelBufferRef = mPixelBuffer.getRef();

	mBackgroundColor = mParser.mBkColor.color;

	mCamera = PerspectiveCamera(mParser.mCamera.center, mParser.mCamera.direction, Vector3D(0, 1, 0), 90);
	// (-10, 75, 60)
//	mCamera = PerspectiveCamera(Vector3D(0, 0, 10), Vector3D(0, 0, -1), Vector3D(0, 1, 0), 60);
	mCamera.Initialize(mWidth, mHeight);

	for (int i = 0; i < mParser.mSphereList.size(); i++) {
		IPrimitive* sph = new Sphere(mParser.mSphereList[i].center, mParser.mSphereList[i].radius);
		sph->SetAmbientColor(mParser.mSphereList[i].ambient.color);
		sph->SetDiffuseColor(mParser.mSphereList[i].diffuse.color);
		sph->SetSpecularColor(mParser.mSphereList[i].specular.color);
		sph->SetShininess(mParser.mSphereList[i].specular.n);
		sph->SetReflectiveness(0.5f);

		mScene.Push(sph);
	}
//	mScene.Push(new Sphere(Vector3D(0, 0, 0), 10));
	for (int i = 0; i < mParser.mTriangleList.size(); i++) {
		IPrimitive* tri = new Triangle(
			mParser.mTriangleList[i].point[0], 
			mParser.mTriangleList[i].point[1], 
			mParser.mTriangleList[i].point[2]);
		tri->SetAmbientColor(mParser.mTriangleList[i].ambient.color);
		tri->SetDiffuseColor(mParser.mTriangleList[i].diffuse.color);
		tri->SetSpecularColor(mParser.mTriangleList[i].specular.color);
		tri->SetShininess(mParser.mTriangleList[i].specular.n);
		tri->SetReflectiveness(0.5f);

		mScene.Push(tri);
	}
//	mScene.Push(new Triangle(Vector3D(-5, 0, -50), Vector3D(3, 3, 0), Vector3D(3, -3, 0)));
	for (int i = 0; i < mParser.mPlaneList.size(); i++) {
		IPrimitive* pla = new Plane(mParser.mPlaneList[i].normal, mParser.mPlaneList[i].depth);
		pla->SetAmbientColor(mParser.mPlaneList[i].ambient.color);
		pla->SetDiffuseColor(mParser.mPlaneList[i].diffuse.color);
		pla->SetSpecularColor(mParser.mPlaneList[i].specular.color);
		pla->SetShininess(mParser.mPlaneList[i].specular.n);
		pla->SetReflectiveness(0.1f);

		mScene.Push(pla);
	}

	for (int i = 0; i < mParser.mCylinderList.size(); i++) {
		IPrimitive* cyl = new Cylinder(
			mParser.mCylinderList[i].position, 
			mParser.mCylinderList[i].axis, 
			mParser.mCylinderList[i].radius,
			mParser.mCylinderList[i].len);
		cyl->SetAmbientColor(mParser.mCylinderList[i].ambient.color);
		cyl->SetDiffuseColor(mParser.mCylinderList[i].diffuse.color);
		cyl->SetSpecularColor(mParser.mCylinderList[i].specular.color);
		cyl->SetShininess(mParser.mCylinderList[i].specular.n);
		cyl->SetReflectiveness(0.1f);

		mScene.Push(cyl);
	}

//	mLightList.push_back(new AmbientLight(Vector3D(0.7, 0.7, 0.7)));
	for (int i = 0; i < mParser.mLightList.size(); i++) {
		switch (mParser.mLightList[i].lType)
		{
		case GLight::AmbientLight:
			{
				mLightList.push_back(new AmbientLight(mParser.mLightList[i].color));
			}
			break;
		case GLight::PointLight:
			{
				ILight* lit = new PointLight(mParser.mLightList[i].center, mParser.mLightList[i].color);
				lit->SetAttenuationA(0.0f);
				lit->SetAttenuationB(0.02f);
				lit->SetAttenuationC(0.0f);
				mLightList.push_back(lit);
			}
			break;
		case GLight::DirectionLight:
			{
				mLightList.push_back(new DirectionalLight(mParser.mLightList[i].direction, mParser.mLightList[i].color));
			}
			break;
		case GLight::SpotLight:
			{
				ILight* lit = new SpotLight(
					mParser.mLightList[i].center,
					mParser.mLightList[i].direction,
					mParser.mLightList[i].color,
					30, 60, 1.0);
				lit->SetAttenuationA(0.0f);
				lit->SetAttenuationB(0.02f);
				lit->SetAttenuationC(0.0f);
				mLightList.push_back(lit);
			}
			break;
		}
	}

	for (int i = 0; i < mLightList.size(); i++) {
		mLightList[i]->Initialize();
	}

	mOutFileName = mParser.mOutFilename;
	mScene.Initialize();
	mMaxRecursiveDepth = mParser.mRecursionDepth;
	mMaxDepth = 1000;

	return true;
}

bool Raytracer::Destroy()
{
	return true;
}

bool Raytracer::SaveToBmp()
{
	TFileOutputStream bmp((mOutFileName + ".bmp").c_str());
	TBmpFile::save(mPixelBuffer.getRef(), &bmp);

	return true;
}

bool Raytracer::Render()
{
	if (mPixelBufferRef.getIsEmpty()) {
		return false;
	}

	mPixelBufferRef.fillColor(Color32(0, 0, 0, 0));
	Color32* pixels = mPixelBufferRef.pdata;

	float dx = 1.0f / mWidth;
	float dy = 1.0f / mHeight;
	float dD = 255.0f / mMaxDepth;
	clock_t timeStart = clock();
	for (int y = 0; y < mHeight; y++) {
		if (y % 20 == 0) {
//			cout << "scanning " << y + 1 << "th line\n";
			printf("%.2f", y * 100.0 / mHeight);
			cout << "% complete...\n";
		}
		float sy = 1 - dy * y;
		for (int x = 0; x < mWidth; x++) {
			float sx = dx * x;

			Ray ray(mCamera.GenerateRay(sx, sy));
			Vector3D color = RayTraceRecursive(mScene, ray, 0);

			color = Limit(color, 0.0f, 1.0f);
			pixels[x].r = (UInt8)(color.r*255);
			pixels[x].g = (UInt8)(color.g*255);
			pixels[x].b = (UInt8)(color.b*255);
			pixels[x].a = 255;
		}
		(UInt8*&)pixels += mPixelBufferRef.byte_width;
	}
	cout << "100.00% complete...\n\n";
	cout << "Picture generated, time cost: " << clock() - timeStart << " millisecond(s)\n";
}

Vector3D Raytracer::RayTraceRecursive(Scene& scene, Ray ray, int currentDepth)
{
	if (currentDepth >= mMaxRecursiveDepth) {
		return Vector3D();
	}

	Vector3D color;
	IntersectResult result = scene.Intersect(ray);
	if (result.mIsHit) {
		for (int i = 0; i < mLightList.size(); i++) {
			color += mLightList[i]->LightIntensity(scene, result, mCamera);
		}
		
		if (result.mPrimitive->GetReflectiveness() > 0) {
			Vector3D R = result.mNormal * (-2 * Dot(result.mNormal, ray.GetDirection())) + ray.GetDirection();
			Ray reflectedRay(result.mPosition, R);
			color += RayTraceRecursive(scene, reflectedRay, currentDepth + 1) * result.mPrimitive->GetReflectiveness();
		}

	} else {
		color = mBackgroundColor;
	}

	return color;
}

