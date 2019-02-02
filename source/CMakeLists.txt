
#
# Configuration for all sub-projects
#

# Generate version-header
configure_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME}/${META_PROJECT_NAME}-version.h)


#
# Sub-projects
#

# Libraries
set(IDE_FOLDER "")
add_subdirectory(rendercore)
add_subdirectory(rendercore-opengl)
add_subdirectory(rendercore-glfw)
add_subdirectory(rendercore-examples)

# Tools
set(IDE_FOLDER "Tools")
add_subdirectory(viewer-glfw)


#
# Deployment
#

# Deploy generated headers
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME} DESTINATION include COMPONENT dev)
