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
	// �ˬd�~�Ӫ� class �O�_�w�g�I�s�L ResetData()
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

	// �p�G�S���w�� http �� https�A�N�n�ˬd�O�_�n�� SSL �s�u��ɤW
	int nHttpFound = serverName.Find(_T("http://"));
	int nHttpsFound = serverName.Find(_T("https://"));
	if (0 == nHttpFound || 0 == nHttpsFound) { // �@�w�n�b url �}�Y�X�{�~��O�����w�A�קK�ѼƤ���n�X�{ http:// �ɻ~�P
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
		// �Y�O�ǤJ�� urlEncoded ���Ŧr��άO _T("http://")�Ahttp_client constructor �| crash�A�]���b�̥~�h�] try catch
		http_client client(urlEncoded);

		client.request(postData.IsEmpty() ? methods::GET : methods::POST, _T(""), postData.GetBuffer(), _T("application/x-www-form-urlencoded"))
		.then([ = ](pplx::task<http_response> taskResponse) {
			// ���J�o�� pplx::task �O���F�z�L pplx::task::get() ���ˬd�s�u�L�{���O�_�� exception�A�i�Ѧ� pplx::task::get() ����
			try	{
				http_response response = taskResponse.get();
				if (status_codes::OK == response.status_code()) {
					// �u���s�u���\�ɡAresponse �~�| assign ���N�q����ơA�]�~�|�I�s ParseResponseData()
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
			// ��o�̡A���s�u���\�Υ��ѡA���|�q�� observers �s�u����
			Finish();
		});

	} catch (const std::exception &excep) {
		CString sWhat = (LPCTSTR)excep.what();
		CString strLog;
		strLog.Format(_T("BaseAPI::DoWork(): %s"), sWhat);
		//CUtilityFunction::LogToFile(BASE_API_LOG, strLog);
		ASSERT(false);
		Finish();
	} catch (...) { // �o��O���F�ȤW�� catch (const std::exception &excep) ���S�ɧ�쪺 exception
		ASSERT(false);
		Finish();
	}
}