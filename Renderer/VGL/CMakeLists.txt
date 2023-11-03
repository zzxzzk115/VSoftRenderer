set(TARGET_NAME VGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenMP
if (PLATFORM_DARWIN)
# libomp 15.0+ from brew is keg-only, so have to search in other locations.
# See https://github.com/Homebrew/homebrew-core/issues/112107#issuecomment-1278042927.
execute_process(COMMAND brew --prefix libomp
        OUTPUT_VARIABLE HOMEBREW_LIBOMP_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE)
set(OpenMP_C_FLAGS
        "-Xpreprocessor -fopenmp -I${HOMEBREW_LIBOMP_PREFIX}/include")
set(OpenMP_CXX_FLAGS
        "-Xpreprocessor -fopenmp -I${HOMEBREW_LIBOMP_PREFIX}/include")
set(OpenMP_C_LIB_NAMES omp)
set(OpenMP_CXX_LIB_NAMES omp)
set(OpenMP_omp_LIBRARY ${HOMEBREW_LIBOMP_PREFIX}/lib/libomp.dylib)
endif()
find_package(OpenMP REQUIRED)

add_library(${TARGET_NAME} src/Line.cpp
        src/Color.cpp
        src/Triangle2D.cpp
        src/FrameBuffer.cpp
        src/Triangle3D.cpp
        src/Utils.cpp
        src/Matrix4.cpp
        src/Texture2D.cpp
        src/VGL.cpp
        src/Matrix3.cpp
        src/ShadersCompile.cpp
)

# Add OpenMP support
target_include_directories(${TARGET_NAME} PRIVATE ${OpenMP_CXX_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} PRIVATE ${OpenMP_CXX_LIBRARIES})
target_compile_options(${TARGET_NAME} PRIVATE ${OpenMP_CXX_FLAGS})

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