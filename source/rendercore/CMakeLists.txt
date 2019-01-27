
#
# External dependencies
#

find_package(cpplocate REQUIRED)
find_package(cppexpose REQUIRED)
find_package(glbinding REQUIRED)
find_package(globjects REQUIRED)
find_package(glm       REQUIRED)


#
# Library name and options
#

# Target name
set(target rendercore)

# Exit here if required dependencies are not met
message(STATUS "Lib ${target}")

# Set API export file and macro
string(MAKE_C_IDENTIFIER ${target} target_id)
string(TOUPPER ${target_id} target_id)
set(feature_file         "include/${target}/${target}_features.h")
set(export_file          "include/${target}/${target}_export.h")
set(template_export_file "include/${target}/${target}_api.h")
set(export_macro         "${target_id}_API")


#
# Sources
#

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(headers
    ${include_path}/rendercore.h

    ${include_path}/base/AbstractContext.h
    ${include_path}/base/AbstractGLContext.h
    ${include_path}/base/AbstractGLContextFactory.h
    ${include_path}/base/CachedValue.h
    ${include_path}/base/CachedValue.inl
    ${include_path}/base/Canvas.h
    ${include_path}/base/ChronoTimer.h
    ${include_path}/base/Environment.h
    ${include_path}/base/ExampleRenderer.h
    ${include_path}/base/GLContextFormat.h
    ${include_path}/base/GLContextUtils.h
    ${include_path}/base/Renderer.h

    ${include_path}/loaders/GlrawTextureLoader.h
    ${include_path}/loaders/RawFileNameSuffix.h
    ${include_path}/loaders/ShaderLoader.h

    ${include_path}/rendering/AbstractDrawable.h
    ${include_path}/rendering/Box.h
    ${include_path}/rendering/Camera.h
    ${include_path}/rendering/CameraUtils.h
    ${include_path}/rendering/Drawable.h
    ${include_path}/rendering/Drawable.inl
    ${include_path}/rendering/Icosahedron.h
    ${include_path}/rendering/Quad.h
    ${include_path}/rendering/Shape.h
    ${include_path}/rendering/ShapeType.h
    ${include_path}/rendering/Sphere.h
    ${include_path}/rendering/Triangle.h
)

set(sources
    ${source_path}/rendercore.cpp

    ${source_path}/base/AbstractContext.cpp
    ${source_path}/base/AbstractGLContext.cpp
    ${source_path}/base/AbstractGLContextFactory.cpp
    ${source_path}/base/Canvas.cpp
    ${source_path}/base/ChronoTimer.cpp
    ${source_path}/base/Environment.cpp
    ${source_path}/base/ExampleRenderer.cpp
    ${source_path}/base/GLContextFormat.cpp
    ${source_path}/base/GLContextUtils.cpp
    ${source_path}/base/Renderer.cpp

    ${source_path}/loaders/GlrawTextureLoader.cpp
    ${source_path}/loaders/RawFileNameSuffix.cpp
    ${source_path}/loaders/ShaderLoader.cpp

    ${source_path}/rendering/AbstractDrawable.cpp
    ${source_path}/rendering/Box.cpp
    ${source_path}/rendering/Camera.cpp
    ${source_path}/rendering/CameraUtils.cpp
    ${source_path}/rendering/Drawable.cpp
    ${source_path}/rendering/Icosahedron.cpp
    ${source_path}/rendering/Quad.cpp
    ${source_path}/rendering/Shape.cpp
    ${source_path}/rendering/Sphere.cpp
    ${source_path}/rendering/Triangle.cpp
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$"
    ${header_group} ${headers})
source_group_by_path(${source_path}  "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$"
    ${source_group} ${sources})


#
# Create library
#

# Build library
add_library(${target}
    ${sources}
    ${headers}
)

# Create namespaced alias
add_library(${META_PROJECT_NAME}::${target} ALIAS ${target})

# Export library for downstream projects
export(TARGETS ${target} NAMESPACE ${META_PROJECT_NAME}:: FILE ${PROJECT_BINARY_DIR}/cmake/${target}/${target}-export.cmake)

# Create feature detection header
# Compilers: https://cmake.org/cmake/help/v3.1/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE_%3CLANG%3E_COMPILER_ID
# Feature: https://cmake.org/cmake/help/v3.1/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html

# Check for availability of module; use pre-generated version if not found
if (WriterCompilerDetectionHeaderFound)
    write_compiler_detection_header(
        FILE ${feature_file}
        PREFIX ${target_id}
        COMPILERS AppleClang Clang GNU MSVC
        FEATURES cxx_alignas cxx_alignof cxx_constexpr cxx_final cxx_noexcept cxx_nullptr cxx_sizeof_member cxx_thread_local
        VERSION 3.2
    )
else()
    file(
        COPY ${PROJECT_SOURCE_DIR}/source/codegeneration/${target}_features.h
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/${target}
        USE_SOURCE_PERMISSIONS
    )
endif()

# Create API export header
generate_export_header(${target}
    EXPORT_FILE_NAME  ${export_file}
    EXPORT_MACRO_NAME ${export_macro}
)
generate_template_export_header(${target}
    ${target_id}
    ${template_export_file}
)


#
# Project options
#

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
    VERSION ${META_VERSION}
    SOVERSION ${META_VERSION_MAJOR}
)


#
# Include directories
#

target_include_directories(${target}
    PRIVATE
    ${PROJECT_BINARY_DIR}/source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include

    PUBLIC
    ${DEFAULT_INCLUDE_DIRECTORIES}

    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


#
# Libraries
#

target_link_libraries(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_LIBRARIES}
    cpplocate::cpplocate
    cppexpose::cppexpose
    glbinding::glbinding
    glbinding::glbinding-aux
    globjects::globjects
    glm

    INTERFACE
)


#
# Compile definitions
#

target_compile_definitions(${target}
    PRIVATE

    PUBLIC
    $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${target_id}_STATIC_DEFINE>
    ${DEFAULT_COMPILE_DEFINITIONS}

    INTERFACE
)


#
# Compile options
#

target_compile_options(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)


#
# Linker options
#

target_link_libraries(${target}
    PRIVATE

    PUBLIC
    ${DEFAULT_LINKER_OPTIONS}

    INTERFACE
)


#
# Target Health
#

perform_health_checks(
    ${target}
    ${sources}
    ${headers}
)


#
# Deployment
#

# Library
install(TARGETS ${target}
    EXPORT  "${target}-export"            COMPONENT dev
    RUNTIME DESTINATION ${INSTALL_BIN}    COMPONENT runtime
    LIBRARY DESTINATION ${INSTALL_SHARED} COMPONENT runtime
    ARCHIVE DESTINATION ${INSTALL_LIB}    COMPONENT dev
)

# Header files
install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# Generated header files
install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# CMake config
install(EXPORT ${target}-export
    NAMESPACE   ${META_PROJECT_NAME}::
    DESTINATION ${INSTALL_CMAKE}/${target}
    COMPONENT   dev
)
