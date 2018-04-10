// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Core/Array.h>
#include <Debug/Logger.h>
#include <Core/String.h>

namespace Gene {
	template <typename T>
	using ResourceHandle = T * const;

	typedef unsigned int ResourceId;

	class IResource {};

	class ResourceManager
	{
	private:
		static ResourceManager *s_StaticInstance;

	private:
		HashMap<ResourceId, IResource*> m_Resources;

	public:
		template <typename T, typename... Args>
		ResourceHandle<T> LoadAsset(ResourceId id, const Args&... args)
		{
			HashMap<ResourceId, IResource*>::iterator it = m_Resources.find(id);
			if (it != m_Resources.end())
			{
				return const_cast<ResourceHandle<T>>(static_cast<T*>((*it).second));
			}

			T* asset = new T;
			asset->Load(args...);
			m_Resources.insert(std::make_pair(id, asset));

			return const_cast<ResourceHandle<T>>(asset);
		}

		template <typename T>
		ResourceHandle<T> GetAsset(ResourceId id)
		{
			HashMap<ResourceId, IResource*>::iterator it = m_Resources.find(id);
			if (it != m_Resources.end())
			{
				return const_cast<ResourceHandle<T>>(static_cast<T*>((*it).second));
			}

			LOG(LogLevel::Warning, "ResourceHandler: Resource " + ToString(id) + " does not exist, returning NULL from GetAsset");
			return nullptr;
		}

	public:
		static ResourceManager *Get();
		static void SetStaticInstance(ResourceManager *assetManager);
	};
}