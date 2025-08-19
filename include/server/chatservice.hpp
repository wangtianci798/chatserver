#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <mutex>
#include <memory>
#include "json.hpp"
using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

#include "redis.hpp"
#include "friendmodel.hpp"
#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "groupmodel.hpp"

//表示处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn,json &js, Timestamp)>;

//聊天服务器业务类
class ChatService
{
public:
    static ChatService* instance();
    //处理登录业务
    void login(const TcpConnectionPtr &conn,json &js, Timestamp time);
    //处理注册业务
    void reg(const TcpConnectionPtr &conn,json &js, Timestamp time);
    //一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn,json &js, Timestamp time);
    //获取消息对应的处理器
    MsgHandler getHander(int msgid);
    //处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);
    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn,json &js, Timestamp time);
    // 加入群组业务
    void addGroup(const TcpConnectionPtr &conn,json &js, Timestamp time);
    // 群组聊天业务
    void groupChat(const TcpConnectionPtr &conn,json &js, Timestamp time);
    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn,json &js, Timestamp time);
    // 添加好友业务
    void addFriend(const TcpConnectionPtr &conn,json &js, Timestamp time);
    // 从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int userid, string msg);
    // 服务器异常，业务重置方法
    void reset();
private:
    ChatService();
    //存储消息id和其对应的业务处理方法
    unordered_map<int, MsgHandler> _handlerMap;

    //存储在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    //数据操作类对象
    UserModel _userModel;
    OfflineMsgeModel _offlineMsgeModel;
    FriendModel _friendModel;
    GroupModel _groupModel;

    //定义互斥锁，保证_线程安全
    mutex _connMutex;

    // redis操作对象
    Redis _redis;
};

#endif