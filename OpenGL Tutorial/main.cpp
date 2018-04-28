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


int main()
{
	using namespace Renderer;

	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	
	
#if 1

	Collada _collada("dae/test.dae");
#else 
	XMLDocument doc;
	doc.LoadFile("dae/test.dae");
	Collada test_Collada;

	for (XMLElement *iter = doc.RootElement()->FirstChildElement(); iter != nullptr; iter = iter->NextSiblingElement())
	{
		
		if (iter->Value() == std::string("library_geometries"))
		{
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
		else if (iter->Value() == std::string("library_controllers"))
		{
			std::cout << "library_controller : " << std::endl;

			ControllerLibrary _controllerLibrary;

			XMLElement *controllerIter = iter->FirstChildElement();
			if (controllerIter->Value() == std::string("controller"))
			{
				Controller _controller;
				_controller.m_ID = controllerIter->Attribute("id");
				_controller.m_Name = controllerIter->Attribute("name");

				XMLElement *skinIter = controllerIter->FirstChildElement();
				if (skinIter->Value() == std::string("skin"))
				{
					Skin _skin;

					_skin.m_Source = skinIter->Attribute("source");

					for (XMLElement *skinChildIter = skinIter->FirstChildElement(); skinChildIter != nullptr; skinChildIter = skinChildIter->NextSiblingElement())
					{
						if (skinChildIter->Value() == std::string("source"))
						{
							Source _source;
							_source.m_ID = skinChildIter->Attribute("id");

							XMLElement *sourceFirstElement = skinChildIter->FirstChildElement();
							if (sourceFirstElement->Value() == std::string("Name_array"))
							{
								NameArray _nameArray;

								_nameArray.m_ID = sourceFirstElement->Attribute("id");
								_nameArray.m_Count = atoi(sourceFirstElement->Attribute("count"));

								std::stringstream ss(sourceFirstElement->GetText());
								//_nameArray.m_Names = (std::string *)malloc(sizeof(std::string) * _nameArray.m_Count);
								
								std::string temp;
								while (ss >> temp)
								{
									//std::cout << temp << std::endl;
									_nameArray.m_Names.push_back(temp);
									
								}
								_source.m_NameArray = _nameArray;
							}
							else if (sourceFirstElement->Value() == std::string("float_array"))
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

							_skin.m_Sources.push_back(_source);
							
						}
						else if (skinChildIter->Value() == std::string("joints"))
						{
							Joints _joints;

							for (XMLElement *jointsIter = skinChildIter->FirstChildElement(); jointsIter != nullptr; jointsIter = jointsIter->NextSiblingElement())
							{
								if (jointsIter->Value() == std::string("input"))
								{
									Input _input;
									_input.m_Source = jointsIter->Attribute("source");
									_input.m_Semantic = jointsIter->Attribute("semantic");

									_skin.m_Joints.m_Inputs.push_back(_input);
								}
							}

							_skin.m_Joints = _joints;
						}
						else if (skinChildIter->Value() == std::string("vertex_weights"))
						{
							VertexWeights _vertexWeights;
							_vertexWeights.m_Count = atoi(skinChildIter->Attribute("count"));

							for (XMLElement *vertexWeightsIter = skinChildIter->FirstChildElement(); vertexWeightsIter != nullptr; vertexWeightsIter = vertexWeightsIter->NextSiblingElement())
							{
								if (vertexWeightsIter->Value() == std::string("input"))
								{
									Input _input;
									_input.m_Source = vertexWeightsIter->Attribute("source");
									_input.m_Semantic = vertexWeightsIter->Attribute("semantic");
									_input.m_Offset = vertexWeightsIter->Attribute("offset");
									_vertexWeights.m_Inputs.push_back(_input);
								}
								else if (vertexWeightsIter->Value() == std::string("vcount"))
								{
									std::stringstream ss(vertexWeightsIter->GetText());
									unsigned short temp;
									while (ss >> temp)
									{
										//Weight _weight;
										//_weight.m_Bones = temp;
										//
										//_vertexWeights.m.push_back(_weight);
									}
									//std::cout << "weights size = " << _vertexWeights.m_Weights.size()<< std::endl;
								}
								else if (vertexWeightsIter->Value() == std::string("v"))
								{
									//std::stringstream ss(vertexWeightsIter->GetText());
									//unsigned short temp_key, temp_value;
									//for (int i = 0; i < _vertexWeights.m_Weights.size(); i++)
									//{
									//	for (int j = 0; j < _vertexWeights.m_Weights[i].m_Bones; j++)
									//	{
									//		ss >> temp_key >> temp_value;
									//		_vertexWeights.m_Weights[i].m_WeightIndices.push_back(std::pair<unsigned short, unsigned short>(temp_key, temp_value));
									//		
									//		
									//	}
									//	//std::cout << _vertexWeights.m_Weights[i].m_Bones << std::endl;
									//}

									//for (int i = 0; i < 100; i++)
									//{
									//	std::cout << "weight : " << std::endl;
									//	for (int j = 0; j < _vertexWeights.m_Weights[i].m_Bones; j++)
									//	{
									//		std::cout << "        " << _vertexWeights.m_Weights[i].m_WeightIndices[j].first << " : " << _vertexWeights.m_Weights[i].m_WeightIndices[j].second << std::endl;
									//	}
									//	
									//} 
								}
							}


							_skin.m_VertexWeights = _vertexWeights;
						}
						else if (skinChildIter->Value() == std::string("bind_shape_matrix"))
						{
							glm::mat4x4 _bindShapeMatrix;

							std::stringstream ss(skinChildIter->GetText());
							int i = 0;
							float temp;
							while (ss >> temp)
							{
								_bindShapeMatrix[i / 4][i % 4] = temp;
								temp = 0;
								i++;
							}

							_skin.m_BindShapeMatrix = _bindShapeMatrix;
						}
					}

					_controller.m_Skin = _skin;
				}

				test_Collada.m_ControllerLibrary.m_Controller = _controller;
			}
			

			test_Collada.m_ControllerLibrary = _controllerLibrary;

		}
		else if (iter->Value() == std::string("library_animations"))
		{
			int i = 0;
			for (XMLElement *animationIter = iter->FirstChildElement(); animationIter != nullptr; animationIter = animationIter->NextSiblingElement())
			{
				if (animationIter->Value() == std::string("animation"))
				{
					i++;
				}
			}
		}
		else if (iter->Value() == std::string("library_visual_scenes"))
		{
			
		}

	}
	
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

	
#endif

	

	

	while (!window.closed())
	{
		window.clear();

		
		
#if 1
		
		_collada.draw(window); 
#else
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

		//glDrawElements(GL_TRIANGLES, ibo_00->getCount(), GL_UNSIGNED_SHORT, test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[0].m_Ps_position.m_Indices);
		//glDrawElements(GL_TRIANGLES, ibo_01->getCount(), GL_UNSIGNED_SHORT, test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[1].m_Ps_position.m_Indices);
		//glDrawElements(GL_TRIANGLES, ibo_02->getCount(), GL_UNSIGNED_SHORT, test_Collada.m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[2].m_Ps_position.m_Indices);

		shader->disable();
		vbo->disable();
		vao->disable();
#endif 



		window.update();
		

	}

	
	return 0;
}
#endif 
