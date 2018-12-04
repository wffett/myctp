#include <iostream>
#include "custommdspi.h"

using namespace std;
int main()
{


    char gMdFrontAddr[] = "tcp://180.168.146.187:13040";
    CThostFtdcMdSpi *pMdUserSpi = new CustomMdSpi();        
    CThostFtdcMdApi *g_pMdUserApi;             
    g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();   
    g_pMdUserApi->RegisterSpi(pMdUserSpi);              
    g_pMdUserApi->RegisterFront(gMdFrontAddr);         
    g_pMdUserApi->Init();                             
    cout << "1111111111111..." << endl;

    g_pMdUserApi->Join();
    cout << "..." << endl;
    delete pMdUserSpi;
    g_pMdUserApi->Release();

}
