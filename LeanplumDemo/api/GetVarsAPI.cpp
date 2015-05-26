#include "stdafx.h"
#include "GetVarsAPI.h"


GetVarsAPI::GetVarsAPI(void)
{
	ResetData();
}


GetVarsAPI::~GetVarsAPI(void)
{
}

void GetVarsAPI::ResetData()
{
	m_deviceId = 0;
	m_userId = 0;
	// 設定為已經呼叫過 ResetData()，BaseAPI::DoWork() 才能通過
	bResetDataDone = true;
	m_responseSuccess = false;
}

void GetVarsAPI::SetIds(int did, int uid)
{
	m_deviceId = did;
	m_userId = uid;
}

bool GetVarsAPI::IsSucceed()
{
	return m_responseSuccess;
}

void GetVarsAPI::SetAppIdForProductionMode(CString appId, CString proId)
{
	m_appId = appId;
	m_productionKey = proId;
}

void GetVarsAPI::PrepareData()
{
	serverName = LEANPLUM_HOST;
	//formAction.Format(_T("?appId=%s&clientKey=%s&apiVersion=%s&action=getVars&deviceId=%d"), m_appId, m_productionKey, LEANPLUM_API_VERSION, m_deviceId);
	formAction.Format(_T("?appId=%s&clientKey=%s&apiVersion=%s&action=getVars&deviceId=%d&userId=%d"), m_appId, m_productionKey, LEANPLUM_API_VERSION, m_deviceId, m_userId);
	postData = _T("");
}

void GetVarsAPI::ExecuteResponseData()
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

void GetVarsAPI::Finish()
{
	NotifyObservers(MessageCode::MESSAGE_GETVARS_FINISH);
}
