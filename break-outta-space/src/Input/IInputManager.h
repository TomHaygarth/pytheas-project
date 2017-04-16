
#pragma once

#include <SDL.h>
#include <string>

namespace Input
{
	/// <summary> A struct that holds the mosue position
	struct MousePoint
	{
		int x;
		int y;
	};

	enum InputType
	{
		KeyboardInput,
		MouseInput,
		JoystickInput
	};

	struct InputControl
	{
		InputType inputType;
		int keyCode;
		unsigned char mouseButton;
	};

	class IInputManager
	{
	public:
		virtual void RegisterKeyBinding(const std::string& KeyEventName, InputControl inputInfo) = 0;
		virtual void UpdateKeys(const SDL_Event& event) = 0;
		virtual void Update() = 0;
		virtual bool GetKeyDown(const std::string& KeyEventName) = 0;
		virtual bool GetKeyUp(const std::string& KeyEventName) = 0;
		virtual bool GetKeyPressed(const std::string& KeyEventName) = 0;
		virtual bool GetKeyReleased(const std::string& KeyEventName) = 0;
		virtual void SetMouseSensitvity(const float& sensitivity) = 0;
		virtual const float& GetMouseSensitivity() = 0;
		virtual int GetMouseWheelScroll() = 0;
		virtual MousePoint GetMousePosition() = 0;
		virtual void SetMousePosition(int x, int y) = 0;
	};
}