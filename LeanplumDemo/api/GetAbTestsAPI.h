#pragma once
#include "BaseAPI.h"
#include "LeanplumParameters.h"

class GetAbTestsAPI : public BaseAPI
{
public:
	GetAbTestsAPI(void);
	~GetAbTestsAPI(void);
	void ResetData();
	bool IsSucceed();
	void SetAppIdForContentReadonlyMode(CString appId, CString croId);
	std::vector<AbTestInfo> GetAbTestsInfo();

protected:
	void PrepareData();
	void ExecuteResponseData();
	void Finish();

private:
	bool m_responseSuccess;
	std::vector<AbTestInfo> m_abTestInfos;
	CString m_appId;
	CString m_contentReadonlyKey;
};

