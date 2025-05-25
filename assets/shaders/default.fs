#version 460

out vec4 frag_color;

in vec4 v_color;

void main()
{
	if (v_color.a < 0.05f) {
		discard;
	}
	frag_color = v_color;
}
