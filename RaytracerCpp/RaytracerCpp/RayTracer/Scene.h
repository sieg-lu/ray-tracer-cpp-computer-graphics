#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "../Primitives/IPrimitive.h"

class Scene : public IPrimitive {
private:
	std::vector<IPrimitive*> mPrimitiveList;

public:
	void Push(IPrimitive* prim);

	bool Initialize();
	bool Destroy();

	virtual IntersectResult Intersect(Ray ray);

};


#endif