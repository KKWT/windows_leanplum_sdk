#include "stdafx.h"
#include "GetAbTestsAPI.h"


GetAbTestsAPI::GetAbTestsAPI(void)
{
	ResetData();
}


GetAbTestsAPI::~GetAbTestsAPI(void)
{
}

void GetAbTestsAPI::ResetData()
{
	// 設定為已經呼叫過 ResetData()，BaseAPI::DoWork() 才能通過
	bResetDataDone = true;
	m_responseSuccess = false;
}

bool GetAbTestsAPI::IsSucceed()
{
	return m_responseSuccess;
}

void GetAbTestsAPI::SetAppIdForContentReadonlyMode(CString appId, CString croId)
{
	m_appId = appId;
	m_contentReadonlyKey = croId;
}

std::vector<AbTestInfo> GetAbTestsAPI::GetAbTestsInfo()
{
	return m_abTestInfos;
}

void GetAbTestsAPI::PrepareData()
{
	serverName = LEANPLUM_HOST;
	formAction.Format(_T("?appId=%s&clientKey=%s&apiVersion=%s&action=getAbTests"), m_appId, m_contentReadonlyKey, LEANPLUM_API_VERSION);
	postData = _T("");
}

void GetAbTestsAPI::ExecuteResponseData()
{
	auto bridgeConfig = response.extract_string().get();
	json::value x = json::value::parse(utility::conversions::to_string_t(bridgeConfig)); 

	m_responseSuccess = x[_T("response")][0].as_object().at(_T("success")).as_bool();
	for (auto iter = x[_T("response")][0].as_object().cbegin(); iter != x[_T("response")][0].as_object().cend(); ++iter) {
		AbTestInfo abInfo;
		json::value arrayObj = x[_T("response")][0].at(iter->first);
		int size = arrayObj.size();
		for (int i = 0; i < size; i++) {  
			abInfo.DataParse(arrayObj[i]);
			m_abTestInfos.push_back(abInfo);
		}
	}
}

void GetAbTestsAPI::Finish()
{
	NotifyObservers(MessageCode::MESSAGE_GETABTESTS_FINISH);
}
