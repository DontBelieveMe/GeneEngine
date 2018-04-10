// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Core/Array.h>

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

	public:
		static ResourceManager *Get();
		static void SetStaticInstance(ResourceManager *assetManager);
	};
}