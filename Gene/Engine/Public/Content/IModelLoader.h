// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include "GeneModel.h"

namespace gene { namespace runtime {
	class IModelLoader 
	{
	public:
		virtual GeneModel *Load(const char * filepath) = 0;
        virtual GeneModel *LoadFromMemory(const char *str) = 0;
        virtual ~IModelLoader(){}
	};
}}
