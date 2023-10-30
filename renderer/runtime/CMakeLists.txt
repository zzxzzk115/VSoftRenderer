set(TARGET_NAME VSoftRendererRuntime)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${TARGET_NAME} src/Line.cpp
        src/Color.cpp
        src/Triangle2D.cpp
        src/RenderConfig.cpp
        src/FrameBuffer.cpp
        src/Triangle3D.cpp
        src/Utils.cpp
)

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Runtime")

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/WX->")

# Link dependencies
target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/${TARGET_NAME}-${PROJECT_VERSION}>
)