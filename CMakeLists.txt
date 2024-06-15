cmake_minimum_required(VERSION 3.26)

project(sfSnake)

# 添加执行文件
add_executable(sfSnake 
    main.cpp 
    Game.cpp 
    MenuScreen.cpp 
    GameScreen.cpp 
    Fruit.cpp 
    GameOverScreen.cpp 
    Screen.cpp 
    Snake.cpp 
    SnakeNode.cpp
)

# 添加头文件目录
# 获取环境变量 SFML_ROOT
set(SFML_ROOT $ENV{SFML_ROOT})


# 设置 SFML_DIR，指向 SFML 的 CMake 文件目录
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")

# 包含 SFML 头文件
target_include_directories(sfSnake PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    "${SFML_ROOT}/include"
)

# 查找 SFML 包
find_package(SFML 2.6 REQUIRED COMPONENTS system window graphics network audio)

# 设置 SFML 相关的变量
# 需要根据电脑上的SFML位置进行修改
set(SFML_ROOT "C:/SFML-2.6.1")
set(SFML_BIN_DIR "${SFML_ROOT}/bin")

# 将 SFML DLL 目录添加到系统 PATH 中
set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
list(APPEND CMAKE_PREFIX_PATH "${SFML_BIN_DIR}")
include(InstallRequiredSystemLibraries)


# 将 SFML 库链接到你的项目
target_link_libraries(sfSnake PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)
# 将可执行文件复制到输出目录
install(TARGETS sfSnake DESTINATION .)