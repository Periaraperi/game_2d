#include "game.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

bool Game::running = false;
Game* Game::game = nullptr;

Game::Game()
{
	renderer = Renderer::instance();
	if (Renderer::is_initialised()) {
		running = true;
		timer = Timer::instance();
		input_manager = Input_Manager::instance();

		// set camera (handles view projections)
		int w = renderer->get_width();
		int h = renderer->get_height();
		cam = std::make_unique<Camera2d>(0.0f,(float)w,(float)h,0.0f,w,h);

		default_shader = std::make_unique<Shader>("../../../shaders/vertex_default.glsl", 
												  "../../../shaders/fragment_default.glsl");
		sprite_sheet = std::make_unique<Texture>("../../../assets/player_sprite.png");

		auto start_pos = glm::vec2(renderer->get_width()*0.5f,renderer->get_height()*0.5f);
		player = std::make_unique<Player>(start_pos,sprite_sheet);

	}
}

Game::~Game()
{
	Timer::release();
	Input_Manager::release();
	Renderer::release();
}

Game* Game::instance()
{
	if (game==nullptr) {
		game = new Game();
	}
	return game;
}

void Game::release()
{
	delete game;
}

void Game::run()
{
		
	cam->set_position(player->get_pos());

	// some static object
	auto wall_verts = gen_quad(Color(1.0f,0.2f,0.5f,1.0f));
	std::unique_ptr<Quad> wall = std::make_unique<Quad>(wall_verts);
	glm::mat4 wall_model = glm::translate(glm::mat4(1.0f),glm::vec3(100.0f,200.0f,0.0f))*
						   glm::scale(glm::mat4(1.0f),glm::vec3(500.0f,50.0f,0.0f));

	glm::vec2 dir(0.0f,1.0f);

	default_shader->enable();
	sprite_sheet->bind();

	while (running) {
		timer->tick();
		input_manager->update();

		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type==SDL_QUIT) {
				running = false;
				break;
			}
		}
		float speed = 2.0f;

		while (timer->get_accumulator()>=timer->get_fixed_step()) {
			glm::vec2 mot(0.0f, 0.0f);

			if (input_manager->key_down(SDL_SCANCODE_A) || input_manager->key_down(SDL_SCANCODE_LEFT)) {
				mot.x += -speed;
				dir = glm::vec2(-1.0f,0.0f);
			}
			if (input_manager->key_down(SDL_SCANCODE_D) || input_manager->key_down(SDL_SCANCODE_RIGHT)) {
				mot.x += speed;
				dir = glm::vec2(1.0f,0.0f);
			}
			if (input_manager->key_down(SDL_SCANCODE_W) || input_manager->key_down(SDL_SCANCODE_UP)) {
				mot.y += -speed;
				dir = glm::vec2(0.0f,-1.0f);
			}
			if (input_manager->key_down(SDL_SCANCODE_S) || input_manager->key_down(SDL_SCANCODE_DOWN)) {
				mot.y += speed;
				dir = glm::vec2(0.0f,1.0f);
			}
			if (mot.x != 0.0f || mot.y != 0.0f) {
				mot = speed * (mot / std::sqrt(mot.x * mot.x + mot.y * mot.y));
				player->update_pos(mot);

				cam->set_position(player->get_pos());
			}

			input_manager->update_prev_keyboard_state();
			timer->update_accumulator();
		}

		renderer->set_screen_color({0.5f,0.5f,0.2f,1.0f});
		renderer->clear_buffer();

		default_shader->set_mat4("u_mvp",cam->view_projection()*player->get_model());
		player->animate(dir,sprite_sheet);

		default_shader->set_mat4("u_mvp",cam->view_projection()*wall_model);
		wall->bind();
		wall->draw();

		renderer->swap_buffers();
	}
}


