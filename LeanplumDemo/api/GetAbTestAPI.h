#pragma once
#include "BaseAPI.h"
#include "LeanplumParameters.h"

class GetAbTestAPI : public BaseAPI
{
public:
	GetAbTestAPI(void);
	~GetAbTestAPI(void);
	void ResetData();
	void SetAbTestId(INT64 id);
	bool IsSucceed();
	void SetAppIdForContentReadonlyMode(CString appId, CString croId);

protected:
	void PrepareData();
	void ExecuteResponseData();
	void Finish();

private:
	INT64 m_abTestId;
	bool m_responseSuccess;
	AbTestInfo m_abTestInfo;
	CString m_appId;
	CString m_contentReadonlyKey;
};

