#pragma once
#include "BaseAPI.h"
#include "LeanplumParameters.h"

class StopAPI :	public BaseAPI
{
public:
	StopAPI(void);
	~StopAPI(void);
	void ResetData();
	void SetIds(int did, int uid);
	bool IsSucceed();
	void SetAppIdForProductionMode(CString appId, CString proId);

protected:
	void PrepareData();
	void ExecuteResponseData();
	void Finish();

private:
	int m_deviceId;
	int m_userId;
	bool m_responseSuccess;
	CString m_appId;
	CString m_productionKey;
};

