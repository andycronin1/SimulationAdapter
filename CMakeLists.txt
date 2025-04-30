cmake_minimum_required(VERSION 3.5)

project(cmakeAdapter VERSION 0.1.0 LANGUAGES C CXX)

find_package(Bullet REQUIRED)

# AirSim dependencies
set(AIRSIM_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/AirSim)
set(RPCLIB_INCLUDE_DIR ${AIRSIM_ROOT}/AirLib/deps/rpclib/include)
set(EIGEN_INCLUDE_DIR ${AIRSIM_ROOT}/AirLib/deps/eigen3)
set(AIRSIM_INCLUDE_DIR ${AIRSIM_ROOT}/AirLib/include)
set(MAVLINKCOM_LIB_DIR ${AIRSIM_ROOT}/AirLib/deps/MavLinkCom/lib/) # Adjusted for macOS
set(RPCLIB_LIB_DIR ${AIRSIM_ROOT}/AirLib/deps/rpclib/lib)        # Adjusted for macOS
set(AIRSIM_LIB_DIR ${AIRSIM_ROOT}/AirLib/lib)             # Adjusted for macOS

# Debugging messages
message(STATUS "BULLET_FOUND: ${BULLET_FOUND}")
message(STATUS "BULLET_INCLUDE_DIRS: ${BULLET_INCLUDE_DIRS}")
message(STATUS "BULLET_LIBRARIES: ${BULLET_LIBRARIES}")
message(STATUS "AIRSIM_ROOT: ${AIRSIM_ROOT}")
message(STATUS "RPCLIB_INCLUDE_DIR: ${RPCLIB_INCLUDE_DIR}")
message(STATUS "EIGEN_INCLUDE_DIR: ${EIGEN_INCLUDE_DIR}")
message(STATUS "AIRSIM_INCLUDE_DIR: ${AIRSIM_INCLUDE_DIR}")
message(STATUS "MAVLINKCOM_LIB_DIR: ${MAVLINKCOM_LIB_DIR}")
message(STATUS "RPCLIB_LIB_DIR: ${RPCLIB_LIB_DIR}")
message(STATUS "AIRSIM_LIB_DIR: ${AIRSIM_LIB_DIR}")

# Check if directories exist
if(EXISTS ${MAVLINKCOM_LIB_DIR})
    message(STATUS "MAVLINKCOM_LIB_DIR exists: ${MAVLINKCOM_LIB_DIR}")
else()
    message(WARNING "MAVLINKCOM_LIB_DIR does not exist: ${MAVLINKCOM_LIB_DIR}")
endif()

if(EXISTS ${RPCLIB_LIB_DIR})
    message(STATUS "RPCLIB_LIB_DIR exists: ${RPCLIB_LIB_DIR}")
else()
    message(WARNING "RPCLIB_LIB_DIR does not exist: ${RPCLIB_LIB_DIR}")
endif()

if(EXISTS ${AIRSIM_LIB_DIR})
    message(STATUS "AIRSIM_LIB_DIR exists: ${AIRSIM_LIB_DIR}")
else()
    message(WARNING "AIRSIM_LIB_DIR does not exist: ${AIRSIM_LIB_DIR}")
endif()

# Check if specific files exist
if(EXISTS ${MAVLINKCOM_LIB_DIR}/libMavLinkCom.a)
    message(STATUS "Found libMavLinkCom.a in ${MAVLINKCOM_LIB_DIR}")
else()
    message(WARNING "libMavLinkCom.a not found in ${MAVLINKCOM_LIB_DIR}")
endif()

if(EXISTS ${RPCLIB_LIB_DIR}/librpc.a)
    message(STATUS "Found librpc.a in ${RPCLIB_LIB_DIR}")
else()
    message(WARNING "librpc.a not found in ${RPCLIB_LIB_DIR}")
endif()

if(EXISTS ${AIRSIM_LIB_DIR}/libAirLib.a)
    message(STATUS "Found libAirLib.a in ${AIRSIM_LIB_DIR}")
else()
    message(WARNING "libAirLib.a not found in ${AIRSIM_LIB_DIR}")
endif()

add_executable(myAdapter main.cpp bulletAdapter.cpp)

# Include directories
target_include_directories(myAdapter PRIVATE
    ${BULLET_INCLUDE_DIRS}
    ${RPCLIB_INCLUDE_DIR}
    ${EIGEN_INCLUDE_DIR}
    ${AIRSIM_INCLUDE_DIR}
)

# Link libraries
if(APPLE)
    target_link_libraries(myAdapter PRIVATE
        ${BULLET_LIBRARIES}
        ${MAVLINKCOM_LIB_DIR}/libMavLinkCom.a
        ${RPCLIB_LIB_DIR}/librpc.a
        ${AIRSIM_LIB_DIR}/libAirLib.a
    )
endif()