#pragma once
#include "GetAbTestAPI.h"
#include "GetAbTestsAPI.h"
#include "GetVarsAPI.h"
#include "SetVarsAPI.h"
#include "StartAPI.h"
#include "StopAPI.h"

class Leanplum : public Subject, InterfaceObserver
{
public:
	enum VARIABLE_TYPE {
		INT,
		BOOL,
		STRING
	};

	Leanplum(void);
	~Leanplum(void);
	void Notify(MessageCode::MESSAGE_CODE messageCode, WPARAM wParam = NULL, LPARAM lParam = NULL);
	void DefineVariable(CString name, std::pair<VARIABLE_TYPE, CString> value);
	void Start();
	void Stop();
	void FinishVariablesDefinition();
	void SyncVariables();
	void SetAppId(CString id);
	void SetProductionKey(CString id);
	void SetDevelopmentKey(CString id);
	void SetDataExportKey(CString id);
	void SetContentReadonlyKey(CString id);
	bool GetValuebyId(CString name, int& value);
	bool GetValuebyId(CString name, bool& value);
	bool GetValuebyId(CString name, CString& value);
	void GetAbTests();
	void GetAbTest(INT64 id);
	void SetDeviceId(int did);
	void SetUserId(int uid);
	void SetLocale(CString locale);
	void ResetApisData();
	std::vector<AbTestInfo> GetAbTestsInfo();

	std::map<CString, std::pair<VARIABLE_TYPE, CString>> m_variablesMap;

private:
	int m_deviceId;
	int m_userId;
	bool m_isSucceed;
	CString m_locale;
	CString m_variablesStr;
	CString m_postData;
	CString m_appId;
	CString m_productionKey;
	CString m_developmentKey;
	CString m_dataExportKey;
	CString m_contentReadonlyKey;
	GetAbTestAPI m_getAbTestApi;
	GetAbTestsAPI m_getAbTestsApi;
	GetVarsAPI m_getVarsApi;
	SetVarsAPI m_setVarsApi;
	StartAPI m_startApi;
	StopAPI m_stopApi;
	std::vector<AbTestInfo> m_abTests;

	void ParserResponse(json::value response);
};

