#pragma once

#include <glm/glm.hpp>

class Camera2d {
public:
	Camera2d(float left, float right, float bottom, float top);
	void set_position(const glm::vec2& p);
	void update_position(const glm::vec2& p);
	const glm::mat4& view_projection();
private:
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 view_proj;

	glm::vec2 pos;

	void calculate_view();
};