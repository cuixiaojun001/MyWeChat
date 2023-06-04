#include <iostream>
#include "TcpClientMediator.h"
#include "./net/TcpClient.h"

namespace net {
TcpClientMediator::TcpClientMediator()
{
    m_pNet = new TcpClient(this);
}
TcpClientMediator::~TcpClientMediator()
{
    if (m_pNet) {
        delete m_pNet;
        m_pNet = nullptr;
    }
}
bool TcpClientMediator::OpenNet()
{
    if (m_pNet->InitNet()) return true;
    return false;
}
void TcpClientMediator::CloseNet()
{
    m_pNet->UnInitNet();
}
bool TcpClientMediator::SendData(unsigned long lSendIP, const char* buf, int nLen)
{
    if (m_pNet->SendData(lSendIP, buf, nLen)) return true;
    return false;
}

void TcpClientMediator::DealData(unsigned long lSendIP, const char* buf, int nLen)
{
     // std::cout<< lSendIP << ":" << buf <<std::endl;
     Q_EMIT SIG_ReadyData(lSendIP, buf, nLen);
}
}
