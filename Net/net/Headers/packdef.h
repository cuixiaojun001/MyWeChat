#pragma once
#include <stdint.h>
#include <cstdio>
#include <memory.h>
#include <string>

#define _DEF_TCP_PORT (8080)
#define _DEF_SERVER_IP ("123.57.187.239")

#define _MAX_SIZE	(40)
#define _DEF_CONTENT_SIZE (1024)

// 协议头
#define _DEF_PROTOCOL_BASE (100)
#define _DEF_PROTOCOL_COUNT (100)

// 注册
#define _DEF_PACK_REGISTER_RQ	(_DEF_PROTOCOL_BASE + 0 )
#define _DEF_PACK_REGISTER_RS	(_DEF_PROTOCOL_BASE + 1 )
//登录
#define _DEF_PACK_LOGIN_RQ	(_DEF_PROTOCOL_BASE + 2 )
#define _DEF_PACK_LOGIN_RS	(_DEF_PROTOCOL_BASE + 3 )
//好友信息
#define _DEF_PACK_FRIEND_INFO	(_DEF_PROTOCOL_BASE + 4 )
//添加好友
#define _DEF_PACK_ADDFRIEND_RQ	(_DEF_PROTOCOL_BASE + 5 )
#define _DEF_PACK_ADDFRIEND_RS	(_DEF_PROTOCOL_BASE + 6 )
//聊天
#define _DEF_PACK_CHAT_RQ	(_DEF_PROTOCOL_BASE + 7 )
#define _DEF_PACK_CHAT_RS	(_DEF_PROTOCOL_BASE + 8 )
//离线
#define _DEF_PACK_OFFLINE_RQ	(_DEF_PROTOCOL_BASE + 9 )
/*文件传输*/
// 文件信息
#define _DEF_PROTOCOL_FILE_INFO_RQ (_DEF_PROTOCOL_BASE + 10)
#define _DEF_PROTOCOL_FILE_INFO_RS (_DEF_PROTOCOL_BASE + 11)
// 文件块
#define _DEF_PROTOCOL_FILE_BLOCK_RQ (_DEF_PROTOCOL_BASE + 12)
#define _DEF_PROTOCOL_FILE_BLOCK_RS (_DEF_PROTOCOL_BASE + 13)
// 最大文件路径长度
#define _MAX_FILE_PATH_SIZE (512)
// 最大文件大小
#define _DEF_FILE_CONTENT_SIZE (8*1024)

//返回的结果
//注册请求的结果
#define user_is_exist		(0)
#define register_success	(1)
//登录请求的结果
#define user_not_exist		(0)
#define password_error		(1)
#define login_success		(2)
#define login_wait          (3)
//添加好友的结果
#define no_this_user		(0)
#define user_refuse			(1)
#define user_offline		(2)
#define add_success			(3)

//协议结构
//注册
typedef struct STRU_REGISTER_RQ
{
    typedef int PackType;
    STRU_REGISTER_RQ() :type(_DEF_PACK_REGISTER_RQ)
    {
        memset(tel, 0, sizeof(tel));
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
    }
    //需要手机号码 , 密码, 昵称
    PackType type;
    char tel[_MAX_SIZE];
    char username[_MAX_SIZE];
    char password[_MAX_SIZE];

}STRU_REGISTER_RQ;

typedef struct STRU_REGISTER_RS
{
    typedef int PackType;
    //回复结果
    STRU_REGISTER_RS() : type(_DEF_PACK_REGISTER_RS), result(register_success)
    {
    }
    PackType type;
    int result;

}STRU_REGISTER_RS;

//登录
typedef struct STRU_LOGIN_RQ
{
    typedef int PackType;
    //登录需要: 手机号 密码
    STRU_LOGIN_RQ() :type(_DEF_PACK_LOGIN_RQ)
    {
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
    }
    /**
     * @brief 数据包类型：_DEF_PACK_LOGIN_RQ
    */
    PackType type;
    /**
     * @brief 用户名
    */
    char username[_MAX_SIZE];
    /**
     * @brief 用户密码
    */
    char password[_MAX_SIZE];

}STRU_LOGIN_RQ;

typedef struct STRU_LOGIN_RS
{
    typedef int PackType;
    // 需要 结果 , 用户的id
    STRU_LOGIN_RS() : type(_DEF_PACK_LOGIN_RS), result(login_success), userid(0)
    {
    }
    PackType type;
    int result;
    int userid;

}STRU_LOGIN_RS;

//好友信息
typedef struct STRU_FRIEND_INFO
{
    typedef int PackType;
    STRU_FRIEND_INFO() :type(_DEF_PACK_FRIEND_INFO), uuid(0), iconid(0), state(0)
    {
        memset(username, 0, sizeof(username));
        memset(feeling, 0, sizeof(feeling));
    }
    //需要 用户id 头像id 昵称 签名 状态--是否在线
    PackType type;
    int uuid;
    int iconid;
    int state;
    char username[_MAX_SIZE];
    char feeling[_MAX_SIZE];

}STRU_FRIEND_INFO;

//添加好友
typedef struct STRU_ADD_FRIEND_RQ
{
    typedef int PackType;
    // 如果用户1 添加用户2 为好友 需要 用户1 id 用户1 名字 ,用户2的名字
    STRU_ADD_FRIEND_RQ() :type(_DEF_PACK_ADDFRIEND_RQ), userid(0)
    {
        memset(userName, 0, sizeof(userName));
        memset(friendName, 0, sizeof(friendName));
    }
    PackType type;
    int userid;
    char userName[_MAX_SIZE];
    char friendName[_MAX_SIZE];

}STRU_ADD_FRIEND_RQ;

typedef struct STRU_ADD_FRIEND_RS
{
    typedef int PackType;
    STRU_ADD_FRIEND_RS() :type(_DEF_PACK_ADDFRIEND_RS), userid(0), friendid(0), result(add_success)
    {
        memset(friendName, 0, sizeof(friendName));
    }
    //如果用户1 添加用户2 需要 用户1id  用户2 id 用户2的名字 结果
    PackType type;
    int userid; // 用户1
    int friendid; // 用户2
    int result;
    char friendName[_MAX_SIZE];

}STRU_ADD_FRIEND_RS;

//聊天
/**
 * @brief 聊天内容请求块
*/
typedef struct STRU_CHAT_RQ
{
    typedef int PackType;
    STRU_CHAT_RQ() :type(_DEF_PACK_CHAT_RQ), userid(0), friendid(0)
    {
        memset(content, 0, _DEF_CONTENT_SIZE);
        memset(createTime, 0, 20);
    }
    // 谁发给谁 服务器转发  用户1 id 用户2 id 发的内容
    /**
     * @brief 数据包类型: _DEF_PACK_CHAT_RQ
    */
    PackType type;
    /**
     * @brief 用户唯一id
    */
    int userid;
    /**
     * @brief 好友id
    */
    int friendid;
    /**
     * @brief 聊天信息块的创建时间
     */
    char createTime[20];
    /**
     * @brief 聊天内容
     */
    char content[_DEF_CONTENT_SIZE];

}STRU_CHAT_RQ;

typedef struct STRU_CHAT_RS
{
    typedef int PackType;
    STRU_CHAT_RS() :type(_DEF_PACK_CHAT_RS), userid(0), friendid(0), result(0)
    {
    }
    PackType type;
    int userid;
    int friendid; //方便找是哪个人不在线
    int result;

}STRU_CHAT_RS;

typedef struct STRU_OFFLINE {
    typedef int PackType;
    STRU_OFFLINE() : type(_DEF_PACK_OFFLINE_RQ) {}
    PackType type;
    int uuid;
}STRU_OFFLINE;

// 文件传输协议
/**
 * @brief 文件信息请求
*/
struct STRU_FILE_INFO_RQ {
    typedef int PackType;
    STRU_FILE_INFO_RQ() : nType(_DEF_PROTOCOL_FILE_INFO_RQ), nFileSize(0), uuid(0), friendid(0) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
        memset(szFileName, 0, _MAX_FILE_PATH_SIZE);
    }
    PackType nType;
    char szFileId[_MAX_FILE_PATH_SIZE];
    char szFileName[_MAX_FILE_PATH_SIZE];
    uint64_t nFileSize;
    int uuid;
    int friendid;
};
/**
 * @brief 文件信息回复
*/
#define _file_accept (0)
#define _file_refuse (1)
struct STRU_FILE_INFO_RS
{
    typedef int PackType;
    STRU_FILE_INFO_RS() : nType(_DEF_PROTOCOL_FILE_INFO_RS), nResult(_file_accept), uuid(0), friendid(0) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
    }
    PackType nType;
    char szFileId[_MAX_FILE_PATH_SIZE];
    int nResult;
    int uuid;
    int friendid;
};

/**
 * @brief 文件块请求
*/
struct STRU_FILE_BLOCK_RQ
{
    typedef int PackType;
    STRU_FILE_BLOCK_RQ() : nType(_DEF_PROTOCOL_FILE_BLOCK_RQ), nBlockSize(0), uuid(0), friendid(0) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
        memset(szFileContent, 0, _DEF_FILE_CONTENT_SIZE);
    }
    PackType nType;
    char szFileId[_MAX_FILE_PATH_SIZE];
    char szFileContent[_DEF_FILE_CONTENT_SIZE];
    uint64_t nBlockSize;
    int uuid;
    int friendid;
};

/**
 * @brief 文件块接受回复
*/
#define _file_block_recv_success (0)
#define _file_block_recv_fail    (1)
struct STRU_FILE_BLOCK_RS
{
    typedef int PackType;
    STRU_FILE_BLOCK_RS() :nType(_DEF_PROTOCOL_FILE_BLOCK_RS), nResult(_file_block_recv_success), uuid(0), friendid(0) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
    }
    PackType nType;
    char szFileId[_MAX_FILE_PATH_SIZE];
    int nResult;
    int uuid;
    int friendid;
};

/**
 * @brief 文件信息
*/
struct FileInfo
{
    FileInfo() : nPos(0), nFileSize(0), pFile(nullptr) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
        memset(szFileName, 0, _MAX_FILE_PATH_SIZE);
        memset(szFilePath, 0, _MAX_FILE_PATH_SIZE);
    }
    char szFileId[_MAX_FILE_PATH_SIZE];
    char szFileName[_MAX_FILE_PATH_SIZE];
    char szFilePath[_MAX_FILE_PATH_SIZE];
    uint64_t nPos;
    uint64_t nFileSize;
    FILE* pFile;
};
