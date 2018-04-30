#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexcoord;

out float out_pos_y;
out vec2 out_texcoord;


uniform mat4 projection = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

void main()
{
	out_pos_y = aPos.y / 255.0f;
	out_texcoord = aTexcoord;
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}