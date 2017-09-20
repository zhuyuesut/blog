---
layout: post
title:  "终端显示hostname的位置显示为字符串bogon"
author: Zhu Yue
categories: other
---
如图所示，打开终端突然发现有些不对，应该显示hostname的位置显示的却是字符串“bogon”，Google一下才知道出问题的并不是我一个。

![image](/assets/img/bogon-in-iterm.jpg)

原因是由于DNS错误地将保留地址反向的NS查询结果（“bogon”）返回了。其中bogon本应该指虚假的IP地址，而非保留IP地址（参考自[Mac 终端里神秘的 bogon 及解决方法](https://air20.com/archives/486.html))。
