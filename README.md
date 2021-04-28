# 四则运算生成器 Qt

软件工程作业，四则运算生成器。

# Usage

首先确保安装Qt相关组件和CMake。

## Linux/Unix

```
$ git clone https://github.com/se-hwk-group/ArthemeticQt.git
$ cd ArthmeticQt
$ mkdir build && cd build
$ cmake .. && make -j8
$ ./Arthmetic
```

## Windows

使用M$VC编译会因为文件编码为UTF-8 (NO BOM)而遇到`常量中存在换行符`无法编译的问题。

解决方法是手动将文件编码转为UTF-8 (With BOM)或GBK(不推荐)，或者使用Clang/MinGW编译器编译。

因文件编码为UTF-8，M$中使用GBK的用户会遇到输出的log的中文是乱码的情况。
