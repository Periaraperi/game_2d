#include "camera2d.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera2d::Camera2d(float left, float right, float bottom, float top)
	:projection(glm::ortho(left,right,bottom,top,-1.0f,1.0f)), view(glm::mat4(1.0f))
{
	view_proj = projection*view;
}

void Camera2d::set_position(const glm::vec2& p)
{
	pos = p;
	calculate_view();
}

void Camera2d::update_position(const glm::vec2& p)
{
	pos += p;
	calculate_view();
}

void Camera2d::calculate_view()
{
	view = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(pos.x,pos.y,0.0f)));
	view_proj = projection*view;
}

const glm::mat4& Camera2d::view_projection()
{
	return view_proj;
}