#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>
using namespace std;

// 处理服务器ctrl + c结束后，重置user的状态信息
void reserHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, reserHandler);

    // 默认值
    std::string ip   = "0.0.0.0";  // 0.0.0.0 表示监听本机所有网卡
    uint16_t  port   = 6000;

    // 解析命令行参数
    if (argc > 1) ip   = argv[1];
    if (argc > 2) port = static_cast<uint16_t>(std::stoi(argv[2]));

    EventLoop loop;
    InetAddress addr(ip, port);
    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop();

    return 0;
}