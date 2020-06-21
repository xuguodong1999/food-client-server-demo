cmake_minimum_required(VERSION 3.15)
project(FoodServer)
set(CMAKE_CXX_STANDARD 11)

if (MSVC)
    # windows下修改到本地 Qt 库的cmake文件夹位置
    set(Qt5_DIR "C:/Qt/5.14.2/msvc2017_64/lib/cmake/Qt5")
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
else ()
    # linux下修改到本地 Qt 库的cmake文件夹位置
    set(Qt5_DIR "/home/xgd/Qt/5.15.0/gcc_64/lib/cmake/Qt5")
endif ()

find_package(Qt5 COMPONENTS Core Network Sql REQUIRED)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

aux_source_directory(. DIR_SRCS)
add_executable(${PROJECT_NAME} ${DIR_SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Sql Qt5::Network)