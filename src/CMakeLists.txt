add_library(bulletAdapter bulletAdapter.cpp)

# Include directories
target_include_directories(bulletAdapter PUBLIC
    ${BULLET_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(bulletAdapter PUBLIC
${BULLET_LIBRARIES}
)