#version 330 core

in float out_pos_y;
in vec2 out_texcoord;

out vec4 FragColor;

uniform sampler2D texture00;
uniform sampler2D texture01;

void main()
{
	if (out_pos_y > 140.0f / 255.0f)
	{
		FragColor = texture(texture00, out_texcoord);
	}
	else
	{
		float alpha = out_pos_y / (140.0f / 255.0f);
		FragColor = texture(texture00, out_texcoord) * alpha + texture(texture01, out_texcoord) * (1 - alpha);
	}
	

}