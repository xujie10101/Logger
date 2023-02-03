# 该工具库为[ZLToolKit](https://github.com/ZLMediaKit/ZLToolKit)项目中精减出来的日志、文件等工具库


# 1. 编译Windows
生成工程
```shell
cd Logger
cmake -G "Visual Studio 16 2019" -A x64 -B build -DCMAKE_BUILD_TYPE=Release .
```
打开2019兼容性开发工具  
x64 Native Tools Command Prompt for VS 2019

```shell
#切换到项目目录
cd /d 项目目录
msbuild build/SDK/ALL_BUILD.vcxproj -p:Configuration=Release  #编译SDK库
msbuild build/sample/ALL_BUILD.vcxproj -p:Configuration=Release #编译示例程序
```
生成后的目录结构  
```shell
├─build
│  ├─CMakeFiles
│  │  ├─3.24.2
│  │  │  ├─CompilerIdC
│  │  │  │  ├─Debug
│  │  │  │  │  └─CompilerIdC.tlog
│  │  │  │  └─tmp
│  │  │  ├─CompilerIdCXX
│  │  │  │  ├─Debug
│  │  │  │  │  └─CompilerIdCXX.tlog
│  │  │  │  └─tmp
│  │  │  └─x64
│  │  │      └─Debug
│  │  │          └─VCTargetsPath.tlog
│  │  ├─a1502e5d51ea514c028f72052e68ffa5
│  │  ├─CMakeTmp
│  │  └─pkgRedirects
│  ├─sample
│  │  └─CMakeFiles
│  └─SDK
│      └─CMakeFiles
├─include
├─pic
├─Release     #lib库位置
├─sample
└─SDK
```

## 使用示例

```C++
#include <iostream>
#include <logger.h>

void initLog(){
    toolkit::LogLevel logLevel;
    logLevel = toolkit::LInfo;
    logLevel = MIN(MAX(logLevel,toolkit::LTrace), toolkit::LError);
    toolkit::Logger::Instance().add(std::make_shared<toolkit::ConsoleChannel>("ConsoleChannel", logLevel));
#if !defined(_WIN32)
    pid_t pid = getpid();
        bool kill_parent_if_failed = true;
        if (bDaemon) {

            System::startDaemon(kill_parent_if_failed);
        }

        System::systemSetup();
#endif//!defined(_WIN32)
    toolkit::Logger::Instance().setWriter(std::make_shared<toolkit::AsyncLogWriter>());

#ifdef WIN32
    //设置日志文件保留位置
    auto fileChannel = std::make_shared<toolkit::FileChannel>("FileChannel", "C:/SourthNorth/log/", logLevel);
#else
    auto fileChannel = std::make_shared<FileChannel>("FileChannel", exeDir() + "log/", logLevel);
#endif
    //设置日志文件保留最大天数
    fileChannel->setMaxDay(30);
    toolkit::Logger::Instance().add(fileChannel);
    toolkit::Logger::Instance().setWriter(std::make_shared<toolkit::AsyncLogWriter>());
}

int main(int argc,char* argv[]){

    initLog();
    PrintLog(toolkit::LogLevel::LInfo,"日志系统初始化完成.");
    PrintLog(toolkit::LogLevel::LInfo,"按任意键推出.");
    getchar();
    return 0;
}

```