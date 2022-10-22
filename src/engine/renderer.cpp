#include "renderer.hpp"

#include <iostream>

bool Renderer::initialized = false;
Renderer* Renderer::renderer = nullptr;

Renderer::Renderer()
	:window_width(1600), window_height(900)
{
	initialized = init();
}

Renderer::~Renderer()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Renderer* Renderer::instance()
{
	if (renderer==nullptr) {
		renderer = new Renderer();
	}
	return renderer;
}

void Renderer::release()
{
	delete renderer;
}

bool Renderer::init()
{
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		std::cerr << SDL_GetError() << '\n';
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("PenisRing",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,window_height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (window==nullptr) {
		std::cerr << SDL_GetError() << '\n';
		return false;
	}
	context = SDL_GL_CreateContext(window);
	if (context==nullptr) {
		std::cerr << SDL_GetError() << '\n';
		return false;
	}

	if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
		return false;
	}
	glViewport(0,0,window_width,window_height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

bool Renderer::is_initialised()
{
	return initialized;
}

void Renderer::set_screen_color(const Color& c)
{
	glClearColor(c.r,c.g,c.b,c.a);
}

void Renderer::clear_buffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::swap_buffers()
{
	SDL_GL_SwapWindow(window);
}

int Renderer::get_width()
{
	return window_width;
}

int Renderer::get_height()
{
	return window_height;
}