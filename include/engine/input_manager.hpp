#pragma once

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>

enum Mouse_button {
	LEFT = 0,
	MID,
	RIGHT
};

class Input_Manager {
public:
	static Input_Manager* instance();
	static void release();

	bool key_down(SDL_Scancode key);
	bool key_pressed(SDL_Scancode key);
	bool key_released(SDL_Scancode key);

	bool mouse_down(Mouse_button button);
	bool mouse_pressed(Mouse_button button);
	bool mouse_released(Mouse_button button);

	void update(); // for the mouse
	void update_prev_keyboard_state();

    glm::vec2 mouse_pos();

private:
	static Input_Manager* input_manager;

	const Uint8* keyboard_state;
	Uint8* prev_keyboard_state;
	int len;

	unsigned int mouse_state;
	unsigned int prev_mouse_state;
	int mouse_x;
	int mouse_y;

	Input_Manager();
	~Input_Manager();
};
