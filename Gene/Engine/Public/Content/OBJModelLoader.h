#pragma once

#include <Content/IModelLoader.h>
#include <Content/GeneModel.h>

namespace Gene { namespace Content {
	class OBJModelLoader : public IModelLoader 
	{
		virtual GeneModel *Load(const char * filepath);
	};
}}