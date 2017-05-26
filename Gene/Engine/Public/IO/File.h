#pragma once

#include <vector>

namespace Gene { namespace IO {
	class File {
	private:
		char *m_Data = nullptr;

	public:
		~File();
		File(const char *filepath=nullptr);
		void Load(const char *filepath);

		const char *Contents() const { return static_cast<const char*>(m_Data); }
		void Free();

		static std::vector<std::string> ReadLines(const char *path);
	};
}}