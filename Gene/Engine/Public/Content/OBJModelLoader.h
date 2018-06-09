// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Content/IModelLoader.h>
#include <Content/GeneModel.h>

#include <sstream>

#include "TinyObjLoader.h"

namespace gene { namespace runtime {
	class OBJModelLoader : public IModelLoader 
	{
    private:
        virtual GeneModel *LoadFromData(const tinyobj::attrib_t& attrib, const Array<tinyobj::shape_t>& shapes, const Array<tinyobj::material_t>& materials);

	public:
		virtual GeneModel *Load(const char * filepath);
        virtual GeneModel *LoadFromMemory(const char *str);
	};
}}
