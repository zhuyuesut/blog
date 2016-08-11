---

layout: post
title: "在《Ｃ＋＋ primer 5th》中文版 中发现的笔误汇总"
author: Zhu Yue

---


12.2.1节(425页)： 

 * 原文：up.release(); // 自动用delete[]销毁其指针
 * 纠正：up.reset(); // 自动用delete[]销毁其指针
 * 理由：
   * 参见表12.4(418页)
   * `u.release()`的操作内容是***u放弃对指针的控制权，返回指针，并将u置为空***
   * `u.reset()`的操作内容是***释放u指向的对象***

14.7节(505页)： 

 * 原文：point.operator()->mem;       // point 是类的一个对象
 * 纠正：point.operator->()->mem;     // point 是类的一个对象
 * 理由：
   * 参见14.7节(505页）
   * `->`执行过程中***如果point是定义了operator->的类的一个对象，则我们使用point.operator->()的结果来获取mem***

目前更新到15.2节（532页），笔者目前还在仔细阅读中
