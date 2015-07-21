/*
��@ rest SDK �����h class,
�~�Ӧ� Subject �ӹ�{ observer pattern,
1. �~�Ӧ۳o�� class �����󥲶���@ ResetData()�BPrepareData(), ExecuteResponseData() and Finish()
2. ResetData() �̫�n�]�w bResetDataDone �� true�ABaseAPI::DoWork() �}�Y�ˬd bResetDataDone �� true �~�~��C
3. �p�G�n�� SSL �s�u�APrepareData() ��@�n���w bSSL = true
*/
#pragma once

#include "../cpprestsdk/cpprest/http_client.h" // Rest SDK
#include "Subject.h"

using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features

class BaseAPI : public Subject
{
public:
	BaseAPI();
	void DoWork();
protected:
	//! �~�Ӫ� class �n��@�N�Ҧ� member variable ��l
	virtual void ResetData() = 0;
	//! �ǳƳs�u�һݸ��
	virtual void PrepareData() = 0;
	//! �B�z�s�u�^�ǭ�
	virtual void ExecuteResponseData() = 0;
	//! �q�� observer �s�u����
	virtual void Finish() = 0;

	CString serverName;
	CString formAction;
	CString postData;
	http_response response;
	bool bSSL;
	//! �Ψ��ˬd�O�_�I�s DoWork() �e���� ResetData(). ref: #89681
	bool bResetDataDone;
};