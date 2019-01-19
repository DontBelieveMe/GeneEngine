add_subdirectory(glfl)

set_target_properties(glfl PROPERTIES FOLDER "ThirdParty")

set(ThirdPartyGlobalIncludes
	${CMAKE_CURRENT_LIST_DIR}/glfl/pregenerated/GLFL
	PARENT_SCOPE
)
