#pragma once

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include <unordered_map>
#include <memory>
#include <array>

#include "shader.hpp"
#include "color.hpp"

class Renderer {
public:
	static Renderer* instance();
	static void release();
	static bool is_initialised();

	void set_screen_color(const Color& c);
	void clear_buffer();
	void swap_buffers();

	std::array<glm::vec2,4> get_tex_coords(float x, float y, 
										   float block_width, float block_height, 
										   float sheet_width, float sheet_height);

	int get_width();
	int get_height();

private:
	static Renderer* renderer;
	static bool initialized;

	SDL_Window* window;
	SDL_GLContext context;
	int window_width;
	int window_height;

	bool init();
	Renderer();
	~Renderer();
};