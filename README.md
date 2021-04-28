# 四则运算生成器 Qt

软件工程作业，四则运算生成器。

# Usage

首先确保安装Qt相关组件和CMake。

Linux/Unix:

```
$ git clone https://github.com/se-hwk-group/ArthemeticQt.git
$ cd ArthmeticQt
$ mkdir build && cd build
$ cmake .. && make -j8
$ ./Arthmetic
```

M$VC用户可能会遇到`常量中存在换行符`的问题，需要手动转换编码格式，因此建议使用GCC(MinGW)编译。
