#include "stdafx.h"
#include "GetAbTestAPI.h"


GetAbTestAPI::GetAbTestAPI(void)
{
}


GetAbTestAPI::~GetAbTestAPI(void)
{
}

void GetAbTestAPI::ResetData()
{
	// �]�w���w�g�I�s�L ResetData()�ABaseAPI::DoWork() �~��q�L
	bResetDataDone = true;
	m_responseSuccess = false;
}

void GetAbTestAPI::SetAbTestId(INT64 id)
{
	m_abTestId = id;
}

bool GetAbTestAPI::IsSucceed()
{
	return m_responseSuccess;
}

void GetAbTestAPI::SetAppIdForContentReadonlyMode(CString appId, CString croId)
{
	m_appId = appId;
	m_contentReadonlyKey = croId;
}

void GetAbTestAPI::PrepareData()
{
	serverName = LEANPLUM_HOST;
	formAction.Format(_T("?appId=%s&clientKey=%s&apiVersion=%s&action=getAbTest"), m_appId, m_contentReadonlyKey, LEANPLUM_API_VERSION);
	postData = _T("");
}

void GetAbTestAPI::ExecuteResponseData()
{
	auto bridgeConfig = response.extract_string().get();
	json::value x = json::value::parse(utility::conversions::to_string_t(bridgeConfig)); 
	json::value arrayObj = x[_T("response")];

	m_abTestInfo.DataParse(arrayObj);
	m_responseSuccess = arrayObj[0].as_object().at(_T("success")).as_bool();
}

void GetAbTestAPI::Finish()
{
	NotifyObservers(MessageCode::MESSAGE_GETABTEST_FINISH);
}
