#include "Material.h"

Material::Material(const char *_mtlFileName)
	:
	id(-1),
	name(_mtlFileName),
	ambient(glm::vec3(0.4f, 0.4f, 0.4f)),
	diffuse(glm::vec3(0.6f, 0.6f, 0.6f)),
	specular(glm::vec3(0.0f, 0.0f, 0.0f)),
	texture(glm::vec4(-1.0f, -1.0f, -1.0f, -1.0f))
{

}