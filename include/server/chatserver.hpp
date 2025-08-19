#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;


//聊天服务器的主类
class ChatServer
{
public:
    //初始化聊天服务器对象
    ChatServer(EventLoop* loop, //事件循环
            const InetAddress& listenAddr,  //IP+Port
            const string& nameArg);          //服务器的名字

            //启动服务
            void start();
private:
    //专门处理用户的连接创建和断开 epoll listenfd accept
        void onConnection(const TcpConnectionPtr &conn);
    //专门处理用户的读写事件
        void onMessage(const TcpConnectionPtr &conn,
                        Buffer *buffer,
                        Timestamp time);

        TcpServer _server; // 组合的muduo库,实现服务器功能的类对象
        EventLoop *_loop; //指向事件循环的指针
};



#endif