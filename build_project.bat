@echo off
chcp 65001 >nul
echo ==================================================
echo         数据结构与算法 - 自动构建脚本
echo ==================================================
echo.

:: 检查 CMake 是否安装并可用
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo [错误] 您的系统未安装 CMake 或未将其添加到环境变量。
    echo.
    echo 解决方法：
    echo 1. 请前往官方网站下载：https://cmake.org/download/
    echo 2. 在安装过程中，请务必勾选 "Add CMake to the system PATH for all users"。
    echo 3. 安装完成后，重启终端或重新打开此脚本。
    echo.
    pause
    exit /b 1
)

echo [进度] CMake 环境检查通过！正在创建构建目录...

:: 创建并进入构建目录
if not exist build (
    mkdir build
)
cd build

echo.
echo [进度] 正在生成项目配置文件...
:: 强制使用 VS2022 构建（因为我两台电脑都装的vs2022，看自己需求可以改成其他版本）
cmake -G "Visual Studio 17 2022" -A x64 ..
if %errorlevel% neq 0 (
    echo.
    echo [错误] CMake 配置文件生成失败，请检查源码或 CMakeLists.txt。
    pause
    exit /b 1
)

echo.
echo ==================================================
echo                构建环境成功
echo       双击 open_in_vs.bat 打开项目开发
echo ==================================================
echo.
pause

