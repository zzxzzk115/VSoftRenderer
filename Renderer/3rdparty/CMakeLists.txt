set(THIRD_PARTY_FOLDER "3rdparty")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

if (NOT TARGET tinyobjloader)
    add_subdirectory(tinyobjloader)
    set_target_properties(tinyobjloader PROPERTIES FOLDER ${THIRD_PARTY_FOLDER}/tinyobjloader)
endif ()