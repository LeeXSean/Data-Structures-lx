<div align="center">

# C++ 数据结构与算法

基于 CMake 构建 · 源码与编译产物分离 · Visual Studio 开发

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
  - [串](#串)

---

## 快速开始

> **环境要求**：Windows + Visual Studio (2019 / 2022 / 2026) + CMake 3.10+

**1. 生成工程**

双击 `build_project.bat`，脚本会按 VS2026 → VS2022 → VS2019 的顺序检测可用的 Visual Studio C++ 生成器，并在 `build/` 下生成对应的解决方案。

> 脚本使用 `--fresh` 刷新 CMake 缓存。项目目录移动、改名，或从其他 VS 版本切换过来时，**无需**手动删除 `build/` 目录。

**2. 打开项目**

双击 `open_in_vs.bat` 拉起 Visual Studio。脚本会优先打开 VS2026+ 生成的 `.slnx`，找不到时再回退到传统 `.sln`。

**3. 编译调试**

在解决方案资源管理器中，右键目标项目（如 `01_Array`）→ **设为启动项目** → 按 **F5** 运行。

> 每个 `src/` 子目录都会被 CMake 编译成一个独立的可执行目标，编译产物输出到 `bin/<配置>-<架构>/`（如 `bin/Debug-x64/`）。

---

## 目录结构

```
.
├── src/                   # 源码：每个子目录 = 一个独立可执行目标
│   ├── 01_Array/
│   ├── 02_LinkedList/
│   ├── ...
│   └── 47_String/
├── build/                 # CMake 生成的工程文件（自动生成，已 .gitignore）
├── bin/                   # 编译输出目录：bin/<配置>-<架构>/
├── CMakeLists.txt         # 自动扫描 src/ 下子目录并生成目标
├── build_project.bat      # 工程生成脚本（检测 VS 版本 + 刷新 CMake 缓存）
├── open_in_vs.bat         # 一键打开 VS 解决方案（.slnx 优先）
└── .gitignore
```

---

## 已实现清单

所有实现均位于 `src/` 下，按编号分目录存放，包含核心的增删改查操作。

> 复杂度记号：**n** = 元素个数，**m** = 模式串长度，**k** = 基数 / 桶数，**d** = 关键字最大位数。

### 线性表

| 结构 | 目录 | 随机访问 | 插入 / 删除 | 查找 |
| :--- | :--- | :---: | :---: | :---: |
| 动态数组 | `01_Array` | O(1) | O(n) | O(n) |
| 单链表 | `02_LinkedList` | O(n) | O(1) <sup>†</sup> | O(n) |
| 单向循环链表 | `03_SinglyCircularLinkedList` | O(n) | O(1) <sup>†</sup> | O(n) |
| 双向链表 | `04_DoublyLinkedList` | O(n) | O(1) <sup>†</sup> | O(n) |
| 双向循环链表 | `05_DoublyCircularLinkedList` | O(n) | O(1) <sup>†</sup> | O(n) |

<sup>†</sup> 已持有目标节点指针时为 O(1)，否则需先 O(n) 定位。

### 栈与队列

| 结构 | 目录 | 入栈 / 入队 | 出栈 / 出队 | 实现方式 |
| :--- | :--- | :---: | :---: | :--- |
| 顺序栈 | `06_Stack` | O(1) | O(1) | 数组 |
| 链式栈 | `07_LinkedListStack` | O(1) | O(1) | 链表 |
| 环形队列 | `08_CircularQueue` | O(1) | O(1) | 数组 |
| 链式队列 | `09_LinkedListQueue` | O(1) | O(1) | 链表 |

### 查找与排序

| 算法 | 目录 | 平均时间 | 最坏时间 | 空间 | 稳定性 |
| :--- | :--- | :---: | :---: | :---: | :---: |
| 二分查找 | `10_BinarySearch` | O(log n) | O(log n) | O(1) | — |
| 冒泡 / 选择 / 插入排序 | `11_BasicSort` | O(n²) | O(n²) | O(1) | 部分 <sup>‡</sup> |
| 快速排序 | `12_QuickSort` | O(n log n) | O(n²) | O(log n) | 不稳定 |
| 归并排序 | `13_MergeSort` | O(n log n) | O(n log n) | O(n) | 稳定 |
| 堆排序 | `15_HeapSort` | O(n log n) | O(n log n) | O(1) | 不稳定 |
| 基数排序 | `17_RadixSort` | O(d·(n+k)) | O(d·(n+k)) | O(n+k) | 稳定 |

<sup>‡</sup> 冒泡、插入排序稳定，选择排序不稳定。

### 树形结构

| 结构 | 目录 | 插入 | 删除 | 查找 | 备注 |
| :--- | :--- | :---: | :---: | :---: | :--- |
| 二叉堆 | `14_BinaryHeap` | O(log n) | O(log n) | O(1) <sup>※</sup> | 数组实现 |
| 二叉搜索树 | `33_BST` | O(log n) | O(log n) | O(log n) | 平均；退化时 O(n) |
| AVL 树 | `38_AVLTree` | O(log n) | O(log n) | O(log n) | 严格平衡 |
| 红黑树 | `39_RBTree` | O(log n) | O(log n) | O(log n) | 近似平衡，旋转更少 |

<sup>※</sup> 取堆顶 O(1)；树形结构插入 / 删除 / 查找均为平均复杂度。

### 哈希表

| 结构 | 目录 | 查找 / 插入 / 删除（平均） | 冲突处理 |
| :--- | :--- | :---: | :--- |
| 开放寻址哈希表 | `18_LinearProbingHashTable` | O(1) | 线性探测 |
| 拉链哈希表 | `19_ChainingHashTable` | O(1) | 链地址法 |

### 串

| 算法 | 目录 | 时间 | 空间 | 说明 |
| :--- | :--- | :---: | :---: | :--- |
| BF 暴力匹配 | `47_String` | O(n·m) | O(1) | 朴素模式匹配 |
| KMP 匹配 | `47_String` | O(n+m) | O(m) | next 数组优化 |
