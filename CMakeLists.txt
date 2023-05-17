# 定义cmake的最低版本
cmake_minimum_required(VERSION 3.0)

# 定义项目名
project("MyLibrary")

# 调用子目录下的CMakeLists.txt
add_subdirectory(threadpool)