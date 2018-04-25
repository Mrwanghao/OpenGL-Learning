#version 330 core

in vec3 out_pos;

out vec4 FragColor;


void main()
{
	if (out_pos.y > 80.0f)
	{
		FragColor = vec4(cos (out_pos.x), out_pos.y / 255.0f, cos (out_pos.z) , 1.0f);
	}
	else
	{
		FragColor = vec4(cos (out_pos.x), 1.0f - out_pos.y / 255.0f, cos (out_pos.z), 1.0f);
	}


	
}