
#include "InputManager.h"

#include <iostream>

namespace Input
{
	InputManager::InputManager(SDL_Window& window)
		:m_window(window)
	{

	}

	void InputManager::RegisterKeyBinding(const std::string& KeyEventName, InputControl inputInfo)
	{
		// add the information to the controlmap
		mControlMap[KeyEventName] = inputInfo;

		// default the keybinding to being up and to ensure it's registered in our state maps aswell
		// check if it's a keyboard key or a mouse button first
		if (inputInfo.inputType == KeyboardInput)
		{
			m_currentKeyState[inputInfo.keyCode] = false;
			m_previousKeyState[inputInfo.keyCode] = false;
		}
		else
		{
			m_currentMouseState[inputInfo.mouseButton] = false;
			m_previousMouseState[inputInfo.mouseButton] = false;
		}

	}

	void InputManager::UpdateKeys(const SDL_Event& event)
	{
		// set the new key/button state depending on which action was recorded in the event
		switch (static_cast<SDL_EventType>(event.type))
		{
		case SDL_KEYDOWN:
			m_currentKeyState[event.key.keysym.sym] = true;
			break;

		case SDL_KEYUP:
			m_currentKeyState[event.key.keysym.sym] = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			m_currentMouseState[event.button.button] = true;
			break;

		case SDL_MOUSEBUTTONUP:
			m_currentMouseState[event.button.button] = true;
			break;
		default:
			std::cout << "Unhandled input event of type: " << event.type << std::endl;
			break;
		}
	}

	void InputManager::Update()
	{
		// set the previous key/button state to the current one
		m_previousKeyState = m_currentKeyState;
		m_previousMouseState = m_currentMouseState;
	}

	bool InputManager::GetKeyDown(const std::string& KeyEventName)
	{
		// first check if it's a mouse button or a keyboard key we're checking for
		if (mControlMap[KeyEventName].inputType == KeyboardInput)
		{
			// next return if the key is down
			return m_currentKeyState[mControlMap[KeyEventName].keyCode];
		}

		else if (mControlMap[KeyEventName].inputType == MouseInput)
		{
			// next return if the button is down
			return m_currentMouseState[mControlMap[KeyEventName].mouseButton];
		}

		return false;
	}

	bool InputManager::GetKeyUp(const std::string& KeyEventName)
	{
		// first check if it's a mouse button or a keyboard key we're checking for
		if (mControlMap[KeyEventName].inputType == KeyboardInput)
		{
			// next return the opposite of the key state
			return !m_currentKeyState[mControlMap[KeyEventName].keyCode];
		}

		else if (mControlMap[KeyEventName].inputType == MouseInput)
		{
			// next return opposite of the button state
			return !m_currentMouseState[mControlMap[KeyEventName].mouseButton];
		}
	}

	bool InputManager::GetKeyPressed(const std::string& KeyEventName)
	{
		// first check if it's a mouse button or a keyboard key we're checking for
		if (mControlMap[KeyEventName].inputType == KeyboardInput)
		{
			// next return true if the key is currently down but was up last frame
			return (m_currentKeyState[mControlMap[KeyEventName].keyCode] && !m_previousKeyState[mControlMap[KeyEventName].keyCode]);
		}

		else if (mControlMap[KeyEventName].inputType == MouseInput)
		{
			// next return true if the mouse button is currently down but was up last frame
			return (m_currentMouseState[mControlMap[KeyEventName].mouseButton] && !m_previousMouseState[mControlMap[KeyEventName].mouseButton]);
		}
	}

	bool InputManager::GetKeyReleased(const std::string& KeyEventName)
	{
		// first check if it's a mouse button or a keyboard key we're checking for
		if (mControlMap[KeyEventName].inputType == KeyboardInput)
		{
			// next return true if the key is currently up but was up last frame
			return (!m_currentKeyState[mControlMap[KeyEventName].keyCode] && m_previousKeyState[mControlMap[KeyEventName].keyCode]);
		}

		else if (mControlMap[KeyEventName].inputType == MouseInput)
		{
			// next return true if the mouse button is currently up but was up last frame
			return (!m_currentMouseState[mControlMap[KeyEventName].mouseButton] && m_previousMouseState[mControlMap[KeyEventName].mouseButton]);
		}
	}

	MousePoint InputManager::GetMousePosition()
	{
		int x;
		int y;

		SDL_GetMouseState(&x, &y);

		MousePoint mouse = { x, y };

		return mouse;
	}

	void InputManager::SetMousePosition(int x, int y)
	{
		SDL_WarpMouseInWindow(&m_window, x, y);
	}
}