#version 460

layout (location=0) in vec3 a_position;
layout (location=1) in vec2 a_textureCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_textureCoord;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
	v_textureCoord = a_textureCoord;
}
