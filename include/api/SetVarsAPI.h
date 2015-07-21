#pragma once
#include "BaseAPI.h"
#include "LeanplumParameters.h"
 
class SetVarsAPI : public BaseAPI
{
public:
	SetVarsAPI(void);
	~SetVarsAPI(void);
	void ResetData();
	void SetPostData(CString data);
	bool IsSucceed();
	void SetAppIdForDevelopmentMode(CString appId, CString devId);

protected:
	void PrepareData();
	void ExecuteResponseData();
	void Finish();

private:
	bool m_responseSuccess;
	CString m_postData;
	CString m_appId;
	CString m_developmentKey;
};

