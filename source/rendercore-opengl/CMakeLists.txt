
#
# External dependencies
#

find_package(cpplocate REQUIRED)
find_package(cppassist REQUIRED)
find_package(cppfs     REQUIRED)
find_package(glbinding REQUIRED)
find_package(globjects REQUIRED)
find_package(glm       REQUIRED)


#
# Library name and options
#

# Target name
set(target rendercore-opengl)

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
    ${include_path}/enums.h

    ${include_path}/AbstractGLContext.h
    ${include_path}/AbstractGLContextFactory.h
    ${include_path}/Box.h
    ${include_path}/Buffer.h
    ${include_path}/Buffer.inl
    ${include_path}/Geometry.h
    ${include_path}/GLContextFormat.h
    ${include_path}/GLContextUtils.h
    ${include_path}/Icosahedron.h
    ${include_path}/Material.h
    ${include_path}/MaterialAttribute.h
    ${include_path}/MaterialAttribute.inl
    ${include_path}/Mesh.h
    ${include_path}/Mesh.inl
    ${include_path}/MeshRenderer.h
    ${include_path}/Program.h
    ${include_path}/Quad.h
    ${include_path}/SceneRenderer.h
    ${include_path}/Shader.h
    ${include_path}/Sphere.h
    ${include_path}/Texture.h
    ${include_path}/TimeMeasurement.h
    ${include_path}/Triangle.h
    ${include_path}/VertexAttribute.h

    ${include_path}/scene/MeshComponent.h
)

set(sources
    ${source_path}/AbstractGLContext.cpp
    ${source_path}/AbstractGLContextFactory.cpp
    ${source_path}/Box.cpp
    ${source_path}/Buffer.cpp
    ${source_path}/Geometry.cpp
    ${source_path}/GLContextFormat.cpp
    ${source_path}/GLContextUtils.cpp
    ${source_path}/Icosahedron.cpp
    ${source_path}/Material.cpp
    ${source_path}/MaterialAttribute.cpp
    ${source_path}/Mesh.cpp
    ${source_path}/MeshRenderer.cpp
    ${source_path}/Program.cpp
    ${source_path}/Quad.cpp
    ${source_path}/SceneRenderer.cpp
    ${source_path}/Shader.cpp
    ${source_path}/Sphere.cpp
    ${source_path}/Texture.cpp
    ${source_path}/TimeMeasurement.cpp
    ${source_path}/Triangle.cpp
    ${source_path}/VertexAttribute.cpp

    ${source_path}/scene/MeshComponent.cpp
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
    cppassist::cppassist
    cppfs::cppfs
    glbinding::glbinding
    glbinding::glbinding-aux
    globjects::globjects
    glm
    ${META_PROJECT_NAME}::rendercore

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
