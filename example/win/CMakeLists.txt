set(PROJECT_NAME freya_win_example)

set(CMAKE_CXX_STANDARD 14)

include_directories(../src)

include_directories(../windows)

######################项目源码######################
include_directories(./)
include_directories(${CMAKE_SOURCE_DIR}/libs/win/include)

file(GLOB_RECURSE PROJECT_HEADERS *.hh *.h *.hpp)
file(GLOB_RECURSE PROJECT_CPPS *.cc *.c *.cpp)
set(ALL_FILES ${PROJECT_HEADERS} ${PROJECT_CPPS})

source_group_by_dir(ALL_FILES)

add_executable(WinExample ${ALL_FILES})
target_link_libraries(WinExample freya_core freya_win)

