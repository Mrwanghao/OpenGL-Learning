#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Window.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace Renderer
{
	class Window;
	GLuint TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

	class Model
	{
	public:
		Model(const std::string &path, bool gamma = false);
		~Model();

		void Draw(const Window &mWindow);

	private:
		std::vector<Texture> textures_loaded;	
		std::vector<Mesh*> meshes;
		std::string directory;
		bool gammaCorrection;
		Shader *mShader;

	private:
		void load_model(std::string const &path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh* processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	
	};
}
