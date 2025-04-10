# 现代 C++ 编程实战示例代码

这里存放的是[现代 C++ 编程实战](https://time.geekbang.org/column/256)的示例代码。构建代码需要 CMake 和下列编译器之一：

- MSVC（Visual Studio）2019 16.4.4 或更新版本
- GCC 7 或更新版本
- Clang 7 或更新版本

我假设 Windows 用户使用 MSVC 和 vcpkg，Linux 用户使用 GCC 和发布版的包管理器，macOS 用户使用 Clang 和 Homebrew。其他组合我不测试，也不知道是否可用。

基本构建过程：

```bash
git clone https://github.com/adah1972/geek_time_cpp.git
cd geek_time_cpp
git submodule init
git submodule update
mkdir build
cd build
cmake ..
cmake --build . -j
```

最后四步（从 `mkdir build` 到 `cmake --build …`）也可以进入到子目录下进行，只构建那一部分的代码。在使用 Unix Makefiles（Unix/Linux 下的默认情况）作为 CMake 的实际构建系统（生成器）时，应当在 `-j` 后面加上并发任务的允许数量（否则 GNU Make 不会对并发任务数进行限制）。

在使用 MSVC 时，可以在最后一步时指定构建的类型：Debug、Release、MinSizeRel 或 RelWithDebInfo。比如，下面的命令可指定构建 Release 版本（默认为 Debug）：

```bash
cmake --build . -j --config Release
```

在使用 Unix Makefiles（一般使用 GCC 或 Clang 的情况）时，只能在创建工程文件时指定构建类型（默认跟一般的命令行一样，非调试、非优化）。比如，下面的命令可指定构建 Debug 版本（我们在 21 讲和 26 讲有例子需要调试符号）：

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . -j8
```
