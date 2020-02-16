cmake_minimum_required (VERSION 3.8)

project ("Freya")

set(CMAKE_CXX_STANDARD 14)

#option
option(EXAMPLE "build example" ON)


#vs工程添加source filter

macro(source_group_by_dir source_files)
	set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
	foreach(sgbd_file ${${source_files}})
		string(REGEX REPLACE "${sgbd_cur_dir}/(.*)" "\\1" sgbd_fpath ${sgbd_file})
		string(REGEX REPLACE "(.*)/.*" "\\1" sgbd_group_name ${sgbd_fpath})
		string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
		string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
		if(sgbd_nogroup)
			set(sgbd_group_name "\\")
		endif(sgbd_nogroup)
		source_group(${sgbd_group_name} FILES ${sgbd_file})
	endforeach(sgbd_file)
endmacro(source_group_by_dir)

#core
add_subdirectory(src)

#platform
if(WIN32)
    add_subdirectory(windows)
    if(EXAMPLE)
        add_subdirectory(example/win)
    endif(EXAMPLE)
elseif(ANDROID)
    add_subdirectory(android)
    if(EXAMPLE)
        add_subdirectory(example/android)
    endif(EXAMPLE)
elseif(IOS)
    add_subdirectory(ios)
    if(EXAMPLE)
        add_subdirectory(example/ios)
    endif(EXAMPLE)
endif(WIN32)

