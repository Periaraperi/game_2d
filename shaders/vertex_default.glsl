#version 330 core
layout (location=0) in vec2 pos;
layout (location=1) in vec4 color;
layout (location=2) in vec2 tex;

out vec4 c;
out vec2 txc;

uniform mat4 u_mvp;

void main()
{
    txc = tex;
    c = color;
    gl_Position = u_mvp*vec4(pos.xy,0.0f,1.0f);
    //gl_Position = vec4(pos.xy,0.0f,1.0f);
}
