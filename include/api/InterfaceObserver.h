#pragma once
#include "MessageCode.h"

class InterfaceObserver
{
public:
	virtual void Notify(MessageCode::MESSAGE_CODE messageCode, WPARAM wParam = NULL, LPARAM lParam = NULL) = 0;

};

