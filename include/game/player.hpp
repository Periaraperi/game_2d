#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.hpp"
#include "quad.hpp"
#include "renderer.hpp"

class Player {
public:

	Player(const glm::vec2& start_pos, const std::unique_ptr<Texture>& sprite_sheet);
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	
	const glm::mat4& get_model();
	void update_pos(const glm::vec2& p);
	const glm::vec2& get_pos();
	void set_moving(bool mv);
	bool is_moving();

	void draw();
	void animate(const glm::vec2& dir, const std::unique_ptr<Texture>& sprite_sheet);

private:
	glm::vec2 pos;
	glm::vec2 scale;
	glm::mat4 model;
	glm::mat4 scale_mat;
	
	std::unique_ptr<Quad> player_quad;
	bool moving;

	int nframes;
	float anim_duration;
	float anim_timer;
	int sprite_id;

	void calculate_model();

};