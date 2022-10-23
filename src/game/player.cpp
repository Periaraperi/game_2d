#include "player.hpp"

#include "timer.hpp"

Player::Player(const glm::vec2& start_pos, const std::unique_ptr<Texture>& sprite_sheet)
	:pos(start_pos), scale(glm::vec2(64.0f,64.0f)), 
	scale_mat(glm::scale(glm::mat4(1.0f),glm::vec3(scale.x,scale.y,0.0f))), 
	moving(false),
	nframes(2), anim_duration(0.6f), anim_timer(0.0f), sprite_id(0)
{
	calculate_model();
	player_quad = std::make_unique<Quad>();
	auto tex_coords = Renderer::instance()->get_tex_coords(4,0,32,32,sprite_sheet->get_width(),
																	 sprite_sheet->get_height());
	auto qverts = gen_quad(tex_coords);
	player_quad->modify_buffer(qverts);
}

void Player::calculate_model()
{
	model = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x,pos.y,0.0f))*scale_mat;
}

void Player::update_pos(const glm::vec2& p)
{
	pos += p;
	calculate_model();
}

void Player::animate(const glm::vec2& dir, const std::unique_ptr<Texture>& sprite_sheet)
{
	float time_per_frame = anim_duration/nframes;
	anim_timer += Timer::instance()->get_delta();

	if (anim_timer>=time_per_frame) {
		++sprite_id;
		sprite_id %= nframes;
		anim_timer -= time_per_frame;
	}

	std::array<glm::vec2,4> tex_coords;

	if (dir==glm::vec2(1.0f,0.0f)) { // right
		tex_coords = Renderer::instance()->get_tex_coords(sprite_id,0,32,32,
			sprite_sheet->get_width(),
			sprite_sheet->get_height());
	}
	if (dir==glm::vec2(-1.0f,0.0f)) { // left
		tex_coords = Renderer::instance()->get_tex_coords(2+sprite_id,0,32,32,
			sprite_sheet->get_width(),
			sprite_sheet->get_height());
	}
	if (dir==glm::vec2(0.0f,1.0f)) { // down
		tex_coords = Renderer::instance()->get_tex_coords(4+sprite_id,0,32,32,
			sprite_sheet->get_width(),
			sprite_sheet->get_height());
	}
	if (dir==glm::vec2(0.0f,-1.0f)) { // up
		tex_coords = Renderer::instance()->get_tex_coords(6+sprite_id,0,32,32,
			sprite_sheet->get_width(),
			sprite_sheet->get_height());
	}
	auto qverts = gen_quad(tex_coords);
	player_quad->modify_buffer(qverts);
	player_quad->bind();
	player_quad->draw();
}

const glm::mat4& Player::get_model()
{
	return model;
}

const glm::vec2& Player::get_pos()
{
	return pos;
}

void Player::set_moving(bool mv)
{
	moving = mv;
}

bool Player::is_moving()
{
	return moving;
}