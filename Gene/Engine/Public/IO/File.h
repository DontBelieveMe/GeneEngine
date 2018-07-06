// Copyright 2017-2018 Barney Wilks. All Rights Reserved

#pragma once

#include <Core/String.h>
#include <Core/Array.h>
#include <GeneCommon.h>

#include <assert.h>

namespace gene { namespace io {
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
            GE_ASSERT(m_Data != NULL, "Trying to return null file contents data."); 

            return static_cast<const char*>(m_Data); 
        }

        /** Free up any resources consumed by this object (file handles etc). Is called by destructor, but can be called manually. */
		void Free();

		static uint8_t* LoadBinaryFile(const char *path);

        /** Static method to load all the lines of a text file into an Array<String>*/
		static Array<String> ReadLines(const char *path);
	};
}}
