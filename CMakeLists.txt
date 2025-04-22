
cmake_minimum_required(VERSION 3.5)

project(cmakeAdapter VERSION 0.1.0 LANGUAGES C CXX)

find_package(Bullet REQUIRED)

message(STATUS "BULLET_FOUND: ${BULLET_FOUND}")
message(STATUS "BULLET_INCLUDE_DIRS: ${BULLET_INCLUDE_DIRS}")
message(STATUS "BULLET_LIBRARIES: ${BULLET_LIBRARIES}")

execute_process(COMMAND ls -l ${BULLET_INCLUDE_DIRS}/LinearMath/btVector3.h OUTPUT_VARIABLE FILE_INFO)
message(STATUS "File Info: ${FILE_INFO}")

add_executable(myAdapter main.cpp adapter.cpp)

# Be explicit about including the LinearMath directory
target_include_directories(myAdapter PRIVATE
    ${BULLET_INCLUDE_DIRS}
)

message(STATUS "BULLET_LIBRARIES: ${BULLET_LIBRARIES}")

target_link_libraries(myAdapter PRIVATE ${BULLET_LIBRARIES})