add_executable(grid_traversal test.cc)
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
target_sources(grid_traversal PRIVATE grid.cc  test.cc)
target_include_directories(grid_traversal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
