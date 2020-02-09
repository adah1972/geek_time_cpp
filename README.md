# 现代 C++ 实战 30 讲示例代码

这里存放的是[现代 C++ 实战 30 讲](https://time.geekbang.org/column/256)的示例代码。构建代码需要 CMake 和下列编译器之一：

- MSVC（Visual Studio）2019 16.4.4 或更新版本
- GCC 7 或更新版本
- Clang 7 或更新版本

我假设 Windows 用户使用 MSVC 和 vcpkg，Linux 用户使用 GCC 和发布版的包管理器，macOS 用户使用 Clang 和 Homebrew。其他组合我不测试，也不知道是否可用。

基本构建过程：

```bash
mkdir build
cd build
cmake ..
cmake --build . -j
```
