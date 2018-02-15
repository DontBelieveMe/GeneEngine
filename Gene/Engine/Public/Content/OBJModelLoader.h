#pragma once

#include <Content/IModelLoader.h>
#include <Content/GeneModel.h>
#include <sstream>
#include "TinyObjLoader.h"

namespace Gene { namespace Content {
	class OBJModelLoader : public IModelLoader 
	{
    private:
        virtual GeneModel *LoadFromData(const tinyobj::attrib_t& attrib, const Array<tinyobj::shape_t>& shapes, const Array<tinyobj::material_t>& materials);

	public:
		virtual GeneModel *Load(const char * filepath);
        virtual GeneModel *LoadFromMemory(const char *str);
	};
}}
