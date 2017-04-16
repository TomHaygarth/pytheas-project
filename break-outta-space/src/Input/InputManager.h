
#pragma once

#include "IInputManager.h"

#include <SDL.h>
#include <map>

namespace Input {
	
	class InputManager : public IInputManager
	{
	public:

		InputManager(SDL_Window& window);

		void RegisterKeyBinding(const std::string& KeyEventName, InputControl inputInfo);

		void UpdateKeys(const SDL_Event& event);

		void Update();

		bool GetKeyDown(const std::string& KeyEventName);

		bool GetKeyUp(const std::string& KeyEventName);

		bool GetKeyPressed(const std::string& KeyEventName);

		bool GetKeyReleased(const std::string& KeyEventName);

		void SetMouseSensitvity(const float& sensitivity) { mMouseSensitivity = sensitivity; }

		const float& GetMouseSensitivity() { return mMouseSensitivity; }

		MousePoint GetMousePosition();

		void SetMousePosition(int x, int y);

	private:

		static InputManager* mInstance;

		std::map<std::string, InputControl> mControlMap;

		std::map<SDL_Keycode, bool> m_currentKeyState;
		std::map<SDL_Keycode, bool> m_previousKeyState;

		std::map<Uint8, bool> m_currentMouseState;
		std::map<Uint8, bool> m_previousMouseState;

		SDL_Window& m_window;
		float mMouseSensitivity;
	};
}