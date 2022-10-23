#pragma once

#include "renderer.hpp"
#include "input_manager.hpp"
#include "timer.hpp"

#include "quad.hpp"
#include "shader.hpp"

#include "camera2d.hpp"
#include "texture.hpp"

#include "player.hpp"

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

	std::unique_ptr<Shader> default_shader;
	std::unique_ptr<Camera2d> cam;
	std::unique_ptr<Texture> sprite_sheet;

	std::unique_ptr<Player> player;
	std::unique_ptr<Quad> wall;
	std::unique_ptr<Quad> wall2;

	Game();
	~Game();
};