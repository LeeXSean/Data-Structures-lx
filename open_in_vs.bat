@echo off
chcp 65001 >nul
echo ==================================================
echo         数据结构与算法 - 打开 Visual Studio
echo ==================================================
echo.

:: --------------------------------------------------------
:: 优先查找 VS2026+ 的 .slnx，再查找传统 .sln
:: --------------------------------------------------------
if exist build\DataStructuresAlgorithms.slnx (
    echo [√] 发现 .slnx 解决方案（VS2026+），正在启动...
    start "" build\DataStructuresAlgorithms.slnx
    exit /b 0
)

if exist build\DataStructuresAlgorithms.sln (
    echo [√] 发现 .sln 解决方案，正在启动...
    start "" build\DataStructuresAlgorithms.sln
    exit /b 0
)

echo [错误] 找不到解决方案文件，请先双击运行 build_project.bat 生成工程。
pause