#pragma once
#include "SomaStd.h";

class IKeyboardHandler {
public:
	virtual bool VOnKeyDown(unsigned int const kcode) = 0;
	virtual bool VOnKeyUp(unsigned int const kcode) = 0;
};
class IPointerHandler {
public:
	virtual bool VOnPointerMove(const Point &mousePos) = 0;
	virtual bool VOnPointerButtonDown(const Point &mousePos, const std::wstring &buttonName) = 0;
	virtual bool VOnPointerButtonUp(const Point &mousePos, const std::wstring &buttonName) = 0;
	virtual int VGetPointerRadius() = 0;
};
class IJoystickHandler {
	const std::string (&buttonName) = 0;
	virtual bool VOnButtonDown(const std::string &buttonName, int const pressure) = 0;
	virtual bool VOnButtonUp(const std::string &buttonName) = 0;
	virtual bool VOnJoystick(float const x, float const y) = 0;
};
class IGamepadHandler {
	virtual bool VOnTrigger(const std::string &triggerName, float const pressure) = 0;
	virtual bool VOnButtonDown(const std::string &buttonName, int const pressure) = 0;
	virtual bool VOnButtonUp(const std::string &buttonName) = 0;
	virtual bool VOnDirectionalPad(const std::string &direction) = 0;
	virtual bool VOnThumbstick(const std::string &stickName, float const x, float const y) = 0;
};

class TempMouseHandler : public IPointerHandler
{
public:
	LPCWSTR x;
	LPCWSTR y;
	std::wstring strX;
	std::wstring strY;
	std::wstring strButton;
	LPCWSTR button;
	TempMouseHandler() {
		x = _T("0");
		y = _T("0");
		button = _T("Click Mouse.");
	};

	virtual bool VOnPointerMove(const Point &mousePos)
	{
		strX = std::to_wstring(mousePos.x);
		strY = std::to_wstring(mousePos.y);
		x = strX.c_str();
		y = strY.c_str();

		return true;
	}
	virtual bool VOnPointerButtonDown(const Point &mousePos, const std::wstring &buttonName)
	{
		strButton = buttonName;
		button = strButton.c_str();

		strX = std::to_wstring(mousePos.x);
		strY = std::to_wstring(mousePos.y);
		x = strX.c_str();
		y = strY.c_str();

		return true;
	}
	virtual bool VOnPointerButtonUp(const Point &mousePos, const std::wstring &buttonName) { return true; }
	virtual int VGetPointerRadius() { return 0; }
};

class TempKeyHandler : public IKeyboardHandler
{
public:
	LPCWSTR key;
	std::wstring strKey;
	TempKeyHandler() {
		key = _T("Type a key.");
	};

	void OnCharInput(std::wstring &input)
	{
		strKey = input;
		key = strKey.c_str();
	}
	virtual bool VOnKeyDown(unsigned int const kcode) { return true; }
	virtual bool VOnKeyUp(unsigned int const kcode) { return true; }
};