#pragma once

#include <vector>
#include <string>
#include <assert.h>
#include <GeneCommon.h>

namespace Gene { namespace IO {
	class File {
	private:
		char *m_Data = nullptr;

	public:
		~File();
		File(const char *filepath=nullptr);
		void Load(const char *filepath);

		const char *Contents() const 
        { 
            GE_ASSERT(m_Data != NULL); 

            return static_cast<const char*>(m_Data); 
        }
		void Free();

		static std::vector<std::string> ReadLines(const char *path);
	};
}}
