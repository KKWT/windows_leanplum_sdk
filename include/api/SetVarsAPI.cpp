#include "stdafx.h"
#include "SetVarsAPI.h"


SetVarsAPI::SetVarsAPI(void)
{
	ResetData();
}


SetVarsAPI::~SetVarsAPI(void)
{
}

void SetVarsAPI::ResetData()
{
	// 設定為已經呼叫過 ResetData()，BaseAPI::DoWork() 才能通過
	bResetDataDone = true;
	m_responseSuccess = false;
}

void SetVarsAPI::SetPostData(CString data)
{
	m_postData = data;
}

bool SetVarsAPI::IsSucceed()
{
	return m_responseSuccess;
}

void SetVarsAPI::SetAppIdForDevelopmentMode(CString appId, CString devId)
{
	m_appId = appId;
	m_developmentKey = devId;
}

void SetVarsAPI::PrepareData()
{
	serverName = LEANPLUM_HOST;
	formAction.Format(_T("?appId=%s&clientKey=%s&apiVersion=%s&action=setVars"), m_appId, m_developmentKey, LEANPLUM_API_VERSION);
	postData = m_postData;
}

void SetVarsAPI::ExecuteResponseData()
{
	auto bridgeConfig = response.extract_string().get();
	json::value x = json::value::parse(utility::conversions::to_string_t(bridgeConfig)); 
	json::value arrayObj = x[_T("response")];

	m_responseSuccess = arrayObj[0].as_object().at(_T("success")).as_bool();
}

void SetVarsAPI::Finish()
{
	NotifyObservers(MessageCode::MESSAGE_SETVARS_FINISH);
}
