#include "input_manager.hpp"

Input_Manager* Input_Manager::input_manager = nullptr;

Input_Manager* Input_Manager::instance()
{
	if(input_manager==nullptr)
		input_manager = new Input_Manager();
	return input_manager;
}

void Input_Manager::release()
{
	delete input_manager;
	input_manager = nullptr;
}

Input_Manager::Input_Manager()
{
	keyboard_state = SDL_GetKeyboardState(&len);
	prev_keyboard_state = new Uint8[len];
	memcpy(prev_keyboard_state,keyboard_state,len);
	mouse_state = SDL_GetMouseState(&mouse_x,&mouse_y);
	prev_mouse_state = mouse_state;
}

Input_Manager::~Input_Manager()
{
	delete[] prev_keyboard_state;
	prev_keyboard_state = nullptr;
}

void Input_Manager::update()
{
	mouse_state = SDL_GetMouseState(&mouse_x,&mouse_y);
}

void Input_Manager::update_prev_keyboard_state()
{
	memcpy(prev_keyboard_state,keyboard_state,len);
	prev_mouse_state = mouse_state;
}

glm::vec2 Input_Manager::mouse_pos() 
{
	return glm::vec2(mouse_x,mouse_y);
}

bool Input_Manager::key_down(SDL_Scancode key)
{
	return (keyboard_state[key]!=0);
}

bool Input_Manager::key_pressed(SDL_Scancode key)
{
	return (keyboard_state[key]!=0 && prev_keyboard_state[key]==0);
}

bool Input_Manager::key_released(SDL_Scancode key)
{
	return (keyboard_state[key]==0 && prev_keyboard_state[key]!=0);
}

bool Input_Manager::mouse_down(Mouse_button button)
{
	unsigned int mask = 0;
	switch(button) {
	case Mouse_button::LEFT: 
		mask = SDL_BUTTON_LMASK;
		break;
	case Mouse_button::MID: 
		mask = SDL_BUTTON_MMASK;
		break;
	case Mouse_button::RIGHT: 
		mask = SDL_BUTTON_RMASK;
		break;
	}
	return ((mouse_state&mask)!=0);
}

bool Input_Manager::mouse_pressed(Mouse_button button)
{
	unsigned int mask = 0;
	switch(button) {
	case Mouse_button::LEFT: 
		mask = SDL_BUTTON_LMASK;
		break;
	case Mouse_button::MID: 
		mask = SDL_BUTTON_MMASK;
		break;
	case Mouse_button::RIGHT: 
		mask = SDL_BUTTON_RMASK;
		break;
	}
	return ((mouse_state&mask)!=0 && (prev_mouse_state&mask)==0);
}

bool Input_Manager::mouse_released(Mouse_button button)
{
	unsigned int mask = 0;
	switch(button) {
	case Mouse_button::LEFT: 
		mask = SDL_BUTTON_LMASK;
		break;
	case Mouse_button::MID: 
		mask = SDL_BUTTON_MMASK;
		break;
	case Mouse_button::RIGHT: 
		mask = SDL_BUTTON_RMASK;
		break;
	}
	return ((mouse_state&mask)==0 && (prev_mouse_state&mask)!=0);
}
