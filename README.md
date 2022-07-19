# TinyHttpServer

http_server_onethread文件夹内包含了windows下，单线程的简易http服务器实现。

开发环境：win10+vs2019

TinyHttpServer文件夹：
设计主从状态机完成HTTP请求的读取和分析；使用非阻塞IO+epoll(ET模式)实现最优的高并发处理请求，减少$epoll\_wait$系统调用次数；注册EPOLLONESHOT事件,保证一个socket在任意时刻都只被一个线程进行处理；使用线程池提高并发，降低频繁创建线程的开销；使用shared\_ptr管理指针，防止内存泄漏。

开发环境：ubuntu16.04+vscode
