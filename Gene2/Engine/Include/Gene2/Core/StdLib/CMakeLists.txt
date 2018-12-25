set(CurrentDir ${CMAKE_CURRENT_SOURCE_DIR})

set(StdLibHeaders
    ${CurrentDir}/Math.hpp
	${CurrentDir}/Array.hpp
	${CurrentDir}/String.hpp
	${CurrentDir}/Random.hpp
	${CurrentDir}/StringStream.hpp
	${CurrentDir}/Types.hpp
	${CurrentDir}/Memory.hpp
	${CurrentDir}/Queue.hpp

    PARENT_SCOPE
)