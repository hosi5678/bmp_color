# cmakeのversion 指定
cmake_minimum_required(VERSION 3.5)

# project名の設定
project(sub_dir)

# compilerの指定
set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")

# source filesの検索
file(GLOB_RECURSE SOURCES "./src/*.cpp")

# target名を決定し、source filesをtargetに付加(.c or .cpp)
add_library(sub_dir STATIC ${SOURCES})

# include files(header files)をtargetに付加
target_include_directories(sub_dir INTERFACE ./include)

# math.hをtargetに付加
target_link_libraries(sub_dir m)

# glfw_sub_dir
# target_link_libraries(sub_dir GL)
# target_link_libraries(sub_dir GLU)
# target_link_libraries(sub_dir glut)
# target_link_libraries(sub_dir glfw)
# target_link_libraries(sub_dir glfw3)
# target_link_libraries(sub_dir GLEW)
# target_link_libraries(sub_dir Xrandr)
# target_link_libraries(sub_dir Xinerama)
# target_link_libraries(sub_dir Xi)
# target_link_libraries(sub_dir Xxf86vm)
# target_link_libraries(sub_dir X11)
# target_link_libraries(sub_dir rt)
# target_link_libraries(sub_dir dl)
# target_link_libraries(sub_dir Xext)
# target_link_libraries(sub_dir Xcursor)
