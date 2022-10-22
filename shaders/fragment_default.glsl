#version 330 core

in vec4 c;
in vec2 txc;
out vec4 pixel_color;

uniform sampler2D u_texture;

void main()
{
    pixel_color = c;
	
}

