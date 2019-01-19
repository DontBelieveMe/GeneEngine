set(Source
	pregenerated/glfl.cpp
)

set(Headers
	pregenerated/GLFL/glfl.h
	pregenerated/GLFL/glfl_func_indices.h
	pregenerated/GLFL/glfl_proxy_proto__.h
	pregenerated/GLFL/glfl_simple_proto__.h
)

add_library(glfl ${Source} ${Headers})
