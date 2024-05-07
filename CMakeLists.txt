cmake_minimum_required(VERSION 3.26)

project(sfSnake)

# 添加执行文件
add_executable(sfSnake main.cpp Game.cpp)

# 添加头文件目录
# 添加头文件目录，包括SFML的头文件路径
target_include_directories(sfSnake PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    "C:/SFML-2.6.1/include"
)

# 寻找 SFML 库
set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML COMPONENTS graphics audio)

link_directories("C:/Users/24398/Desktop/oop/大作业/sfSnake/SFML/extlibs")
# 将 SFML 库链接到你的项目
target_link_libraries(sfSnake PRIVATE sfml-graphics sfml-audio)
