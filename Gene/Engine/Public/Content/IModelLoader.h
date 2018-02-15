#pragma once

#include "GeneModel.h"

namespace Gene { namespace Content {
	class IModelLoader 
	{
	public:
		virtual GeneModel *Load(const char * filepath) = 0;
        virtual GeneModel *LoadFromMemory(const char *str) = 0;
        virtual ~IModelLoader(){}
	};
}}
