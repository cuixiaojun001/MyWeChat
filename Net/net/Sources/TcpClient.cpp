#include "TcpClient.h"
#include <iostream>
#include "qDebug"
namespace net {
TcpClient::TcpClient(INetMediator* mediator) : m_socket(INVALID_SOCKET), m_hThreadHandle(NULL), m_isStop(false)
{
    m_pMediator = mediator;
}
TcpClient::~TcpClient()
{
    UnInitNet();
}
bool TcpClient::InitNet()
{
    /*加载库*/
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        return false;
    }

    /* Confirm that the WinSock DLL supports 2.2.*/
    /* Note that if the DLL supports versions greater    */
    /* than 2.2 in addition to 2.2, it will still return */
    /* 2.2 in wVersion since that is the version we      */
    /* requested.                                        */

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
        return false;
    }
    else
        printf("The Winsock 2.2 dll was found okay\n");
    /*创建套接字*/
    if ((m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        WSACleanup();
        return false;
    }
    /*连接connect()*/
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.S_un.S_addr = inet_addr(_DEF_SERVER_IP);
    server_addr.sin_port = htons(_DEF_TCP_PORT);

    if (connect(m_socket, (const sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        UnInitNet();
        return false;
    }
    std::cout << "connect server[" << inet_ntoa(server_addr.sin_addr) << "] success." << std::endl;

    m_hThreadHandle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);

    return true;
}
void TcpClient::UnInitNet()
{
    m_isStop = true;
    if (m_hThreadHandle) {
        if (WaitForSingleObject(m_hThreadHandle, 100) == WAIT_TIMEOUT) {
            TerminateThread(m_hThreadHandle, -1);
        }
        CloseHandle(m_hThreadHandle);
        m_hThreadHandle = NULL;
    }
    if (m_socket && m_socket != INVALID_SOCKET) {
        closesocket(m_socket);
    }
    WSACleanup();
}
bool TcpClient::SendData(unsigned long lSendIP, const char* buf, int nLen)
{
    if (!buf || nLen <= 0) return false;
    // TODO: 防止粘包, 解决办法: 先发包大小, 再发数据包
    send(m_socket, (char*)&nLen, sizeof(int), 0);
    if (send(m_socket, buf, nLen, 0) <= 0) return false;

    return true;
}
void TcpClient::RecvData()
{
    Sleep(100);
    // SOCKET sockWaiter = m_mapThreadIdToSocket[GetCurrentThreadId()];
    // if (!sockWaiter || sockWaiter == INVALID_SOCKET) return;
    int nPackSize = 0; // 存储包大小

    int iResult = 0;
    while (!m_isStop) {
        // 先接受包大小 再接受数据包
        iResult = recv(m_socket, (char*)&nPackSize, sizeof(int), 0);
        qDebug() << "ip[123.57.187.239] recv 字节数: "<< iResult << " says nPackSize: " << nPackSize;
        if (iResult <= 0) break;
        int offset = 0; //从buf开始起始偏移多少
        char* recvbuf = new char[nPackSize];
        while (nPackSize > 0) {
            qDebug() << "剩余" << nPackSize << "未读取";
            if ((iResult = recv(m_socket, recvbuf + offset, nPackSize, 0)) > 0) {
                // TODO: 处理数据
                qDebug() << "recv 读取一次, 读了" << iResult << "字节";
                nPackSize -= iResult;
                offset += iResult;
            }
        }
        qDebug() << "ip[123.57.187.239] says: " << recvbuf;
        m_pMediator->DealData(m_socket, recvbuf, offset);
    }
}
unsigned int __stdcall TcpClient::RecvThread(LPVOID lpParameter)
{
    TcpClient* pthis = (TcpClient*)lpParameter;
    pthis->RecvData();
    return 0;
}
}

