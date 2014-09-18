#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

#include <iostream>
#include "../hGraphic32/hGraphic32.h"
#include "../VMath/VMath.h"
#include "PerspectiveCamera.h"
#include "Scene.h"
#include "../Primitives/Sphere.h"
#include "../Primitives/Triangle.h"
#include "../Primitives/Plane.h"
#include "../Primitives/Cylinder.h"
#include "../Lights/AmbientLight.h"
#include "../Lights/PointLight.h"
#include "../Lights/DirectionalLight.h"
#include "../Lights/SpotLight.h"
#include "../Common/Parser.h"
using namespace std;

class Raytracer {
private:
	int						mWidth, mHeight;
	string					mOutFileName;
	string					mInFileName;

	TPixels32				mPixelBuffer;
	TPixels32Ref			mPixelBufferRef;

	PerspectiveCamera		mCamera;
	Scene					mScene;
	vector<ILight*>			mLightList;
	Vector3D				mBackgroundColor;

	int						mMaxDepth;
	int						mMaxRecursiveDepth;

	Parser					mParser;

public:
	Raytracer(string infilename);

	bool					Initialize();
	bool					Destroy();
	bool					SaveToBmp();

	bool					Render();

	Vector3D				RayTraceRecursive(Scene& scene, Ray ray, int currentDepth);

};



#endif