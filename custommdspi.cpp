#include <iostream>
#include <fstream>
#include <unordered_map>
#include "custommdspi.h"

CThostFtdcMdApi *g_pMdUserApi;            
extern char gMdFrontAddr[];              
TThostFtdcBrokerIDType gBrokerID;       
TThostFtdcInvestorIDType gInvesterID;  
TThostFtdcPasswordType gInvesterPassword;


void CustomMdSpi::OnFrontConnected()
{
    std::cout << "=====connected successfully=====" << std::endl;
}

void CustomMdSpi::OnFrontDisconnected(int nReason)
{
    std::cerr << "=====网络连接断开=====" << std::endl;
    std::cerr << "错误码： " << nReason << std::endl;
}


void CustomMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
    std::cerr << "=====网络心跳超时=====" << std::endl;
    std::cerr << "距上次连接时间： " << nTimeLapse << std::endl;
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
        std::cout << "=====账户登录成功=====" << std::endl;
        std::cout << "交易日： " << pRspUserLogin->TradingDay << std::endl;
        std::cout << "登录时间： " << pRspUserLogin->LoginTime << std::endl;
        std::cout << "经纪商： " << pRspUserLogin->BrokerID << std::endl;
        std::cout << "帐户名： " << pRspUserLogin->UserID << std::endl;

//        int rt = g_pMdUserApi->SubscribeMarketData(g_pInstrumentID, instrumentNum);
//        if (!rt)
//            std::cout << ">>>>>>发送订阅行情请求成功" << std::endl;
//        else
//            std::cerr << "--->>>发送订阅行情请求失败" << std::endl;
    }
    else
        std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
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
        std::cout << "=====账户登出成功=====" << std::endl;
        std::cout << "经纪商： " << pUserLogout->BrokerID << std::endl;
        std::cout << "帐户名： " << pUserLogout->UserID << std::endl;
    }
    else
        std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 错误通知
void CustomMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (bResult)
        std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 订阅行情应答
void CustomMdSpi::OnRspSubMarketData(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        std::cout << "=====订阅行情成功=====" << std::endl;
        std::cout << "合约代码： " << pSpecificInstrument->InstrumentID << std::endl;
        // 如果需要存入文件或者数据库，在这里创建表头,不同的合约单独存储
        char filePath[100] = {'\0'};
        sprintf(filePath, "%s_market_data.csv", pSpecificInstrument->InstrumentID);
        std::ofstream outFile;
        outFile.open(filePath, std::ios::out); // 新开文件
        outFile << "合约代码" << ","
            << "更新时间" << ","
            << "最新价" << ","
            << "成交量" << ","
            << "买价一" << ","
            << "买量一" << ","
            << "卖价一" << ","
            << "卖量一" << ","
            << "持仓量" << ","
            << "换手率"
            << std::endl;
        outFile.close();
    }
    else
        std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 取消订阅行情应答
void CustomMdSpi::OnRspUnSubMarketData(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        std::cout << "=====取消订阅行情成功=====" << std::endl;
        std::cout << "合约代码： " << pSpecificInstrument->InstrumentID << std::endl;
    }
    else
        std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 订阅询价应答
void CustomMdSpi::OnRspSubForQuoteRsp(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument,
    CThostFtdcRspInfoField *pRspInfo,
    int nRequestID,
    bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        std::cout << "=====订阅询价成功=====" << std::endl;
        std::cout << "合约代码： " << pSpecificInstrument->InstrumentID << std::endl;
    }
    else
        std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 取消订阅询价应答
void CustomMdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        std::cout << "=====取消订阅询价成功=====" << std::endl;
        std::cout << "合约代码： " << pSpecificInstrument->InstrumentID << std::endl;
    }
    else
        std::cerr << "返回错误--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << std::endl;
}

// 行情详情通知
void CustomMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    // 打印行情，字段较多，截取部分
    std::cout << "=====获得深度行情=====" << std::endl;
    std::cout << "交易日： " << pDepthMarketData->TradingDay << std::endl;
    std::cout << "交易所代码： " << pDepthMarketData->ExchangeID << std::endl;
    std::cout << "合约代码： " << pDepthMarketData->InstrumentID << std::endl;
    std::cout << "合约在交易所的代码： " << pDepthMarketData->ExchangeInstID << std::endl;
    std::cout << "最新价： " << pDepthMarketData->LastPrice << std::endl;
    std::cout << "数量： " << pDepthMarketData->Volume << std::endl;
    // 取消订阅行情
    //int rt = g_pMdUserApi->UnSubscribeMarketData(g_pInstrumentID, instrumentNum);
    //if (!rt)
    //	std::cout << ">>>>>>发送取消订阅行情请求成功" << std::endl;
    //else
    //	std::cerr << "--->>>发送取消订阅行情请求失败" << std::endl;
}

// 询价详情通知
void CustomMdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
    // 部分询价结果
    std::cout << "=====获得询价结果=====" << std::endl;
    std::cout << "交易日： " << pForQuoteRsp->TradingDay << std::endl;
    std::cout << "交易所代码： " << pForQuoteRsp->ExchangeID << std::endl;
    std::cout << "合约代码： " << pForQuoteRsp->InstrumentID << std::endl;
    std::cout << "询价编号： " << pForQuoteRsp->ForQuoteSysID << std::endl;
}
