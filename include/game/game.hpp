#pragma once

#include "renderer.hpp"
#include "input_manager.hpp"
#include "timer.hpp"

#include "quad.hpp"
#include "shader.hpp"

#include "camera2d.hpp"

class Game {
public:
	static Game* instance();
	static void release();

	void run();

private:
	static Game* game;
	static bool running;

	Renderer* renderer;
	Input_Manager* input_manager;
	Timer* timer;

	std::unique_ptr<Quad> player;
	std::unique_ptr<Shader> default_shader;
	std::unique_ptr<Camera2d> cam;

	Game();
	~Game();
};