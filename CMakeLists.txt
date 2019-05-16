
cmake_minimum_required(VERSION 3.10)

project(hello-cmake)

#set(CMAKE_CXX_STANDARD 11)

include(utils-fs.cmake)

macro(ADD_EXE_BY_DIR curdir pre)
    message('---ADD_EXE_BY_DIR begin:')
    scandir_r(SUBDIRS ${curdir})
    foreach(subdir ${SUBDIRS})
        set(hfiles "")
        set(cfiles "")
        file(GLOB hfiles ${curdir}/${subdir}/*.h)
        file(GLOB cfiles ${curdir}/${subdir}/*.c)
        string(LENGTH "${cfiles}" cfiles_len)
        if (cfiles_len GREATER 2)
            get_filename_component(dirname1 ${curdir}/${subdir} NAME)
            message('subdir:' ${subdir} ' - dirname1:' ${dirname1})
            set(programe_name ${pre}_${dirname1})
            add_executable(${programe_name}
                    ${hfiles}
                    ${cfiles}
                    )
            message('---ADD_EXE_BY_DIR :' ${programe_name})
            string(REGEX MATCH "^.*\\.[^.]*$" temp1 ${subdir}) # 第几个括号（序号）是 ${CMAKE_MATCH_n} 中的n
        endif ()
        #    ADD_SUBDIRECTORY(${subdir})
    endforeach()
    message('---ADD_EXE_BY_DIR end.')
endmacro()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/apue.2e/include)
ADD_EXE_BY_DIR(${CMAKE_CURRENT_SOURCE_DIR}/apue.2e apue2)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/apue.3e/include)
ADD_EXE_BY_DIR(${CMAKE_CURRENT_SOURCE_DIR}/apue.3e apue3)

