#if 1



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
#include "tinyxml2/tinyxml2.h"
#include "Collada.h"

using namespace tinyxml2;

Renderer::Camera mCamera(glm::vec3(0.0f, 0.0f, 3.0f));
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
std::string WINDOW_TITLE = std::string("OpenGL Engine");
Renderer::Window mWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);


int main()
{
	using namespace Renderer;


	
	Terrain terrain("heightmap.raw");
	Texture2D texture2d("texture_01.jpg");
	
	while (!mWindow.closed())
	{
		mWindow.clear();

		terrain.draw();
		texture2d.draw();
		

		mWindow.update();
		

	}

	
	return 0;
}
#endif 
