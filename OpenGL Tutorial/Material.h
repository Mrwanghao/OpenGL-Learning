#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>

struct Material
{
	unsigned int id;
	std::string name;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 texture;

	Material(const char *_mtlFileName);

};
