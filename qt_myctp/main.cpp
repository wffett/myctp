#include <iostream>
#include "custommdspi.h"
#include "CTP_API_64/ThostFtdcMdApi.h"

using namespace std;

char gMdFrontAddr[] = "tcp://180.168.146.187:13040";
CThostFtdcMdApi *g_pMdUserApi;
CThostFtdcMdSpi *pMdUserSpi;
TThostFtdcBrokerIDType gBrokerID = "9999";
TThostFtdcInvestorIDType gInvesterID = "129198";
TThostFtdcPasswordType gInvesterPassword = "wang190611";
int main()
{
    pMdUserSpi = new CustomMdSpi();
    g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
    g_pMdUserApi->RegisterSpi(pMdUserSpi);              
    g_pMdUserApi->RegisterFront(gMdFrontAddr);         
    g_pMdUserApi->Init();                             
    g_pMdUserApi->Join();
    delete pMdUserSpi;
    g_pMdUserApi->Release();

}
