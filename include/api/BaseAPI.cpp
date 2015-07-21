#include "stdafx.h"
#include "BaseAPI.h" // Template Pattern
//#include "UtilityFunction.h"

BaseAPI::BaseAPI()
{
	this->bSSL = false;
	this->response.set_status_code(0);
}

void BaseAPI::DoWork()
{
	// 檢查繼承的 class 是否已經呼叫過 ResetData()
	if (!bResetDataDone) {
		ASSERT(false);
		Finish();
		return;
	}
	bResetDataDone = false;

	try {
		PrepareData();
	} catch (...) {
		ASSERT(false);
		Finish();
		return;
	}

	// 如果沒指定走 http 或 https，就要檢查是否要走 SSL 連線後補上
	int nHttpFound = serverName.Find(_T("http://"));
	int nHttpsFound = serverName.Find(_T("https://"));
	if (0 == nHttpFound || 0 == nHttpsFound) { // 一定要在 url 開頭出現才算是有指定，避免參數中剛好出現 http:// 時誤判
	} else {
		serverName = (bSSL ? _T("https://") : _T("http://")) + serverName;
	}
	if (!formAction.IsEmpty()) {
		serverName += /*_T("/") +*/ formAction;
	}

	CString strLog;
	strLog.Format(_T("serverName: %s"), serverName);
	//CUtilityFunction::LogToFile(BASE_API_LOG, strLog);

	try	{
		// url encoding
		auto urlEncoded = http::uri::encode_uri(serverName.GetBuffer(), uri::components::query);
		// 若是傳入的 urlEncoded 為空字串或是 _T("http://")，http_client constructor 會 crash，因此在最外層包 try catch
		http_client client(urlEncoded);

		client.request(postData.IsEmpty() ? methods::GET : methods::POST, _T(""), postData.GetBuffer(), _T("application/x-www-form-urlencoded"))
		.then([ = ](pplx::task<http_response> taskResponse) {
			// 插入這個 pplx::task 是為了透過 pplx::task::get() 來檢查連線過程中是否有 exception，可參考 pplx::task::get() 說明
			try	{
				http_response response = taskResponse.get();
				if (status_codes::OK == response.status_code()) {
					// 只有連線成功時，response 才會 assign 有意義的資料，也才會呼叫 ParseResponseData()
					this->response = response;
					ExecuteResponseData();
				}
			} catch (const std::exception &excep) {
				CString sWhat = (LPCTSTR)excep.what();
				CString strLog;
				strLog.Format(_T("BaseAPI::DoWork(): %s"), sWhat);
				//CUtilityFunction::LogToFile(BASE_API_LOG, strLog);
				ASSERT(false);
			} catch (...) {
				ASSERT(false);
			}
			// 放這裡，讓連線成功或失敗，都會通知 observers 連線結束
			Finish();
		});

	} catch (const std::exception &excep) {
		CString sWhat = (LPCTSTR)excep.what();
		CString strLog;
		strLog.Format(_T("BaseAPI::DoWork(): %s"), sWhat);
		//CUtilityFunction::LogToFile(BASE_API_LOG, strLog);
		ASSERT(false);
		Finish();
	} catch (...) { // 這行是為了怕上面 catch (const std::exception &excep) 有沒補抓到的 exception
		ASSERT(false);
		Finish();
	}
}