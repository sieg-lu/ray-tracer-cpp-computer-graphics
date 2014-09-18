#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../VMath/VMath.h"
using namespace std;


struct GVertex {
	Vector3D pta;
	Vector3D ptb;
};

struct GMaterial {
	enum MtrlType {
		Ambient,
		Diffuse,
		Specular,
	};
	MtrlType mType;
	Vector3D color;
	int n;
};

struct GSphere {
	Vector3D center;
	float radius;
	GMaterial ambient;
	GMaterial diffuse;
	GMaterial specular;
};

struct GTriangle {
	Vector3D point[3];
	GMaterial ambient;
	GMaterial diffuse;
	GMaterial specular;
};

struct GPlane {
	Vector3D normal;
	float depth;
	GMaterial ambient;
	GMaterial diffuse;
	GMaterial specular;
};

struct GCylinder {
	Vector3D position;
	Vector3D axis;
	float radius;
	float len;
	GMaterial ambient;
	GMaterial diffuse;
	GMaterial specular;
};

struct GLight {
	enum LightType {
		PointLight,
		DirectionLight,
		SpotLight,
		AmbientLight,
	};
	LightType lType;
	Vector3D center, direction;
	Vector3D color;
};

struct GCamera {
	Vector3D center, direction;
};

struct GImageResolution {
	int width, height;
};

struct GBackGround {
	Vector3D color;
};

class Parser
{
public:
	vector<GVertex> mVectorList;
	GMaterial mAmbientMtrl;
	GMaterial mDiffuseMtrl;
	GMaterial mSpecularMtrl;
	vector<GSphere> mSphereList;
	vector<GTriangle> mTriangleList;
	vector<GPlane> mPlaneList;
	vector<GCylinder> mCylinderList;
	vector<GLight> mLightList;
	GCamera mCamera;
	GImageResolution mImageRes;
	string mOutFilename;
	GBackGround mBkColor;
	int mRecursionDepth;

	bool Initialize();
	bool Parse(string filename);

private:
	void BuildTriangle2(int index0, int index1, int index2);
	void BuildQuadrilateral(int index0, int index1, int index2, int index3);
	void BuildHexahedral(int index0, int index1, int index2, int index3, int index4, int index5, int index6, int index7);

};


#endif ///> end of __PARSER_H__