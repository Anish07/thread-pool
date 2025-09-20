
project(thread_pool LANGUAGES CXX)
add_library(thread_pool INTERFACE)
target_include_directories(thread_pool INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(thread_pool_example examples/basic.cpp)
target_link_libraries(thread_pool_example PRIVATE thread_pool)
