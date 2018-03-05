#pragma once

#include <vector>
#include <string>
#include <assert.h>
#include <GeneCommon.h>

namespace Gene { namespace IO {
    // TODO: Implement it so a File object can be reused -> e.g Load() , Free() then can Load() again.
    /** Class that represents a file object in memory. One object can only ever represent one file. */
	class File {
	private:
		char *m_Data = nullptr;

	public:
		~File();

        /** If a filename is specified create load that files data into memory. Otherwise do nothing & just create the object. */
        File(const char *filepath = nullptr);

        /** Will load the files data into memory, but only if no data has been loaded yet (e.g this function has not been called or constructor with filename argument). */
		void Load(const char *filepath);

        /** Return the data contained inside the File object. */
		const char *Contents() const 
        { 
            GE_ASSERT(m_Data != NULL); 

            return static_cast<const char*>(m_Data); 
        }

        /** Free up any resources consumed by this object (file handles etc). Is called by destructor, but can be called manually. */
		void Free();

        /** Static method to load all the lines of a text file into an Array<std::string>*/
		static Array<std::string> ReadLines(const char *path);
	};
}}
