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
#include "Collada/Collada.h"

using namespace tinyxml2;

Renderer::Camera mCamera(glm::vec3(0.0f, 0.0f, 3.0f));
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
std::string WINDOW_TITLE = std::string("OpenGL Engine");


int main()
{
	using namespace Renderer;

	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	

	XMLDocument doc;
	doc.LoadFile("dae/test.dae");
	Collada test_Collada;

	for (XMLElement *iter = doc.RootElement()->FirstChildElement(); iter != nullptr; iter = iter->NextSiblingElement())
	{
		//std::cout << iter->Value() << std::endl;

		if (iter->Value() == std::string("library_geometries"))
		{
			std::cout << iter->Value() << std::endl;
			GeometryLibrary _geometryLibrary;
			
			XMLElement *geometryElement = iter->FirstChildElement();
			Geometry _geometry;
			_geometry.m_ID = geometryElement->Attribute("id");
			_geometry.m_Name = geometryElement->Attribute("name");

			ColladaMesh _colladaMesh;

			XMLElement *meshElement = geometryElement->FirstChildElement();
			for (XMLElement *iter = meshElement->FirstChildElement(); iter != nullptr; iter = iter->NextSiblingElement())
			{
				if (iter->Value() == std::string("source"))
				{
					Source _source;
					_source.m_ID = iter->Attribute("id");
					
					XMLElement *sourceFirstElement = iter->FirstChildElement();
					if (sourceFirstElement->Value() == std::string("float_array"))
					{
						FloatArray _floatArray;

						_floatArray.m_ID = sourceFirstElement->Attribute("id");
						_floatArray.m_Count = atoi(sourceFirstElement->Attribute("count"));
						
						std::stringstream ss(sourceFirstElement->GetText());
						_floatArray.m_Floats = (float *)malloc(sizeof(float) * _floatArray.m_Count);
						int i = 0;
						while (ss >> _floatArray.m_Floats[i])
						{
							i++;
						}

						_source.m_FloatArray = _floatArray;
					}
					
					
					XMLElement *sourceSecondElement = iter->NextSiblingElement();
					if (sourceSecondElement->Value() == std::string("technique_common"))
					{
						TechniqueCommon _techniqueCommon;
						
						XMLElement *accessorElement = sourceSecondElement->FirstChildElement();
						Accessor _accessor;
						_accessor.m_Count = atoi(accessorElement->Attribute("count"));
						_accessor.m_Stride = atoi(accessorElement->Attribute("stride"));
						_accessor.m_Source = accessorElement->Attribute("source");

						for (XMLElement *iter = accessorElement->FirstChildElement(); iter != nullptr; iter = iter->NextSiblingElement())
						{
							if (iter->Value() == std::string("param"))
							{
								Param _param;
								_param.m_Name = iter->Attribute("name");
								_param.m_Type = iter->Attribute("type");
								_accessor.m_Params.push_back(_param);
							}
						}

						_techniqueCommon.m_Accessor = _accessor;

						_source.m_TechniqueCommon = _techniqueCommon;
					}

					_colladaMesh.m_Sources.push_back(_source);
				}
				else if (iter->Value() == std::string("vertices"))
				{
					Vertices _vertices;
					_vertices.m_ID = iter->Attribute("id");

					for (XMLElement *verticesIter = iter->FirstChildElement(); verticesIter != nullptr; verticesIter = verticesIter->NextSiblingElement())
					{
						Input _input;
						_input.m_Source = verticesIter->Attribute("source");
						_input.m_Semantic = verticesIter->Attribute("semantic");
						_vertices.m_Inputs.push_back(_input);
					}

					_colladaMesh.m_Vertices = _vertices;
				}
				else if (iter->Value() == std::string("lines"))
				{
					Lines _lines;

					_lines.m_Count = atoi(iter->Attribute("count"));

					for (XMLElement *linesIter = iter->FirstChildElement(); linesIter != nullptr; linesIter = linesIter->NextSiblingElement())
					{
						if (linesIter->Value() == std::string("input"))
						{
							Input _input;
							_input.m_Source = linesIter->Attribute("source");
							_input.m_Semantic = linesIter->Attribute("semantic");
							_input.m_Offset = linesIter->Attribute("offset");
							
							_lines.m_Inputs.push_back(_input);
						}
						else if (linesIter->Value() == std::string("p"))
						{
							P _p;
							_p.m_Count = _lines.m_Count * 2;
							std::stringstream ss(linesIter->GetText());
							_p.m_Indices = (unsigned short*) malloc(sizeof(unsigned short) * _p.m_Count);
							
							int i = 0;
							while (ss >> _p.m_Indices[i])
							{
								i++;
							}
							
							
							_lines.m_P = _p;
						}
					}

					_colladaMesh.m_Lines = _lines;
				}
				else if (iter->Value() == std::string("polylist"))
				{
					Polylist _polylist;
					_polylist.m_Count = atoi(iter->Attribute("count"));
					_polylist.m_Material = iter->Attribute("material");

					for (XMLElement *polylistIter = iter->FirstChildElement(); polylistIter != nullptr; polylistIter = polylistIter->NextSiblingElement())
					{
						if (polylistIter->Value() == std::string("input"))
						{
							Input _input;
							_input.m_Source = polylistIter->Attribute("source");
							_input.m_Semantic = polylistIter->Attribute("semantic");
							_input.m_Offset = polylistIter->Attribute("offset");
							if (polylistIter->BoolAttribute("set"))
							{
								_input.m_Set = polylistIter->Attribute("set");
							}
							_polylist.m_Inputs.push_back(_input);
						}
						else if(polylistIter->Value() == std::string("vcount"))
						{
							std::stringstream ss(polylistIter->GetText());
							int vcount;
							ss >> vcount;
							
						}
						else if (polylistIter->Value() == std::string("p"))
						{
							P _p_00;
							P _p_01;
							P _p_02;
							_p_00.m_Count = _polylist.m_Count * 3;
							_p_01.m_Count = _polylist.m_Count * 3;
							_p_02.m_Count = _polylist.m_Count * 3;
							
							std::stringstream ss(polylistIter->GetText());

							
							_p_00.m_Indices = (unsigned short*)malloc(sizeof(unsigned short) * _p_00.m_Count);
							std::cout << "pp_00------" << _p_00.m_Count << std::endl;				   
							_p_01.m_Indices = (unsigned short*)malloc(sizeof(unsigned short) * _p_01.m_Count);
							_p_02.m_Indices = (unsigned short*)malloc(sizeof(unsigned short) * _p_02.m_Count);


							int i = 0;

							float temp;
							while (ss >> temp)
							{
								if (i % 3 == 0)
								{
									_p_00.m_Indices[i / 3] = temp;
				
								}
								else if (i % 3 == 1)
								{
									_p_01.m_Indices[i / 3] = temp;
									
								}
								else if (i % 3 == 2)
								{
									_p_02.m_Indices[i / 3] = temp;
									
								}

								i++;
							}
							std::cout << "pp_00 :" << _p_00.m_Count<< std::endl;
							std::cout << _p_01.m_Count << std::endl;
							std::cout << _p_02.m_Count << std::endl;

							_polylist.m_Ps_position = _p_00;
							_polylist.m_Ps_normals = _p_01;
							_polylist.m_Ps_texcoords = _p_02;
							
						}
					}

					_colladaMesh.m_Polylists.push_back(_polylist);
				}
			}


			_geometry.m_Mesh = _colladaMesh;
			_geometryLibrary.m_Geometry = _geometry;
			test_Collada.m_GeometryLibrary = _geometryLibrary;
		}


	}
	

	std::cout << "collada data:" << test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[1].m_Ps_position.m_Count << std::endl;

	VertexArray *vao = new VertexArray;
	Buffer *vbo = new Buffer(
		test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Sources[0].m_FloatArray.m_Floats, 
		test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Sources[0].m_FloatArray.m_Count, 
		3);
	vao->addBuffer(vbo, 0);
	IndexBuffer *ibo_00 = new IndexBuffer(test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[0].m_Ps_position.m_Indices, test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[0].m_Ps_position.m_Count);
	IndexBuffer *ibo_01 = new IndexBuffer(test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[1].m_Ps_position.m_Indices, test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[1].m_Ps_position.m_Count);
	IndexBuffer *ibo_02 = new IndexBuffer(test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[2].m_Ps_position.m_Indices, test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[2].m_Ps_position.m_Count);

	Shader *shader = new Shader("Terrain.vs", "Terrain.fs");

	//SkyBox _skybox;
#if 1
	//Model rock_model(std::string("nanosuit/nanosuit.obj"));
	//Renderer::Terrain ter;
	//ter.loadHeightMap("heightmap.raw");
	//ter.setDataToBuffer();
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

		vao->enable();
		vbo->enable();
		
		shader->enable();

		glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom), (float)window.mWidth / (float)window.mHeight, 0.1f, 10000.0f);
		shader->setMat4("projection", projection);

		glm::mat4 view = mCamera.GetViewMatrix();
		shader->setMat4("view", view);

		glm::mat4 model = glm::mat4(0.000001f);
		shader->setMat4("model", model);
		
		glDrawElements(GL_TRIANGLES, ibo_00->getCount(), GL_UNSIGNED_SHORT, test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[0].m_Ps_position.m_Indices);
		glDrawElements(GL_TRIANGLES, ibo_01->getCount(), GL_UNSIGNED_SHORT, test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[1].m_Ps_position.m_Indices);
		glDrawElements(GL_TRIANGLES, ibo_02->getCount(), GL_UNSIGNED_SHORT, test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[2].m_Ps_position.m_Indices);

		shader->disable();
		vbo->disable();
		vao->disable();

#if 1
		//rock_model.Draw(window);
		//ter.draw(window);
		
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
#endif 
