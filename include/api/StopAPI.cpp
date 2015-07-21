#include "stdafx.h"
#include "StopAPI.h"


StopAPI::StopAPI(void)
{
	ResetData();
}


StopAPI::~StopAPI(void)
{
}

void StopAPI::ResetData()
{
	m_deviceId = 0;
	m_userId = 0;
	// 設定為已經呼叫過 ResetData()，BaseAPI::DoWork() 才能通過
	bResetDataDone = true;
	m_responseSuccess = false;
}

void StopAPI::SetIds(int did, int uid)
{
	m_deviceId = did;
	m_userId = uid;
}

bool StopAPI::IsSucceed()
{
	return m_responseSuccess;
}

void StopAPI::SetAppIdForProductionMode(CString appId, CString proId)
{
	m_appId = appId;
	m_productionKey = proId;
}

void StopAPI::PrepareData()
{
	serverName = LEANPLUM_HOST;
	formAction.Format(_T("?appId=%s&clientKey=%s&apiVersion=%s&action=stop&deviceId=%d&userId=%d"), m_appId, m_productionKey, LEANPLUM_API_VERSION, m_deviceId, m_userId);
	postData = _T("");
}

void StopAPI::ExecuteResponseData()
{
	auto bridgeConfig = response.extract_string().get();
	json::value x = json::value::parse(utility::conversions::to_string_t(bridgeConfig)); 
	json::value arrayObj = x[_T("response")];

	m_responseSuccess = arrayObj[0].as_object().at(_T("success")).as_bool();
}

void StopAPI::Finish()
{
	NotifyObservers(MessageCode::MESSAGE_STOP_FINISH);
}
