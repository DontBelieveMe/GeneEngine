#pragma once

#include "GeneModel.h"

namespace Gene { namespace Content {
	class IModelLoader 
	{
	public:
		virtual GeneModel *Load(const char * filepath) = 0;
	};
}}