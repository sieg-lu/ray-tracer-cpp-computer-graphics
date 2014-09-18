#include <string>
#include "../hGraphic32/hGraphic32.h"
#include "../RayTracer/Raytracer.h"
using std::string;

// This code is highly effected and taught by Milo Yip's blog:
// http://www.cnblogs.com/miloyip/archive/2010/03/29/1698953.html
// http://www.cnblogs.com/miloyip/archive/2010/04/02/1702768.html
// Highly admired and appreciated his help.

// Also be helped by Bin Bo.

Raytracer* gRaytracer;

int main(int argc, char* argv[])
{
	string infilename = "default.txt";
	if (argc >= 2) {
		infilename = string(argv[1]);
	}
	gRaytracer = new Raytracer(infilename);
	if (!gRaytracer->Initialize()) {
		system("pause");
		return 0;
	}
	gRaytracer->Render();
	gRaytracer->SaveToBmp();
	gRaytracer->Destroy();
	delete gRaytracer;

//	system("pause");
	return 0;
}