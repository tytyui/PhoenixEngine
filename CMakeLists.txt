#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)
project(PhoenixEngine)

# Enable debug symbols by default
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug CACHE STRING
       "Choose the type of build, options are: None Debug Release RelWithDebInfo
MinSizeRel."
       FORCE )
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

set(PH_EXTINC_DIR "${PROJECT_SOURCE_DIR}/Solution/Libraries/Include")
set(PH_EXTLIB_DIR "${PROJECT_SOURCE_DIR}/Solution/Libraries/Lib")

# Set version information in a EngineConfig.h file
set(PH_VERSION_MAJOR 1)
set(PH_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/CMake/EngineConfig.h.in"
  "${PROJECT_BINARY_DIR}/Project/PhoenixEngine/Config/EngineConfig.h"
  )

include_directories ("${PROJECT_SOURCE_DIR}/Solution/PhoenixEngine/Source")

set(PH_SOURCE_DIR "Solution/PhoenixEngine/Source")

#Source 
file(GLOB AUDIO_SRC
    "${PH_SOURCE_DIR}/Audio/*.h"
    "${PH_SOURCE_DIR}/Audio/*.cpp"
)
source_group("Source\\Audio" FILES ${AUDIO_SRC})

file(GLOB CORE_SRC
    "${PH_SOURCE_DIR}/Core/*.h"
    "${PH_SOURCE_DIR}/Core/*.cpp"
)
source_group("Source\\Core" FILES ${CORE_SRC})

file(GLOB GAME_SRC
    "${PH_SOURCE_DIR}/Game/*.h"
    "${PH_SOURCE_DIR}/Game/*.cpp"
)
source_group("Source\\Game" FILES ${GAME_SRC})

file(GLOB PHYSICS_SRC
    "${PH_SOURCE_DIR}/Physics/*.h"
    "${PH_SOURCE_DIR}/Physics/*.cpp"
)
source_group("Source\\Physics" FILES ${PHYSICS_SRC})

file(GLOB RENDERING_SRC
    "${PH_SOURCE_DIR}/Rendering/*.h"
    "${PH_SOURCE_DIR}/Rendering/*.cpp"
)
source_group("Source\\Rendering" FILES ${RENDERING_SRC})

file(GLOB UTILITY_SRC
	"${PH_SOURCE_DIR}/Utility/*.h"
	"${PH_SOURCE_DIR}/Utility/*.cpp"
)
source_group("Source\\Utility" FILES ${UTILITY_SRC})

# Define sources and executable
set(ENGINE_NAME "PhoenixEngine")
add_library(${ENGINE_NAME} ${AUDIO_SRC} ${CORE_SRC} ${GAME_SRC} ${PHYSICS_SRC} ${RENDERING_SRC} ${UTILITY_SRC})


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/Modules" ${CMAKE_MODULE_PATH})

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
  target_link_libraries(${ENGINE_NAME} ${OPENGL_LIBRARIES})
  # or: target_link_libraries(${ENGINE_NAME} ${OPENGL_gl_LIBRARY})
  #target_link_libraries(${ENGINE_NAME} m)  # if you use maths.h
endif()

include_directories(${PH_EXTINC_DIR})
set(GLEW_INCLUDE_DIR "${PH_EXTINC_DIR}/GLEW")
  file(GLOB GLEW_LIBRARIES
	"${PH_EXTLIB_DIR}/${CMAKE_BUILD_TYPE}/GLEW/*.lib"
  )
  target_link_libraries(${ENGINE_NAME} ${GLEW_LIBRARIES})
  message ("${GLEW_LIBRARIES}")
  
# Install target
install(TARGETS ${ENGINE_NAME} DESTINATION bin)

# TEST GAME MAKEFILE #
file(GLOB TESTGAME_SRC
    "Solution/TestGame/*.h"
    "Solution/TestGame/*.cpp"
)
source_group("Source" FILES ${TESTGAME_SRC})

add_executable(TestGame ${TESTGAME_SRC})

target_link_libraries(TestGame ${ENGINE_NAME})
# CPack packaging
include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${PH_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PH_VERSION_MINOR}")
include(CPack)