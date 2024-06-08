# cmake_minimum_required(VERSION 3.10)

# project(os)

# set(CMAKE_CXX_STANDARD 17)

# set(SOURCES
#     4_1fs.cpp
#     4_1fs_main.cpp
#     # 4_1fs_ui.cpp
# )

# add_executable(4_1fs ${SOURCES})

# 最低要求的CMake版本
cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(fs VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加可执行文件，并指定其源文件
add_executable(fs
    fs.cpp
    fs_main.cpp
)

# 指定目标的子系统为控制台
if (MINGW OR MSYS)
    set_target_properties(fs PROPERTIES 
        LINK_FLAGS "-static-libgcc -static-libstdc++")
endif()