<p align="center">
  <img src="docs/banner2.png" width="100%">
</p>

# INTRODUCTION

Stree is personal project to develop Vector from sratch with purpose learn memory management,continus allocation and low level,this project have unique challenge because allocation used is continus allocation which have change memory fragmentation occurs.

> [!note]
> this project on going develoment

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
  vector
  GIT_REPOSITORY https://github.com/Build-X-From-Scratch/SVector.git
)

FetchContent_MakeAvailable(vector)
```

Then link the library to your executable:
```cmake
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE forward_list)
```


# How To Use?

after setup instalation,you can include header example:

```cpp
#include <Vector>
```

if done,you ready to use this library,this example use method that exist an library

```cpp
#include <iostream>
#include <vector>
#include "../header/vector.hpp"
using namespace mystl;
int main(){
    Vector<int>v = {100,200,300};
    std::cout << "print use built in function" << std::endl;
   // v.print();
    for(int i = 0;i < v.get_size();i++){
        std::cout << v[i] << " ";
    }  
    mystl::Vector<int>a = {500,600,700};
    a.erase(a.begin() + 0);
    a.print();
    return 0;
}
```

# Issue

if you encounter any issue ,please open an issue and submit a pull request.

# Develoment

[![wakatime](https://wakatime.com/badge/user/04a3154f-bfdc-49e5-b523-80e1a082da81/project/b5c663e4-c9b1-4566-94e6-4e4766d94d60.svg)](https://wakatime.com/badge/user/04a3154f-bfdc-49e5-b523-80e1a082da81/project/b5c663e4-c9b1-4566-94e6-4e4766d94d60)

# License

this project is licensed under [MIT](https://github.com/Build-X-From-Scratch/SVector/blob/main/LICENSE)

You are free to use, modify, and distribute it with proper attribution.


