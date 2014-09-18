#include "Parser.h"


bool Parser::Initialize()
{
	mVectorList.clear();

	mAmbientMtrl.mType = GMaterial::MtrlType::Ambient;
	mAmbientMtrl.color = Vector3D(0.2f, 0.2f, 0.2f);
	mAmbientMtrl.n = 0;

	mDiffuseMtrl.mType = GMaterial::MtrlType::Diffuse;
	mDiffuseMtrl.color = Vector3D(1.0f, 1.0f, 1.0f);
	mDiffuseMtrl.n = 0;

	mSpecularMtrl.mType = GMaterial::MtrlType::Specular;
	mSpecularMtrl.color = Vector3D(1.0f, 1.0f, 1.0f);
	mSpecularMtrl.n = 64;

	mSphereList.clear();
	mTriangleList.clear();
	mPlaneList.clear();
	mLightList.clear();

	mCamera.center = Vector3D(0.0f);
	mCamera.direction = Vector3D(0.0f, 0.0f, -1000.0f);

	mImageRes.width = 512;
	mImageRes.height = 512;

	mOutFilename = string("default");
	mBkColor.color = Vector3D(0.0f);

	mRecursionDepth = 64;

	return true;
}

bool Parser::Parse(string filename)
{
	ifstream finVector(filename), fin(filename);
	if (!fin) {
		return false;
	}

	string cmd, buffer;
	while (getline(finVector, buffer)) {
		if (buffer == "") {
			continue;;
		}
		istringstream iss(buffer);
		iss >> cmd;
		if (cmd == "vv") {
			GVertex vv;
			float x, y, z, dx, dy, dz;
			iss >> x >> y >> z >> dx >> dy >> dz;
			vv.pta = Vector3D(x, y, z);
			vv.ptb = Vector3D(dx, dy, dz);
			mVectorList.push_back(vv);
		}
	}

	while (getline(fin, buffer)) {
		if (buffer == "") {
			continue;;
		}
		istringstream iss(buffer);
		iss >> cmd;
		if (cmd == "am") {
			float r, g, b;
			iss >> r >> g >> b;
			mAmbientMtrl.color.r = r;
			mAmbientMtrl.color.g = g;
			mAmbientMtrl.color.b = b;
		} else if (cmd == "dm") {
			float r, g, b;
			iss >> r >> g >> b;
			mDiffuseMtrl.color.r = r;
			mDiffuseMtrl.color.g = g;
			mDiffuseMtrl.color.b = b;
		} else if (cmd == "sm") {
			float r, g, b;
			iss >> r >> g >> b;
			mSpecularMtrl.color.r = r;
			mSpecularMtrl.color.g = g;
			mSpecularMtrl.color.b = b;
		} else if (cmd == "ss") {
			int index;
			iss >> index;
			GSphere sph;
			sph.center = mVectorList[index].pta;
			sph.radius = Length(mVectorList[index].ptb);
			sph.ambient = mAmbientMtrl;
			sph.diffuse = mDiffuseMtrl;
			sph.specular = mSpecularMtrl;
			mSphereList.push_back(sph);
		} else if (cmd == "ts") {
			int index[3];
			iss >> index[0] >> index[1] >> index[2];
			BuildTriangle2(index[0], index[1], index[2]);			
		} else if (cmd == "ps") {
			int index;
			iss >> index;
			GPlane plane;
			plane.depth = mVectorList[index].pta.z;
			plane.normal = mVectorList[index].ptb;
			plane.ambient = mAmbientMtrl;
			plane.diffuse = mDiffuseMtrl;
			plane.specular = mSpecularMtrl;
			mPlaneList.push_back(plane);
		} else if (cmd == "cyl") {
			int index;
			float rad, len;
			iss >> index >> rad >> len;
			GCylinder cyl;
			cyl.position = mVectorList[index].pta;
			cyl.axis = mVectorList[index].ptb;
			cyl.radius = rad;
			cyl.len = len;
			cyl.ambient = mAmbientMtrl;
			cyl.diffuse = mDiffuseMtrl;
			cyl.specular = mSpecularMtrl;
			mCylinderList.push_back(cyl);
		} else if (cmd == "quad") {
			int index[4];
			iss >> index[0] >> index[1] >> index[2] >> index[3];
			BuildQuadrilateral(index[0], index[1], index[2], index[3]);
		} else if (cmd == "hex") {
			int index[8];
			for (int i = 0; i < 8; i++) {
				iss >> index[i];
			}
			BuildHexahedral(index[0], index[1], index[2], index[3], index[4], index[5], index[6], index[7]);
		} else if (cmd == "pl") {
			GLight light;
			int index;
			float r, g, b;
			iss >> index >> r >> g >> b;
			light.lType = GLight::LightType::PointLight;
			light.color = Vector3D(r, g, b);
			light.center = mVectorList[index].pta;
			light.direction = mVectorList[index].ptb;
			mLightList.push_back(light);
		} else if (cmd == "dl") {
			GLight light;
			int index;
			float r, g, b;
			iss >> index >> r >> g >> b;
			light.lType = GLight::LightType::DirectionLight;
			light.color = Vector3D(r, g, b);
			light.center = mVectorList[index].pta;
			light.direction = mVectorList[index].ptb;
			mLightList.push_back(light);
		} else if (cmd == "sl") {
			GLight light;
			int index;
			float r, g, b;
			iss >> index >> r >> g >> b;
			light.lType = GLight::LightType::SpotLight;
			light.color = Vector3D(r, g, b);
			light.center = mVectorList[index].pta;
			light.direction = mVectorList[index].ptb;
			mLightList.push_back(light);
		} else if (cmd == "al") {
			GLight light;
			int index;
			float r, g, b;
			iss >> index >> r >> g >> b;
			light.lType = GLight::LightType::AmbientLight;
			light.color = Vector3D(r, g, b);
// 			light.center = mVectorList[index].pta;
// 			light.direction = mVectorList[index].ptb;
			mLightList.push_back(light);
		} else if (cmd == "cc") {
			int index;
			iss >> index;
			mCamera.center = mVectorList[index].pta;
			mCamera.direction = Normalize(mVectorList[index].ptb - mCamera.center);
		} else if (cmd == "ir") {
			iss >> mImageRes.width >> mImageRes.height;
		} else if (cmd == "back") {
			iss >> mBkColor.color.r >> mBkColor.color.g >> mBkColor.color.b;
		} else if (cmd == "rdepth") {
			iss >> mRecursionDepth;
		} else if (cmd == "out") {
			iss >> mOutFilename;
		}
	}

	return true;
}

void Parser::BuildTriangle2(int index0, int index1, int index2)
{
	GTriangle tri;
	tri.point[0] = mVectorList[index0].pta;
	tri.point[1] = mVectorList[index1].pta;
	tri.point[2] = mVectorList[index2].pta;
	tri.ambient = mAmbientMtrl;
	tri.diffuse = mDiffuseMtrl;
	tri.specular = mSpecularMtrl;
	mTriangleList.push_back(tri);

	GTriangle tri2;
	tri2.point[0] = tri.point[2];
	tri2.point[1] = tri.point[1];
	tri2.point[2] = tri.point[0];
	tri2.ambient = mAmbientMtrl;
	tri2.diffuse = mDiffuseMtrl;
	tri2.specular = mSpecularMtrl;
	mTriangleList.push_back(tri2);
}

void Parser::BuildQuadrilateral(int index0, int index1, int index2, int index3)
{
	BuildTriangle2(index0, index1, index2);
	BuildTriangle2(index0, index2, index3);
}

void Parser::BuildHexahedral(int index0, int index1, int index2, int index3, int index4, int index5, int index6, int index7)
{
	BuildQuadrilateral(index0, index1, index2, index3);
	BuildQuadrilateral(index4, index5, index6, index7);
	BuildQuadrilateral(index0, index3, index7, index4);
	BuildQuadrilateral(index1, index2, index6, index5);
	BuildQuadrilateral(index0, index1, index5, index4);
	BuildQuadrilateral(index3, index2, index6, index7);
}
