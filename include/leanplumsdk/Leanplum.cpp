#include "stdafx.h"
#include "Leanplum.h"


Leanplum::Leanplum(void)
{
	m_variablesStr = _T("");
	m_variablesMap.clear();
}


Leanplum::~Leanplum(void)
{
}

void Leanplum::Notify(MessageCode::MESSAGE_CODE messageCode, WPARAM wParam /*= NULL*/, LPARAM lParam /*= NULL*/)
{
	if (MessageCode::MESSAGE_GETVARS_FINISH == messageCode) {
		m_isSucceed = m_getVarsApi.IsSucceed();
		if (m_isSucceed) {
			ParserResponse(m_getVarsApi.m_responseVariabls);
			NotifyObservers(MessageCode::MESSAGE_GETVARS_FINISH);
		}
	} else if (MessageCode::MESSAGE_START_FINISH == messageCode) {
		m_isSucceed = m_startApi.IsSucceed();
		if (m_isSucceed) {
			ParserResponse(m_startApi.m_responseVariabls);
			NotifyObservers(MessageCode::MESSAGE_START_FINISH);
		}
	} else if (MessageCode::MESSAGE_GETABTEST_FINISH == messageCode) {
		m_isSucceed = m_getAbTestApi.IsSucceed();
		if (m_isSucceed) {
			NotifyObservers(MessageCode::MESSAGE_GETABTEST_FINISH);
		}
	} else if (MessageCode::MESSAGE_STOP_FINISH == messageCode) {
		m_isSucceed = m_stopApi.IsSucceed();
		if (m_isSucceed) {
			NotifyObservers(MessageCode::MESSAGE_STOP_FINISH);
		}
	} else if (MessageCode::MESSAGE_SETVARS_FINISH == messageCode) {
		m_isSucceed = m_setVarsApi.IsSucceed();
		if (m_isSucceed) {
			NotifyObservers(MessageCode::MESSAGE_SETVARS_FINISH);
		}
	} else if (MessageCode::MESSAGE_GETABTESTS_FINISH == messageCode) {
		m_isSucceed = m_getAbTestsApi.IsSucceed();
		if (m_isSucceed) {
			m_abTests = m_getAbTestsApi.GetAbTestsInfo();
			NotifyObservers(MessageCode::MESSAGE_GETABTESTS_FINISH);
		}
	}
}

void Leanplum::DefineVariable(CString name, std::pair<VARIABLE_TYPE, CString> value)
{
	m_variablesMap.insert(make_pair(name, value));
	if (VARIABLE_TYPE::INT == value.first) {
		m_variablesStr = m_variablesStr + _T(",\"") + name + _T("\":") + value.second;
	} else if (VARIABLE_TYPE::BOOL == value.first) {
		m_variablesStr = m_variablesStr + _T(",\"") + name + _T("\":") + value.second;
	} else if (VARIABLE_TYPE::STRING == value.first) {
		m_variablesStr = m_variablesStr + _T(",\"") + name + _T("\":\"") + value.second + _T("\""); 
	}
}

void Leanplum::ParserResponse(json::value response)
{
	if (response.is_null()){
		return;
	}

	CString key;
	VARIABLE_TYPE type;
	typedef std::map<CString, std::pair<VARIABLE_TYPE, CString>>::iterator it_type;
	for(it_type iterator = m_variablesMap.begin(); iterator != m_variablesMap.end(); iterator++) {
		key = iterator->first;
		type = iterator->second.first;
		if (VARIABLE_TYPE::INT == type) {
			 int v = response.at(key.GetBuffer()).as_integer();
			 iterator->second.second.Format(_T("%d"), v);
		} else if (VARIABLE_TYPE::BOOL == type) {
			bool v = response.at(key.GetBuffer()).as_bool();
			iterator->second.second = v? _T("true"):_T("false");
		} else if (VARIABLE_TYPE::STRING == type) {
			iterator->second.second = response.at(key.GetBuffer()).as_string().c_str();
		}
	}
}

void Leanplum::Start()
{
	m_startApi.AttachObserver(this);
	m_startApi.SetAppIdForProductionMode(m_appId, m_productionKey);
	m_startApi.SetIds(m_deviceId, m_userId);
	m_startApi.SetLocale(m_locale);
	m_startApi.DoWork();
}

void Leanplum::Stop()
{
	m_stopApi.AttachObserver(this);
	m_stopApi.SetAppIdForProductionMode(m_appId, m_productionKey);
	m_stopApi.SetIds(m_deviceId, m_userId);
	m_stopApi.DoWork();
}

void Leanplum::FinishVariablesDefinition()
{
	m_setVarsApi.AttachObserver(this);
	m_setVarsApi.SetAppIdForDevelopmentMode(m_appId, m_developmentKey);
	m_variablesStr = m_variablesStr.Mid(1, m_variablesStr.GetLength()-1);
	m_postData.Format(_T("{\"vars\":{%s}}"), m_variablesStr);
	m_setVarsApi.SetPostData(m_postData);
	m_setVarsApi.DoWork();
}

void Leanplum::SyncVariables()
{
	m_getVarsApi.AttachObserver(this);
	m_getVarsApi.SetAppIdForProductionMode(m_appId, m_productionKey);
	m_getVarsApi.SetIds(m_deviceId, m_userId);
	m_getVarsApi.DoWork();
}

void Leanplum::SetAppId(CString id)
{
	m_appId = id;
}

void Leanplum::SetProductionKey(CString id)
{
	m_productionKey = id;
}

void Leanplum::SetDevelopmentKey(CString id)
{
	m_developmentKey = id;
}

void Leanplum::SetDataExportKey(CString id)
{
	m_dataExportKey = id;
}

void Leanplum::SetContentReadonlyKey(CString id)
{
	m_contentReadonlyKey = id;
}

bool Leanplum::GetValuebyId(CString name, int& value)
{
	auto result = m_variablesMap.find(name);
	if (result != m_variablesMap.end()) {
		value = _ttoi(m_variablesMap[name].second);
		return true;
	} else {
		return false;
	}
}

bool Leanplum::GetValuebyId(CString name, bool& value)
{
	auto result = m_variablesMap.find(name);
	if (result != m_variablesMap.end()) {
		if (_T("true") == m_variablesMap[name].second) {
			value = true;
		} else {
			value = false;
		}
		return true;
	} else {
		return false;
	}
}

bool Leanplum::GetValuebyId(CString name, CString& value)
{
	auto result = m_variablesMap.find(name);
	if (result != m_variablesMap.end()) {
		value = m_variablesMap[name].second;
		return true;
	} else {
		return false;
	}
}

void Leanplum::GetAbTests()
{
	m_getAbTestsApi.AttachObserver(this);
	m_getAbTestsApi.SetAppIdForContentReadonlyMode(m_appId, m_contentReadonlyKey);
	m_getAbTestsApi.DoWork();
}

void Leanplum::GetAbTest(INT64 id)
{
	m_getAbTestApi.AttachObserver(this);
	m_getAbTestApi.SetAppIdForContentReadonlyMode(m_appId, m_contentReadonlyKey);
	m_getAbTestApi.SetAbTestId(id);
	m_getAbTestApi.DoWork();
}

void Leanplum::SetDeviceId(int did)
{
	m_deviceId = did;
}

void Leanplum::SetUserId(int uid)
{
	m_userId = uid;
}

void Leanplum::SetLocale(CString locale)
{
	m_locale = locale;
}

void Leanplum::ResetApisData()
{
	// reset every api data for next connection
	m_getAbTestApi.ResetData();
	m_getAbTestsApi.ResetData();
	m_getVarsApi.ResetData();
	m_setVarsApi.ResetData();
	m_startApi.ResetData();
	m_stopApi.ResetData();
	// remove from every api's observer list
	m_getAbTestApi.DetachObserver(this);
	m_getAbTestsApi.DetachObserver(this);
	m_getVarsApi.DetachObserver(this);
	m_setVarsApi.DetachObserver(this);
	m_startApi.DetachObserver(this);
	m_stopApi.DetachObserver(this);
}

std::vector<AbTestInfo> Leanplum::GetAbTestsInfo()
{
	return m_abTests;
}
