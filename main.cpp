#include <iostream>
#include "custommdspi.h"

using namespace std;
int main()
{


    char gMdFrontAddr[] = "tcp://180.168.146.187:13040";
    CThostFtdcMdSpi *pMdUserSpi;        
    CThostFtdcMdApi *g_pMdUserApi;             
    pMdUserSpi = new CustomMdSpi();        
    g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();   
    g_pMdUserApi->RegisterSpi(pMdUserSpi);              
    g_pMdUserApi->RegisterFront(gMdFrontAddr);         
    g_pMdUserApi->Init();                             
    g_pMdUserApi->Join();
    delete pMdUserSpi;
    g_pMdUserApi->Release();

}
