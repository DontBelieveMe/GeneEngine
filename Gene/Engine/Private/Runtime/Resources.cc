// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#include <Runtime/Resources.h>
#include <Debug/Logger.h>

using namespace gene;

ResourceManager* ResourceManager::s_StaticInstance = nullptr;

ResourceManager *ResourceManager::Get()
{
	return s_StaticInstance;
}

void ResourceManager::SetStaticInstance(ResourceManager *assetManger) {
	s_StaticInstance = assetManger;

#ifndef NDEBUG
	if (!assetManger)
	{
		LOG(LogLevel::Warning, "Asset manager static instance being set to null");
	}
#endif
}