#pragma once
#include <string>
#include "..\Utilities\types.h"

class IKeyboardHandler {
public:
	virtual bool VOnKeyDown(unsigned int const kcode) = 0;
	virtual bool VOnKeyUp(unsigned int const kcode) = 0;
};
class IPointerHandler {
public:
	virtual bool VOnPointerMove(const Point &mousePos) = 0;
	virtual bool VOnPointerButtonDown(const Point &mousePos, const std::string &buttonName) = 0;
	virtual bool VOnPointerButtonUp(const Point &mousePos, const std::string &buttonName) = 0;
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