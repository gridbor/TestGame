#version 460

out vec4 frag_color;

in vec2 v_textureCoord;

uniform sampler2D u_texture;

void main()
{
	vec4 color = texture(u_texture, v_textureCoord);
	if (color.a < 0.05f) {
		discard;
	}
	frag_color = color;
}
