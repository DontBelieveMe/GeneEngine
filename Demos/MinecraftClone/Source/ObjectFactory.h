#pragma once

#include <Content/GeneModel.h>
#include "Cube.h"

class ObjectFactory {
private:
	Gene::Content::GeneModel *m_CubeMesh;

public:
	void InitAllTypes();
	Cube CreateCube(Vector3 position);

	static ObjectFactory *Get() {
		static ObjectFactory objs;
		return &objs;
	}
};