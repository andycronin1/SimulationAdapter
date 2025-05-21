
cmake_minimum_required(VERSION 3.5)

project(cmakeAdapter VERSION 0.1.0 LANGUAGES C CXX)
find_package(Bullet REQUIRED)

add_subdirectory(src)
add_subdirectory(app)


