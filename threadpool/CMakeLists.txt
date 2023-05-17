# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 指定头文件路径，PROJECT_SOURCE_DIR: 当前项目的根目录
include_directories(${PROJECT_SOURCE_DIR}/common)

# 生成可执行文件
add_executable(threadpool test.cpp)

# 添加外部链接库
link_directories(${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(threadpool pthread)