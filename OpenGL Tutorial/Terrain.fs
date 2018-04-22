#version 330 core

out vec4 FragColor;

in vec3 out_pos;

void main()
{
	FragColor = vec4(out_pos, 1.0f);

	
}