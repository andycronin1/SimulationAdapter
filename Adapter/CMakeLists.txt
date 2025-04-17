cmake_minimum_required(VERSION 3.5)
project(cmakeAdapter VERSION 0.1.0 LANGUAGES C CXX)

add_executable(cmakeAdapter main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/bullet3/src)
target_link_libraries(cmakeAdapter Bullet3Collision Bullet3Common Bullet3Dynamics Bullet3LinearMath Bullet3Geometry BulletDynamics)

include(CTest)
enable_testing()

