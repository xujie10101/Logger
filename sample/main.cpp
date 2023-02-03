//
// Created by du-pc on 2023/2/3.
//
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
