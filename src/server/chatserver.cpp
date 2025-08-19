#include "chatserver.hpp"
#include "json.hpp"
#include "chatservice.hpp"

#include <string>
#include <functional>
using namespace std;
using json = nlohmann::json;
using namespace placeholders;

ChatServer::ChatServer(EventLoop *loop,
                        const InetAddress &listenAddr,
                        const string &nameArg)
    :  _server(loop, listenAddr, nameArg), _loop(loop)
    {
        //注册连接回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

        //注册消息回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        //设置线程数量
        _server.setThreadNum(4);
    }

//启动服务
void ChatServer::start(){
    _server.start();
}

//专门处理用户的连接创建和断开 epoll listenfd accept
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    //用户端断开连接断开
    if(!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}

//专门处理用户的读写事件
void ChatServer::onMessage(const TcpConnectionPtr &conn,
                        Buffer *buffer,
                        Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    // 数据的反序列化
    json js = json::parse(buf);
    //目的：完全解耦网络模块的代码和业务模块的代码
    //通过js["msgid"] 获取=》业务hander conn js time
    auto msgHandler = ChatService::instance()->getHander(js["msgid"].get<int>());
    msgHandler(conn, js, time);
}



