cmake_minimum_required(VERSION 3.0)

project(sfSnake)

# 添加执行文件
add_executable(sfSnake main.cpp Game.cpp)

# 添加头文件目录
target_include_directories(sfSnake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 寻找 SFML 库
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# 将 SFML 库链接到你的项目
target_link_libraries(sfSnake PRIVATE sfml-graphics sfml-audio)