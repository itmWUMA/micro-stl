## 小型STL

#### 1. 简介
实现小型STL：仿照C++标准模板库的结构，自实现小型的STL，以满足STL的基本功能



#### 2. 软件架构

开发环境：Microsoft Visual Studio 2019

程序架构：

> \- alloctor.hpp		// 空间分配器，用以调度内存
>
> \- iterator.hpp		// 迭代器接口，用以定义4种迭代器类型与相关关系
>
> \- vector.hpp
>
> \- list.hpp
>
> \- deque.hpp
>
> \- stack.hpp
>
> \- queue.hpp
>
> \- sortedset.hpp
>
> \- sortedmap.hpp
>
> \- hashset.hpp
>
> \- hashmap.hpp
>
> \- algorithm.hpp	// 算法，用以实现对容器操作的各类算法
>
> \- functor.hpp		// 仿函数，用以实现算法中部分常用的仿函数

注：自实现的所有stl内容均在***mstl_itm***名称空间下



#### 3. 内容介绍

*STL的六大组件均会在本项目中实现，但是部分组件会进行一部分的简化与调整*

- **allocator**

本项目中仅实现了一个简易的空间分配器，底层直接调用new和delete，负责容器中元素的内存分配与释放

- **container**

本项目实现**动态数组、链表、双向数组、栈、队列、有序表、哈希表**的结构定义与相关操作，包括增、删、改、查、插等

- **iterator**

iterator共存在5种类型：**random_acess_iterator  |  bidirectional_iterator  | forward_iterator | input_iterator | output_iterator**，本项目实现前4种

每个容器均存在自身的iterator，供用户访问容器中存放的元素，同时供算法进行调用操作

- **algorithm**

本项目实现基本的**查询、排序**算法

- **functor**

由于C++11后引入lambda表达式，其功能更加灵活方便，故本项目仅实现常用的部分仿函数，如**关系类仿函数、哈希函数**等

- **adaptor**

本项目简化了adaptor的内容，部分适配器功能已融入其它组件中



#### 4. 参与贡献

***itmWuma***

Github：[https://github.com/itmWUMA](https://gitee.com/link?target=https%3A%2F%2Fgithub.com%2FitmWUMA)

Gitee：https://gitee.com/itmwuma

Email：[itmwuma@163.com](mailto:itmwuma@163.com)
