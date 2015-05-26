/*
¹ê§@ observer pattern
*/
#pragma once
#include <vector>
#include <list>
#include "MessageCode.h"
#include "InterfaceObserver.h"

class Subject
{
private:
	std::vector<InterfaceObserver*> m_listObserver;

public:
	void AttachObserver(InterfaceObserver *pObserver);
	void DetachObserver(InterfaceObserver *pObserver);
	void NotifyObservers(MessageCode::MESSAGE_CODE messageCode, WPARAM wParam = NULL, LPARAM lParam = NULL);
};