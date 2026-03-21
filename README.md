# C++ 数据结构与算法代码库

本项目是我个人用于学习和手写数据结构与算法的 C++ 代码仓库。
整个项目采用 CMake 构建系统，实现了源码与编译产物的分离，支持跨平台编译（目前仅支持跨自己的两台设备emmm）。

## 快速开始 (Windows + Visual Studio)

1. **生成工程**：双击运行项目根目录下的 `build_project.bat`，脚本将自动在 `build/` 目录下生成 Visual Studio 解决方案。
2. **打开项目**：双击运行 `open_in_vs.bat`，拉起 Visual Studio。
3. **编译调试**：在“解决方案资源管理器”中，右键需要运行的算法（如 `01_Array`），选择**“设为启动项目”**，直接点击运行 (F5) 即可。

*注：编译好的 `.exe` 可执行文件会自动输出到根目录的 `bin/<配置>-<架构>/` 文件夹中（如 `bin/Debug-x64/`）。*

## 目录结构

```text
数据结构与算法
 ├─ src/                # 核心源码目录：所有数据结构和算法工具的实现
 ├─ build/              # CMake 自动生成的构建目录
 ├─ bin/                # 可执行文件编译输出目录
 ├─ CMakeLists.txt      # CMake 工程配置文件
 ├─ build_project.bat   # Windows 工程生成脚本
 ├─ open_in_vs.bat      # 快捷打开 VS 的脚本
 └─ .gitignore          # Git 忽略规则文件
```

## 已实现清单

代码按编号分类存放在 `src/` 目录下，各数据结构均包含核心的增删改查实现：

### 线性表
| 项目目录 | 数据结构/算法实现 |
| :--- | :--- |
| `01_Array` | 动态数组 |
| `02_LinkedList` | 单链表 |
| `03_SinglyCircularLinkedList` | 单向循环链表 |
| `04_DoublyLinkedList` | 双向链表 |
| `05_DoublyCircularLinkedList` | 双向循环链表 |

### 栈与队列
| 项目目录 | 数据结构/算法实现 |
| :--- | :--- |
| `06_Stack` | 顺序栈 (数组实现) |
| `07_LinkedListStack` | 链式栈 (链表实现) |
| `08_CircularQueue` | 环形队列 (数组实现) |
| `09_LinkedListQueue` | 链式队列 (链表实现) |

### 查找与排序算法
| 项目目录 | 数据结构/算法实现 |
| :--- | :--- |
| `10_BinarySearch` | 二分查找 |
| `11_BasicSort` | 基础排序 (冒泡、选择、插入) |
| `12_QuickSort` | 快速排序 |
| `13_MergeSort` | 归并排序 |
| `15_HeapSort` | 堆排序 |
| `17_RadixSort` | 基数排序 |

### 树形结构
| 项目目录 | 数据结构/算法实现 |
| :--- | :--- |
| `14_BinaryHeap` | 二叉堆 (数组实现) |
| `33_BST` | 二叉搜索树 |
| `38_AVLTree` | AVL 平衡二叉树 |

### 哈希表
| 项目目录 | 数据结构/算法实现 |
| :--- | :--- |
| `18_LinearProbingHashTable` | 哈希表 (开放寻址法) |
| `19_ChainingHashTable` | 哈希表 (拉链法) |
