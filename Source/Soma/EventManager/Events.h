#pragma once
#include "EventManager.h"

class EvtData_MouseClick : public BaseEventData
{
	int m_buttonId;
public:
	static const EventType sk_EventType;
	explicit EvtData_MouseClick(int buttonId) : m_buttonId(buttonId) { }
	explicit EvtData_MouseClick(std::istrstream& in) {
		in >> m_buttonId;
	}
	virtual const EventType& VGetEventType(void) const {
		return sk_EventType;
	}
	virtual IEventDataPtr VCopy(void) const {
		// reminder to define macro for debug new
		return IEventDataPtr(new EvtData_MouseClick(m_buttonId));
	}
	virtual void VSerialize(std::ostrstream &out) const {
		out << m_buttonId;
	}
	virtual void VDeserialize(std::istrstream &in) {
		in >> m_buttonId;
	}
	virtual const char* GetName(void) const {
		return "EvtData_MouseClick";
	}
	int GetButtonId(void) const { return m_buttonId; }
};