# Create the executable and link the library
add_executable(myAdapter main.cpp)

# AirSim dependencies
set(AIRSIM_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../AirSim)
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

target_include_directories(myAdapter PUBLIC
# AirSim dependencies
    ${AIRSIM_INCLUDE_DIR}
    ${AIRSIM_INCLUDE_COMMON}
    ${RPCLIB_INCLUDE_DIR}
    ${EIGEN_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Link the bulletAdapter library
target_link_libraries(myAdapter PUBLIC 
bulletAdapter
${MAVLINKCOM_LIB_DIR}/libMavLinkCom.a
${RPCLIB_LIB_DIR}/librpc.a
${AIRSIM_LIB_DIR}/libAirLib.a
)
