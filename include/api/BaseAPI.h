/*
實作 rest SDK 的底層 class,
繼承自 Subject 來實現 observer pattern,
1. 繼承自這個 class 的物件必須實作 ResetData()、PrepareData(), ExecuteResponseData() and Finish()
2. ResetData() 最後要設定 bResetDataDone 為 true，BaseAPI::DoWork() 開頭檢查 bResetDataDone 為 true 才繼續。
3. 如果要走 SSL 連線，PrepareData() 實作要指定 bSSL = true
*/
#pragma once

#include "../cpprestsdk/cpprest/http_client.h" // Rest SDK
#include "Subject.h"

using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features

class BaseAPI : public Subject
{
public:
	BaseAPI();
	void DoWork();
protected:
	//! 繼承的 class 要實作將所有 member variable 初始
	virtual void ResetData() = 0;
	//! 準備連線所需資料
	virtual void PrepareData() = 0;
	//! 處理連線回傳值
	virtual void ExecuteResponseData() = 0;
	//! 通知 observer 連線結束
	virtual void Finish() = 0;

	CString serverName;
	CString formAction;
	CString postData;
	http_response response;
	bool bSSL;
	//! 用來檢查是否呼叫 DoWork() 前有先 ResetData(). ref: #89681
	bool bResetDataDone;
};