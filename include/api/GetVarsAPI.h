#pragma once
#include "BaseAPI.h"
#include "LeanplumParameters.h"

class GetVarsAPI : public BaseAPI
{
public:
	GetVarsAPI(void);
	~GetVarsAPI(void);
	void ResetData();
	void SetIds(int did, int uid);
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
	CString m_responseMessage;
	CString m_appId;
	CString m_productionKey;
	int m_responseNumber;
};

