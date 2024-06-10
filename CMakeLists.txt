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
# 添加头文件目录，包括SFML的头文件路径
target_include_directories(sfSnake PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    "C:/SFML-2.6.1/include"
)

# 寻找 SFML 库
set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics audio window system)


# 设置 SFML 相关的变量
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