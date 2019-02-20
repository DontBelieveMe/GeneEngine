add_subdirectory(glfl)

set_target_properties(glfl PROPERTIES FOLDER "ThirdParty")

set(ThirdPartyGlobalIncludes
	${CMAKE_CURRENT_LIST_DIR}/glfl/pregenerated/GLFL/glfl.h
	${CMAKE_CURRENT_LIST_DIR}/stb_image/stb_image.h
	${CMAKE_CURRENT_LIST_DIR}/tinyobjloader/tinyobjloader/tiny_obj_loader.h
	PARENT_SCOPE
)
