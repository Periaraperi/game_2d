#include "game.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
		cam = std::make_unique<Camera2d>(0.0f,(float)renderer->get_width(),(float)renderer->get_height(),0.0f);

		default_shader = std::make_unique<Shader>("../../../shaders/vertex_default.glsl", 
												  "../../../shaders/fragment_default.glsl");
		
		player = std::make_unique<Quad>(); // default quad
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
	glm::mat4 quad_model = glm::scale(glm::mat4(1.0f),glm::vec3(100.0f,100.0f,0.0f));

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

			if (input_manager->key_down(SDL_SCANCODE_A)) {
				mot.x += speed;
			}
			if (input_manager->key_down(SDL_SCANCODE_D)) {
				mot.x += -speed;
			}
			if (input_manager->key_down(SDL_SCANCODE_W)) {
				mot.y += speed;
			}
			if (input_manager->key_down(SDL_SCANCODE_S)) {
				mot.y += -speed;
			}
			if (mot.x != 0.0f || mot.y != 0.0f) {
				mot = speed * (mot / std::sqrt(mot.x * mot.x + mot.y * mot.y));

				cam->update_position(mot);
			}
			input_manager->update_prev_keyboard_state();
			timer->update_accumulator();
		}

		renderer->set_screen_color({0.5f,0.5f,0.2f,1.0f});
		renderer->clear_buffer();

		default_shader->enable();
		default_shader->set_mat4("u_mvp",cam->view_projection()*quad_model);
		player->bind();
		player->draw();

		renderer->swap_buffers();
	}
}


