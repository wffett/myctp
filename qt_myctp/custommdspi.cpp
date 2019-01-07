#include <iostream>
#include <string.h>
#include <fstream>
#include <unordered_map>
#include "custommdspi.h"
using namespace std;

extern CThostFtdcMdApi *g_pMdUserApi;
//extern char gMdFrontAddr[];
static int iRequestID;
extern TThostFtdcBrokerIDType gBrokerID;
extern TThostFtdcInvestorIDType gInvesterID;
extern TThostFtdcPasswordType gInvesterPassword;

void CustomMdSpi::wReqUserLogin()
{
   CThostFtdcReqUserLoginField req;
   memset(&req,0,sizeof (req));
   strcpy(req.BrokerID,gBrokerID);
   strcpy(req.UserID,gInvesterID);
   strcpy(req.Password,gInvesterPassword);
   g_pMdUserApi->ReqUserLogin(&req,++iRequestID);

}



void CustomMdSpi::OnFrontConnected()
{
    std::cout << "=====connected successfully=====" << std::endl;
    wReqUserLogin();
}

void CustomMdSpi::OnFrontDisconnected(int nReason)
{
    std::cerr << "=====�������ӶϿ�=====" << std::endl;
    std::cerr << "�����룺 " << nReason << std::endl;
}


void CustomMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
    std::cerr << "=====����������ʱ=====" << std::endl;
    std::cerr << "���ϴ�����ʱ�䣺 " << nTimeLapse << std::endl;
}


void CustomMdSpi::OnRspUserLogin(
    CThostFtdcRspUserLoginField *pRspUserLogin,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        std::cout << "=====Login successful =====" << std::endl;
        std::cout << "Trading Day is: " << pRspUserLogin->TradingDay << std::endl;
        std::cout << "Login Time is: " << pRspUserLogin->LoginTime << std::endl;
        std::cout << "Your BrokerID is: " << pRspUserLogin->BrokerID << std::endl;
        std::cout << "Your ID is: " << pRspUserLogin->UserID << std::endl;

//        int rt = g_pMdUserApi->SubscribeMarketData(g_pInstrumentID, instrumentNum);
//        if (!rt)
//            std::cout << ">>>>>>���Ͷ������������ɹ�" << std::endl;
//        else
//            std::cerr << "--->>>���Ͷ�����������ʧ��" << std::endl;
    }
    else
        std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}


void CustomMdSpi::OnRspUserLogout(
    CThostFtdcUserLogoutField *pUserLogout,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        std::cout << "=====�˻��ǳ��ɹ�=====" << std::endl;
        std::cout << "�����̣� " << pUserLogout->BrokerID << std::endl;
        std::cout << "�ʻ����� " << pUserLogout->UserID << std::endl;
    }
    else
        std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ����֪ͨ
void CustomMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (bResult)
        std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��������Ӧ��
void CustomMdSpi::OnRspSubMarketData(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        std::cout << "=====���������ɹ�=====" << std::endl;
        std::cout << "��Լ���룺 " << pSpecificInstrument->InstrumentID << std::endl;
        // ������Ҫ�����ļ��������ݿ⣬�����ﴴ����ͷ,��ͬ�ĺ�Լ�����洢
        char filePath[100] = {'\0'};
        sprintf(filePath, "%s_market_data.csv", pSpecificInstrument->InstrumentID);
        std::ofstream outFile;
        outFile.open(filePath, std::ios::out); // �¿��ļ�
        outFile << "��Լ����" << ","
            << "����ʱ��" << ","
            << "���¼�" << ","
            << "�ɽ���" << ","
            << "����һ" << ","
            << "����һ" << ","
            << "����һ" << ","
            << "����һ" << ","
            << "�ֲ���" << ","
            << "������"
            << std::endl;
        outFile.close();
    }
    else
        std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ȡ����������Ӧ��
void CustomMdSpi::OnRspUnSubMarketData(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        std::cout << "=====ȡ�����������ɹ�=====" << std::endl;
        std::cout << "��Լ���룺 " << pSpecificInstrument->InstrumentID << std::endl;
    }
    else
        std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ����ѯ��Ӧ��
void CustomMdSpi::OnRspSubForQuoteRsp(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        std::cout << "=====����ѯ�۳ɹ�=====" << std::endl;
        std::cout << "��Լ���룺 " << pSpecificInstrument->InstrumentID << std::endl;
    }
    else
        std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ȡ������ѯ��Ӧ��
void CustomMdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        std::cout << "=====ȡ������ѯ�۳ɹ�=====" << std::endl;
        std::cout << "��Լ���룺 " << pSpecificInstrument->InstrumentID << std::endl;
    }
    else
        std::cerr << "���ش���--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// ��������֪ͨ
void CustomMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    // ��ӡ���飬�ֶν϶࣬��ȡ����
    std::cout << "=====������������=====" << std::endl;
    std::cout << "�����գ� " << pDepthMarketData->TradingDay << std::endl;
    std::cout << "���������룺 " << pDepthMarketData->ExchangeID << std::endl;
    std::cout << "��Լ���룺 " << pDepthMarketData->InstrumentID << std::endl;
    std::cout << "��Լ�ڽ������Ĵ��룺 " << pDepthMarketData->ExchangeInstID << std::endl;
    std::cout << "���¼ۣ� " << pDepthMarketData->LastPrice << std::endl;
    std::cout << "������ " << pDepthMarketData->Volume << std::endl;
    // ȡ����������
    //int rt = g_pMdUserApi->UnSubscribeMarketData(g_pInstrumentID, instrumentNum);
    //if (!rt)
    //	std::cout << ">>>>>>����ȡ���������������ɹ�" << std::endl;
    //else
    //	std::cerr << "--->>>����ȡ��������������ʧ��" << std::endl;
}

// ѯ������֪ͨ
void CustomMdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
    // ����ѯ�۽���
    std::cout << "=====����ѯ�۽���=====" << std::endl;
    std::cout << "�����գ� " << pForQuoteRsp->TradingDay << std::endl;
    std::cout << "���������룺 " << pForQuoteRsp->ExchangeID << std::endl;
    std::cout << "��Լ���룺 " << pForQuoteRsp->InstrumentID << std::endl;
    std::cout << "ѯ�۱��ţ� " << pForQuoteRsp->ForQuoteSysID << std::endl;
}
