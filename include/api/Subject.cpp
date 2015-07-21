#include "stdafx.h"
#include "Subject.h"
#include <algorithm>
using namespace std;


void Subject::AttachObserver(InterfaceObserver *pObserver)
{
	m_listObserver.push_back(pObserver);
}

void Subject::DetachObserver(InterfaceObserver *pObserver)
{
	m_listObserver.erase(std::remove(m_listObserver.begin(), m_listObserver.end(), pObserver), m_listObserver.end());
}

void Subject::NotifyObservers(MessageCode::MESSAGE_CODE messageCode, WPARAM wParam, LPARAM lParam)
{
	for (auto iter = m_listObserver.begin(); iter != m_listObserver.end(); ++iter) {
		if (*iter) {
			(*iter)->Notify(messageCode, wParam, lParam);
		}
	}
}
