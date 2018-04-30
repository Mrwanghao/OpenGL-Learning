#include "Collada.h"
#include <sstream>
#include <stdio.h>
#include <fstream>
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace tinyxml2;
using namespace Renderer;

extern Renderer::Camera mCamera;
extern Renderer::Window mWindow;

Collada::Collada()
	:
	m_ColladaFileName(""),
	m_VAO(new VertexArray()),
	m_IndicesLength(0),
	m_DOC(new XMLDocument),
	m_Shader(new Shader("collada.vs", "collada.fs"))
{
	
}

Collada::Collada(const char *colladaFileName)
	: 
	m_ColladaFileName(colladaFileName),
	m_VAO(new VertexArray()),
	m_IndicesLength(0),
	m_DOC(new XMLDocument),
	m_Shader(new Shader("collada.vs", "collada.fs"))
{
	readCollada(m_ColladaFileName);
	setDataToBuffer();
}

Collada::~Collada()
{
	if (m_VAO) delete m_VAO; m_VAO = nullptr;
	if (m_IBO) delete m_IBO; m_IBO = nullptr;
	if (m_DOC) delete m_DOC; m_DOC = nullptr;
	if (m_IndicesData) delete m_IndicesData; m_IndicesData = nullptr;
	if (m_Shader) delete m_Shader; m_Shader = nullptr;
	
}

void Collada::setDataToBuffer()
{
	Buffer *vertices_buffer = new Buffer(getVerticesData(), getVerticesLength(), 3);
	m_VAO->addBuffer(vertices_buffer, 0);

}

void Collada::setDataToIndexBuffer(int index)
{
	delete m_IBO;
	m_IBO = nullptr;
	m_IBO = new IndexBuffer(getIndicesDataByIndex(index), getIndicesLengthByIndex(index));
	
}

void Collada::drawPolylist(int index)
{
	setDataToIndexBuffer(index);

	m_VAO->enable();
	m_IBO->enable();

	m_Shader->enable();

	glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom), (float)mWindow.mWidth / (float)mWindow.mHeight, 0.1f, 10000.0f);
	m_Shader->setMat4("projection", projection);

	glm::mat4 view = mCamera.GetViewMatrix();
	m_Shader->setMat4("view", view);

	glm::mat4 model = glm::mat4(0.000001f);
	m_Shader->setMat4("model", model);

	glDrawElements(GL_TRIANGLES, m_IBO->getCount(), GL_UNSIGNED_SHORT, 0);
	m_Shader->disable();

	m_IBO->disable();
	m_VAO->disable();
}

void Collada::updateComputeVertex()
{
	
}

void Collada::draw()
{
	for (int i = 0; i < getPolylistSize(); i++)
	{
		drawPolylist(i);
	}
}


void Collada::readCollada(const char *colladaFileName)
{
	m_DOC->LoadFile(colladaFileName);
	XMLElement *rootElement = m_DOC->RootElement();
	for (XMLElement *element = rootElement->FirstChildElement(); element != nullptr; element = element->NextSiblingElement())
	{
		readLibrary(element);
	}
}


void Collada::readLibrary(XMLElement *element)
{
	if (checkValueIsEqualToKey(element, GEOMETRIESLIBRARY))
	{
		readGeometry(element);
	}
	else if (checkValueIsEqualToKey(element, CONTROLLERLIBRARY))
	{
		readController(element);
	}
	else if (checkValueIsEqualToKey(element, ANIMATIONLIBRARY))
	{
		readAnimations(element);
	}
	
}

Geometry Collada::readGeometry(XMLElement *element)
{
	GeometryLibrary _geometryLibrary;
	Geometry _geometry;
	XMLElement *elementChild = element->FirstChildElement();
	if (checkValueIsEqualToKey(elementChild, GEOMETRY))
	{
		_geometry.m_ID = getAttributeStringValue(elementChild, "id");
		_geometry.m_Name = getAttributeStringValue(elementChild, "name");

		XMLElement *elementGrandson = elementChild->FirstChildElement();
		if (checkValueIsEqualToKey(elementGrandson, MESH))
		{
			_geometry.m_Mesh = readMesh(elementGrandson);
		}

		_geometryLibrary.m_Geometry = _geometry;
	}

	m_GeometryLibrary = _geometryLibrary;
	return _geometry;
}

Controller Collada::readController(tinyxml2::XMLElement * element)
{
	ControllerLibrary _controllerLibrary;
	Controller _controller;
	XMLElement *elementChild = element->FirstChildElement();
	if (checkValueIsEqualToKey(elementChild, CONTROLLER))
	{
		XMLElement *elementGrandson = elementChild->FirstChildElement();
		if (checkValueIsEqualToKey(elementGrandson, SKIN))
		{
			_controller.m_Skin = readSkin(elementGrandson);
		}

	}
	_controllerLibrary.m_Controller = _controller;
	m_ControllerLibrary = _controllerLibrary;
	return _controller;
}

void Collada::readAnimations(tinyxml2::XMLElement * element)
{
	for (XMLElement *elementChild = element->FirstChildElement(); elementChild != nullptr; elementChild = elementChild->NextSiblingElement())
	{
		if (checkValueIsEqualToKey(elementChild, ANIMATION))
		{
			readAnimation(elementChild);
		}
	}
	buildAnimationBoneList();
}

void Collada::readAnimation(tinyxml2::XMLElement * element)
{

	Animation _animation;
	_animation.m_ID = getAttributeStringValue(element, "id");
	
	for (XMLElement *elementChild = element->FirstChildElement(); elementChild != nullptr; elementChild = elementChild->NextSiblingElement())
	{
		if (checkValueIsEqualToKey(elementChild, SOURCE))
		{
			_animation.m_Sources.push_back(readSource(elementChild));
			
		}
		else if (checkValueIsEqualToKey(elementChild, SAMPLER))
		{
			Sampler _sampler;
			_sampler.m_ID = getAttributeStringValue(elementChild, "id");
			for (XMLElement *elementGrandson = elementChild->FirstChildElement(); elementGrandson != nullptr; elementGrandson = elementGrandson->NextSiblingElement())
			{
				if (checkValueIsEqualToKey(elementGrandson, INPUT))
				{
					_animation.m_Sampler.m_Inputs.push_back(readInput(elementGrandson));
				}
			}

			_animation.m_Sampler = _sampler;
			
		}
		else if (checkValueIsEqualToKey(elementChild, CHANNEL))
		{
			Channel _channel;
			_channel.m_Source = getAttributeStringValue(elementChild, "source");
			_channel.m_Target = getAttributeStringValue(elementChild, "target");

			_animation.m_Channel = _channel;
		}
	}

	m_AnimationLibrary.m_BoneAnimations.push_back(_animation);
}

void Collada::buildAnimationBoneList()
{
	
}

void Collada::buildWeightBoneList()
{

}

ColladaMesh Collada::readMesh(tinyxml2::XMLElement * element)
{
	ColladaMesh _colladaMesh;
	for (XMLElement *elementChild = element->FirstChildElement(); elementChild != nullptr; elementChild = elementChild->NextSiblingElement())
	{
		if (checkValueIsEqualToKey(elementChild, SOURCE))
		{
			_colladaMesh.m_Sources.push_back(readSource(elementChild));
		}
		else if (checkValueIsEqualToKey(elementChild, POLYLIST))
		{
			_colladaMesh.m_Polylists.push_back(readPolylist(elementChild));
		}
	}
	return _colladaMesh;
}

VisualScene Collada::readVisualScene(tinyxml2::XMLElement * element)
{
	VisualSceneLibrary _visualSceneLibrary;
	
	XMLElement *elementChild = element->FirstChildElement();
	VisualScene _visualScene;
	
	if (checkValueIsEqualToKey(elementChild, VISUALSCENE))
	{
		_visualScene.m_ID = getAttributeStringValue(elementChild, "id");
		_visualScene.m_Name = getAttributeStringValue(elementChild, "name");

		XMLElement *elementGrandson = elementChild->FirstChildElement();
		_visualScene.m_Nodes.push_back(readNode(elementGrandson));

	}
	m_VisualSceneLibrary = _visualSceneLibrary;
	return _visualScene;
}

Source Collada::readSource(tinyxml2::XMLElement * element)
{
	Source _source;
	_source.m_ID = getAttributeStringValue(element, "id");
	XMLElement *elementChild = element->FirstChildElement();
	if (checkValueIsEqualToKey(elementChild, FLOATARRAY))
	{
		_source.m_FloatArray = readFloatArray(elementChild);

	}
	else if (checkValueIsEqualToKey(elementChild, NAMEARRAY))
	{
		_source.m_NameArray = readNameArray(elementChild);

	}

	//technique common
	XMLElement *elementBrother = elementChild->NextSiblingElement();
	if (checkValueIsEqualToKey(elementBrother, TECHNIQUE_COMMON))
	{
		TechniqueCommon _techniqueCommon;
		
		XMLElement *elementChild = elementBrother->FirstChildElement();
		if (checkValueIsEqualToKey(elementChild, ACCESSOR))
		{
			_techniqueCommon.m_Accessor = readAccessor(elementChild);
		}

		_source.m_TechniqueCommon = _techniqueCommon;
	}

	return _source;

}

Polylist Collada::readPolylist(tinyxml2::XMLElement * element)
{
	Polylist _polylist;
	_polylist.m_Count = getAttributeUShortValue(element, "count");
	_polylist.m_Material = getAttributeStringValue(element, "material");


	for (XMLElement *elementChild = element->FirstChildElement(); elementChild != nullptr; elementChild = elementChild->NextSiblingElement())
	{
		if (checkValueIsEqualToKey(elementChild, INPUT))
		{
			Input _input;
			_input.m_Source = getAttributeStringValue(elementChild, "source");
			_input.m_Semantic = getAttributeStringValue(elementChild, "semantic");
			_input.m_Offset = getAttributeStringValue(elementChild, "offset");
			_input.m_Set = getAttributeStringValue(elementChild, "set");

			_polylist.m_Inputs.push_back(_input);
		}
		else if (checkValueIsEqualToKey(elementChild, "vcount"))
		{
			
		}
		else if (checkValueIsEqualToKey(elementChild, "p"))
		{
			P _vertices_P;
			P _normals_P;
			P _coordinate_P;

			_vertices_P.m_Count = _polylist.m_Count * 3;
			_normals_P.m_Count = _polylist.m_Count * 3;
			_coordinate_P.m_Count = _polylist.m_Count * 3; 

			std::stringstream ss(elementChild->GetText());

			_vertices_P.m_Indices = (unsigned short*)malloc(sizeof(unsigned short) * _vertices_P.m_Count);
			_normals_P.m_Indices = (unsigned short*)malloc(sizeof(unsigned short) * _normals_P.m_Count);
			_coordinate_P.m_Indices = (unsigned short*)malloc(sizeof(unsigned short) * _coordinate_P.m_Count);

			int i = 0;
			float temp;
			while (ss >> temp)
			{
				if (i % 3 == 0)
				{
					_vertices_P.m_Indices[i / 3] = temp;
				}
				else if (i % 3 == 1)
				{
					_normals_P.m_Indices[i / 3] = temp;
				}
				else if (i % 3 == 2)
				{
					_coordinate_P.m_Indices[i / 3] = temp;
				}
				
				i++;
			}

			_polylist.m_Ps_position = _vertices_P;
			_polylist.m_Ps_normals = _normals_P;
			_polylist.m_Ps_texcoords = _coordinate_P;
		}
	}
	return _polylist;

}

FloatArray Collada::readFloatArray(tinyxml2::XMLElement * element)
{
	FloatArray _floatArray;
	_floatArray.m_ID = getAttributeStringValue(element, "id");
	_floatArray.m_Count = getAttributeUShortValue(element, "count");
	std::stringstream ss(element->GetText());
	_floatArray.m_Floats = (float *)malloc(sizeof(float) * _floatArray.m_Count);
	int i = 0;
	while (ss >> _floatArray.m_Floats[i])
	{
		i++;
	}

	return _floatArray;
}

NameArray Collada::readNameArray(tinyxml2::XMLElement * element)
{
	NameArray _nameArray;
	_nameArray.m_ID = getAttributeStringValue(element, "id");
	_nameArray.m_Count = getAttributeUShortValue(element, "count");

	std::stringstream ss(element->GetText());
	_nameArray.m_Names.reserve(_nameArray.m_Count);
	std::string temp;
	while (ss >> temp)
	{
		_nameArray.m_Names.push_back(temp);
	}

	return _nameArray;
}

Accessor Collada::readAccessor(tinyxml2::XMLElement * element)
{
	Accessor _accessor;
	_accessor.m_Source = getAttributeStringValue(element, "source");
	_accessor.m_Count = getAttributeUShortValue(element, "count");
	_accessor.m_Stride = getAttributeUShortValue(element, "stribe");

	for (XMLElement *elementChild = element->FirstChildElement(); elementChild != nullptr; elementChild = elementChild->NextSiblingElement())
	{
		if (checkValueIsEqualToKey(elementChild, PARAM))
		{
			Param _param;
			_param.m_Name = getAttributeStringValue(elementChild, "name");
			_param.m_Type = getAttributeStringValue(elementChild, "type");
			_accessor.m_Params.push_back(_param);
		}
	}

	return _accessor;
}

Skin Collada::readSkin(tinyxml2::XMLElement * element)
{
	Skin _skin;
	_skin.m_Source = getAttributeStringValue(element, "source");
	for (XMLElement *elementChild = element->FirstChildElement(); elementChild != nullptr; elementChild = elementChild->NextSiblingElement())
	{
		if (checkValueIsEqualToKey(elementChild, BINDSHAPEMATRIX))
		{
			glm::mat4x4 _bindShapeMatrix;

			std::stringstream ss(elementChild->GetText());

			int i = 0;
			float temp;
			while (ss >> temp)
			{
				_bindShapeMatrix[i / 4][i % 4] = temp;
			}

			_skin.m_BindShapeMatrix = _bindShapeMatrix;
		}
		else if (checkValueIsEqualToKey(elementChild, SOURCE))
		{
			_skin.m_Sources.push_back(readSource(elementChild));
			
		}
		else if (checkValueIsEqualToKey(elementChild, JOINTS))
		{
			Joints _joints;

			for (XMLElement *elementGrandson = elementChild->FirstChildElement(); elementGrandson != nullptr; elementGrandson = elementGrandson->NextSiblingElement())
			{
				_joints.m_Inputs.push_back(readInput(elementGrandson));
			}

			_skin.m_Joints = _joints;
		}
		else if (checkValueIsEqualToKey(elementChild, VERTEXWEIGHTS))
		{
			_skin.m_VertexWeights = readVertexWeights(elementChild);
		}
	}
	

	return _skin;
}

Input Collada::readInput(tinyxml2::XMLElement * element)
{
	Input _input;
	_input.m_Source = getAttributeStringValue(element, "source");
	_input.m_Semantic = getAttributeStringValue(element, "semantic");
	_input.m_Offset = getAttributeStringValue(element, "offset");
	_input.m_Set = getAttributeStringValue(element, "set");

	return _input;
}

VertexWeights Collada::readVertexWeights(tinyxml2::XMLElement * element)
{

	VertexWeights _vertexWeights;
	_vertexWeights.m_Count = getAttributeUShortValue(element, "count");

	for (XMLElement *elementChild = element->FirstChildElement(); elementChild != nullptr; elementChild = elementChild->NextSiblingElement())
	{
		if (checkValueIsEqualToKey(elementChild, INPUT))
		{
			_vertexWeights.m_Inputs.push_back(readInput(element));
		}
		else if (checkValueIsEqualToKey(elementChild, VCOUNT))
		{
			std::stringstream ss(elementChild->GetText());
			int temp;
			while (ss >> temp)
			{
				_vertexWeights.m_WeightsCountEveryVertex.push_back(temp);
			}

		}
		else if (checkValueIsEqualToKey(elementChild, V))
		{
			std::stringstream ss(elementChild->GetText());
			unsigned short temp_key, temp_value;
			unsigned int _size = _vertexWeights.m_WeightsCountEveryVertex.size();
			for (unsigned int i = 0; i < _size; i++)
			{
				WeightVertex _weightVertex;

				for (int j = 0; j < _vertexWeights.m_WeightsCountEveryVertex[i]; j++)
				{
					Weight _weight;

					ss >> temp_key >> temp_value;
					_weight.m_Bones = temp_key;
					_weight.m_WeightIndices = temp_value;

					_weightVertex.m_Weights.push_back(_weight);
					
				}

				_vertexWeights.m_WeightVertexs.push_back(_weightVertex);

				//if (i >= _size - 5)
				//{
				//	std::cout << "i = " << i << " : " << std::endl;
				//	for (int k = 0; k < _vertexWeights.m_WeightVertexs[i].m_Weights.size(); k++)
				//	{
				//		std::cout << "     " << "boneindice = " << _vertexWeights.m_WeightVertexs[i].m_Weights[k].m_Bones << ", " << " weightindices = " << _vertexWeights.m_WeightVertexs[i].m_Weights[k].m_WeightIndices << std::endl;
				//	}
				//	
				//}
			}
		}
	}

	return _vertexWeights;
}

Node Collada::readNode(tinyxml2::XMLElement * element)
{
	Node _node;
	

	return _node;
}







std::string Collada::getAttributeStringValue(tinyxml2::XMLElement * element, const char *attributeKey)
{
	for (const XMLAttribute *attribute = element->FirstAttribute(); attribute != nullptr; attribute = attribute->Next())
	{
		if (attribute->Name() == std::string(attributeKey))
		{
			return element->Attribute(attributeKey);
		}
	}
	return std::string();
}

int Collada::getAttributeUShortValue(tinyxml2::XMLElement * element, const char * attributeKey)
{
	for (const XMLAttribute *attribute = element->FirstAttribute(); attribute != nullptr; attribute = attribute->Next())
	{
		if (attribute->Name() == std::string(attributeKey))
		{
			return atoi(element->Attribute(attributeKey));
		}
	}
	
	return 0;
}



