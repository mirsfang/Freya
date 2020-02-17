#project name
set(PROJECT_NAME freya_win)

set (CORE_VERSION_MAJOR 1)
set (CORE_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 14)
 

get_filename_component(PROJECT_PATH "${CMAKE_CURRENT_LIST_FILE}" PATH)

#add libs
if(WIN32)

elseif(ANDROID)

elseif(IOS)

endif(WIN32)


include_directories(../windows)

#source
file(GLOB_RECURSE PROJECT_HEADERS *.hh *.h *.hpp)
file(GLOB_RECURSE PROJECT_CPPS *.cc *.c *.cpp)
set(ALL_FILES ${PROJECT_HEADERS} ${PROJECT_CPPS})

source_group_by_dir(ALL_FILES)

## 构建库
message("${PROJECT_NAME} ${ALL_FILES}")
add_library(${PROJECT_NAME} ${BUILD_TYPE} ${ALL_FILES})
## 链接头文件
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_PATH} ${RAPIDJSON_INCLUDB_DIR})
## 链接其他库
target_link_libraries( ${PROJECT_NAME} PUBLIC ${EXTEND_OBJS} freya_core)