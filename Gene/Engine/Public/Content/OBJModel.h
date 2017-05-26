#pragma once

namespace Gene { namespace Content {
	class OBJModel
	{
	private:
		bool m_Loaded = false;

	public:
		OBJModel(const char *path);
		OBJModel() {}

		~OBJModel();

		void Load(const char *filepath);

		inline bool IsLoaded() const { return m_Loaded; }
	};
}}