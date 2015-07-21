#include "stdafx.h"
#include "StartAPI.h"


StartAPI::StartAPI(void)
{
	ResetData();
}


StartAPI::~StartAPI(void)
{
}

void StartAPI::ResetData()
{
	m_deviceId = 0;
	m_userId = 0;
	m_locale = _T("zh_TW");
	// 設定為已經呼叫過 ResetData()，BaseAPI::DoWork() 才能通過
	bResetDataDone = true;
	m_responseSuccess = false;
}

void StartAPI::SetIds(int did, int uid)
{
	m_deviceId = did;
	m_userId = uid;
}

void StartAPI::SetLocale(CString locale)
{
	m_locale = locale;
}

bool StartAPI::IsSucceed()
{
	return m_responseSuccess;
}

void StartAPI::SetAppIdForProductionMode(CString appId, CString proId)
{
	m_appId = appId;
	m_productionKey = proId;
}

void StartAPI::PrepareData()
{
	serverName = LEANPLUM_HOST;
	formAction.Format(_T("?appId=%s&clientKey=%s&apiVersion=%s&action=start&deviceId=%d&userId=%d&locale=%s"), m_appId, m_productionKey, LEANPLUM_API_VERSION, m_deviceId, m_userId, m_locale);
	postData = _T("");
}

void StartAPI::ExecuteResponseData()
{
	auto bridgeConfig = response.extract_string().get();
	json::value x = json::value::parse(utility::conversions::to_string_t(bridgeConfig)); 
	json::value arrayObj = x[_T("response")];

	m_responseSuccess = arrayObj[0].as_object().at(_T("success")).as_bool();
	if (m_responseSuccess) {
		m_responseVariabls = arrayObj[0].as_object().at(_T("vars"));
	} else {
		CString error = arrayObj[0].as_object().at(_T("error")).at(_T("message")).as_string().c_str();
		AfxMessageBox(error);
	}
}

void StartAPI::Finish()
{
	NotifyObservers(MessageCode::MESSAGE_START_FINISH);
}
