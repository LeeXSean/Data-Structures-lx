@echo off
chcp 65001 >nul
echo 正在尝试打开 Visual Studio 解决方案...

:: 优先寻找 VS2026/较新版本的 .slnx 文件
if exist build\DataStructuresAlgorithms.slnx (
    echo [发现 .slnx 解决方案，正在启动...]
    start build\DataStructuresAlgorithms.slnx
    exit /b 0
)

:: 兼容寻找 VS2022 及之前传统版本的 .sln 文件
if exist build\DataStructuresAlgorithms.sln (
    echo [发现 .sln 解决方案，正在启动...]
    start build\DataStructuresAlgorithms.sln
    exit /b 0
)

echo [错误] 找不到任何解决方案文件！请先双击运行 build_project.bat 进行生成。
pause