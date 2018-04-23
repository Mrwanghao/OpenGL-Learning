#include "Window.h"
#include "SimpleRenderer2D.h"
#include "Renderable2D.h"
#include "Texture2D.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Common.h"
#include "Terrain.h"
#include "SkyBox.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "BMPLoader.h"
#include "Terrain.h"

Renderer::Camera mCamera(glm::vec3(0.0f, 0.0f, 3.0f));
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
std::string WINDOW_TITLE = std::string("OpenGL Engine");


int main()
{
	using namespace Renderer;

	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	
	//SkyBox _skybox;
#if 1
	//Model rock_model(std::string("nanosuit/nanosuit.obj"));
	Renderer::Terrain ter;
	ter.loadHeightMap("heightmap.raw");
	ter.setDataToBuffer();
#else
	//Texture2D mTex("texture_01.jpg");
	//Model rock_model(std::string("nanosuit/nanosuit.obj"));
	Renderer::Terrain ter;
	ter.loadHeightMap("heightmap.raw");
	ter.setDataToBuffer();
#endif

	while (!window.closed())
	{
		window.clear();

		//_skybox.draw(window);

#if 1
		//rock_model.Draw(window);
		ter.draw(window);
		
#else 
		//mTex.draw(window);
		//rock_model.Draw(window);
		ter.draw(window);

#endif

		window.update();
		//std::cout << "update" << std::endl;

	}

	
	
	return 0;
}
