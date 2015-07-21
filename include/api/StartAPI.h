#pragma once
#include "BaseAPI.h"
#include "LeanplumParameters.h"

class StartAPI : public BaseAPI
{
public:
	StartAPI(void);
	~StartAPI(void);
	void ResetData();
	void SetIds(int did, int uid);
	void SetLocale(CString locale);
	bool IsSucceed();
	void SetAppIdForProductionMode(CString appId, CString proId);
	json::value m_responseVariabls;

protected:
	void PrepareData();
	void ExecuteResponseData();
	void Finish();

private:
	int m_deviceId;
	int m_userId;
	bool m_responseSuccess;
	CString m_locale;
	CString m_appId;
	CString m_productionKey;
};

