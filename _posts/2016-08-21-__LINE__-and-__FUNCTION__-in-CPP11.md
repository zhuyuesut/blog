---

layout: post
title: "宏LOG编写练习与宏__LINE__和__func__使用随笔"
author: Zhu Yue

---

很久以前就写过 `LOG` 宏用来调试，虽然 *Xcode* 用来调试足够用了，
而且标准库中还有 `assert` 宏作为辅助。

其实实现 `LOG` 宏的过程往往最后变成了练习。

从开始时只使用最普通的 **宏 (`Macros`)** 来实现，
再之后分别使用了 **可变参宏（`Variadic Macros`）** 、
**初始化列表 (`initializer_list`)** 、 
**重载 `()` 运算符的对象 (`a kind of Function Object`)** 、
**可变参数模版 (`Variadic Macros`)** 。

在这次 `LOG` 宏的定义中出现了两点要说一下：

* `__FILE__` 宏是一个 `const char *` 类型，而 `__LINE__` 是常数类型
* `__func__` 和 `__FUNCTION__` 不是 `const char *` 类型，而是 `const char []`

下面是例子，其中 `log` 是一个函数对象。

```cpp
#define LOG(...) do {\
        log(__FILE__ ":" STR(__LINE__);\
        log(__VA_ARGS__);\
    } while (false)
#define STR(x) _VAR(x)
#define _VAR(x) #x
``` 

能看出两点：

1. 例子中没有使用 `#__LINE__` 而是使用 `STR(__LINE__)` ，因为 `#` 的作用只限于宏参数
2. 例子中没有使用 `#define STR(x) #x` 而是使用 `#define STR(x) _VAR(x)` 和 `#define _VAR(x) #x` ，
这是因为宏参数 `x` 是一个宏，需要等待宏 `x` 的解析结束后方可在两端添加 `"` ，也就是说宏的解析是并行的。

如果直接使用 `log(__FILE__ ":" __FUNCTION__ ":" STR(__LINE__);` 会产生编译错误，
原因如下：

* 不妨设语句最终位置在 `main` 函数中，那么 `__FUNCTION__` 的值为 `"main"` ，
而它的类型将会是 `const char [sizeof("main")]` ，也就是 `const char [5]` 。
所以挨着的字符串常量可以自动连接的这种语法就不再适用了。 `__func__` 和 `__FUNCTION__` 一样。

最后 `LOG` 宏定义代码如下：

```cpp
#define LOG(...) do {\
        log(std::string("Log: " "(" #__VA_ARGS__ "), function ")\
                .append(__FUNCTION__)\
                .append(", file " __FILE__ ", line " STR(__LINE__) ", value(s) "),\
            __VA_ARGS__);\
    } while (false)
#define STR(x) _VAR(x)
#define _VAR(x) #x
```

测试输出格式样例如下：

```
Log: (a, b, c, d, e), function main, file /Users/zhuyue/CppClassLog/main.cpp, line 26, value(s) 	2	3.1	$	true	string.
```

