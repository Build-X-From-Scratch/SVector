
<p align="center">
  <img src="docs/banner2.png" width="100%">
</p>

# INTRODUCTION

Stree is personal project to develop Vector from sratch with purpose learn memory management,continus allocation and low level,this project have unique challenge because allocation used is continus allocation which have change memory fragmentation occurs.


# Requirements

- compiler: c++17,c++20,c++23(Recomendded)

- Operation system: Windows,Linux(Recomendded),MacOS

- Cmake for using with fetch content


# Instalation

## Use Cmake

If your project uses CMake, you can integrate this library using `FetchContent`. Add the following code to your `CMakeLists.txt`:

```cmake
include(FetchContent)

FetchContent_Declare(
  forward_lists
  GIT_REPOSITORY https://github.com/Build-X-From-Scratch/forward_list_sratch.git
  GIT_TAG v1.0.0
)

FetchContent_MakeAvailable(forward_lists)
```

Then link the library to your executable:
```cmake
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE forward_list)
```