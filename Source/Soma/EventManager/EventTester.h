#pragma once

#include "Events.h"

// Class to test mouse click event for lab 7

class EventTester
{
public:

	int buttonId;
	std::wstring text;
	LPCWSTR lpcText;

	EventTester(void) {
		buttonId = 999;
		text = _T("Click the mouse.");
		lpcText = text.c_str();
	}
	~EventTester(void) {
		EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate(this, &EventTester::MouseClickDelegate);

		IEventManager::Get()->VRemoveListener(delegateFunc, EvtData_MouseClick::sk_EventType);
	}

	void MouseClickDelegate(IEventDataPtr pEventData)
	{
		std::shared_ptr<EvtData_MouseClick> pCastEventData = 
			std::static_pointer_cast<EvtData_MouseClick>(pEventData);

		SetButtonId(pCastEventData->GetButtonId());
		switch (buttonId)
		{
		case 0:
			text = _T("Left Click");
			break;
		case 1:
			text = _T("Middle Click");
			break;
		case 2:
			text = _T("Right Click");
			break;
		}
		lpcText = text.c_str();
	}

	void SetButtonId(int id) {
		buttonId = id;
	}

	LPCWSTR GetButtonName(void)
	{
		return lpcText;
	}

	void Init(void)
	{
		EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate(this, &EventTester::MouseClickDelegate);

		IEventManager::Get()->VAddListener(delegateFunc, EvtData_MouseClick::sk_EventType);
	}
};