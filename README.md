<div align="center">

# C++ 数据结构与算法代码库

个人学习用 C++ 数据结构与算法手写代码仓库

CMake 构建 | 源码与编译产物分离 | Visual Studio 开发

</div>

---

## 目录

- [快速开始](#快速开始)
- [目录结构](#目录结构)
- [已实现清单](#已实现清单)
  - [线性表](#线性表)
  - [栈与队列](#栈与队列)
  - [查找与排序](#查找与排序)
  - [树形结构](#树形结构)
  - [哈希表](#哈希表)

---

## 快速开始

> 环境要求：Windows + Visual Studio + CMake

**1. 生成工程**

双击 `build_project.bat`，自动在 `build/` 下生成 VS 解决方案。

**2. 打开项目**

双击 `open_in_vs.bat`，拉起 Visual Studio。

**3. 编译调试**

在解决方案资源管理器中，右键目标项目（如 `01_Array`）→ **设为启动项目** → 按 **F5** 运行。

> 编译产物输出路径：`bin/<配置>-<架构>/`（如 `bin/Debug-x64/`）

---

## 目录结构

```
.
├── src/                  # 源码目录
├── build/                # 构建目录（自动生成）
├── bin/                  # 编译输出目录
├── CMakeLists.txt        # CMake 配置
├── build_project.bat     # 工程生成脚本
├── open_in_vs.bat        # 快捷打开 VS
└── .gitignore
```

---

## 已实现清单

所有实现均在 `src/` 下按编号分目录存放，包含核心的增删改查操作。

### 线性表

- **`01_Array`** — 动态数组
- **`02_LinkedList`** — 单链表
- **`03_SinglyCircularLinkedList`** — 单向循环链表
- **`04_DoublyLinkedList`** — 双向链表
- **`05_DoublyCircularLinkedList`** — 双向循环链表

### 栈与队列

- **`06_Stack`** — 顺序栈（数组实现）
- **`07_LinkedListStack`** — 链式栈（链表实现）
- **`08_CircularQueue`** — 环形队列（数组实现）
- **`09_LinkedListQueue`** — 链式队列（链表实现）

### 查找与排序

- **`10_BinarySearch`** — 二分查找
- **`11_BasicSort`** — 基础排序（冒泡、选择、插入）
- **`12_QuickSort`** — 快速排序
- **`13_MergeSort`** — 归并排序
- **`15_HeapSort`** — 堆排序
- **`17_RadixSort`** — 基数排序

### 树形结构

- **`14_BinaryHeap`** — 二叉堆（数组实现）
- **`33_BST`** — 二叉搜索树
- **`38_AVLTree`** — AVL 平衡二叉树

### 哈希表

- **`18_LinearProbingHashTable`** — 哈希表（开放寻址法）
- **`19_ChainingHashTable`** — 哈希表（拉链法）
