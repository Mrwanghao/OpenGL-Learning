#version 330 core

in vec3 out_pos;

out vec4 FragColor;


void main()
{
	FragColor = vec4(out_pos.x / 1024.0f, out_pos.y / 255.0f, out_pos.z / 1024.0f, 1.0f);

	
}