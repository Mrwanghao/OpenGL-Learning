#pragma once
#include <string>
#include <vector>
#include <glm/matrix.hpp>
#include <map>
#include "tinyxml2/tinyxml2.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#include "Shader.h"
#include "Window.h"

#define GEOMETRIESLIBRARY std::string("library_geometries")
#define CONTROLLERLIBRARY std::string("library_controllers")
#define ANIMATIONLIBRARY std::string("library_animations")
#define VISUALSCENELIBRARY std::string("library_visual_scene")
#define GEOMETRY std::string("geometry")
#define CONTROLLER std::string("controller")
#define SKIN std::string("skin")
#define MESH std::string("mesh")
#define SOURCE std::string("source")
#define POLYLIST std::string("polylist")
#define FLOATARRAY std::string("float_array")
#define NAMEARRAY std::string("Name_array")
#define TECHNIQUE_COMMON std::string("technique_common")
#define ACCESSOR std::string("accessor")
#define PARAM std::string("param")
#define INPUT std::string("input")
#define BINDSHAPEMATRIX std::string("bind_shape_matrix")
#define JOINTS std::string("joints")
#define VERTEXWEIGHTS std::string("vertex_weights")
#define VCOUNT std::string("vcount")
#define ANIMATION std::string("animation")
#define V std::string("v")
#define SAMPLER std::string("sampler")
#define CHANNEL std::string("channel")

struct FloatArray
{
	std::string m_ID;
	unsigned int m_Count;
	float *m_Floats;
};

struct NameArray
{
	unsigned int m_Count;
	std::string m_ID;
	std::vector<std::string> m_Names;

};

struct Param
{
	std::string m_Name;
	std::string m_Type;
};

struct Accessor
{
	unsigned int m_Count;
	unsigned int m_Stride;
	std::string m_Source;
	std::vector<Param> m_Params;
};

struct TechniqueCommon
{
	Accessor m_Accessor;
};

struct Source
{
	std::string m_ID;
	FloatArray m_FloatArray;
	NameArray m_NameArray;
	TechniqueCommon m_TechniqueCommon;
};

struct Input
{
	std::string m_Source;
	std::string m_Semantic;
	std::string m_Offset;
	std::string m_Set;

};

struct P
{
	unsigned int m_Count;
	unsigned short *m_Indices;

};

struct Polylist
{
	unsigned int m_Count;
	std::string m_Material;
	std::vector<Input> m_Inputs;
	P m_Ps_position;
	P m_Ps_normals;
	P m_Ps_texcoords;
};

struct Lines
{
	unsigned int m_Count;
	std::vector<Input> m_Inputs;
	P m_P;
};

struct Vertices
{
	std::string m_ID;
	std::vector<Input> m_Inputs;

};

struct ColladaMesh
{
	std::vector<Source> m_Sources;
	Vertices m_Vertices;
	Lines m_Lines;
	std::vector<Polylist> m_Polylists;
};

struct Geometry
{
	std::string m_ID;
	std::string m_Name;
	ColladaMesh m_Mesh;
};

struct GeometryLibrary
{
	Geometry m_Geometry;
};

struct Weight
{
	unsigned short m_Bones;
	unsigned short m_WeightIndices;
};

struct WeightVertex
{
	std::vector<Weight> m_Weights;
};

struct VertexWeights
{
	unsigned int m_Count;
	std::vector<Input> m_Inputs;
	std::vector<int> m_WeightsCountEveryVertex;
	std::vector<WeightVertex> m_WeightVertexs;
};

struct Joints
{
	std::vector<Input> m_Inputs;
};

struct Skin
{
	std::string m_Source;
	glm::mat4x4 m_BindShapeMatrix;
	Joints m_Joints;
	std::vector<Source> m_Sources;
	VertexWeights m_VertexWeights;
};

struct Controller
{
	std::string m_ID;
	std::string m_Name;
	Skin m_Skin;
};

struct ControllerLibrary
{
	Controller m_Controller;
};

struct Channel
{
	std::string m_Source;
	std::string m_Target;
};

struct Sampler
{
	std::string m_ID;
	std::vector<Input> m_Inputs;
};

struct Animation
{
	std::string m_ID;
	std::vector<Source> m_Sources;
	Sampler m_Sampler;
	Channel m_Channel;
};

struct AnimationLibrary
{
	std::vector<Animation> m_BoneAnimations;
};

struct Matrix
{
	std::string m_SID;
	glm::mat4 m_Matrix;

};

struct Node
{
	std::string m_ID;
	std::string m_Name;
	std::string m_SID;
	std::string m_Type;
	Matrix m_Matrix;
	std::vector<Node*> m_Nodes;
	//¸¸×Ó¹ØÏµ
	Node *m_ParentNode;
};

struct VisualScene
{
	std::string m_ID;
	std::string m_Name;
	std::vector<Node> m_Nodes;
};

struct VisualSceneLibrary
{
	VisualScene m_VisualScene;

};

#define MAX_BONE_COUNT_PER_VERTEX 4

struct ColladaVertex
{
	float m_BindX;
	float m_BindY;
	float m_BindZ;

	float m_BoneIDs[4];
	float m_Weights[4];
};


struct Bone
{
	glm::mat4 m_StartMatrix;
	glm::mat4 m_EndMatrix;

	float m_StartTime;
	float m_EndTime;

};


class Collada
{
public:
	Collada();
	Collada(const char *colladaFileName);
	~Collada();

	void draw(const Renderer::Window &mWindow);
	void drawPolylist(const Renderer::Window &mWindow, int index);

	void updateComputeVertex();

public:
	GeometryLibrary m_GeometryLibrary;
	ControllerLibrary m_ControllerLibrary;
	AnimationLibrary m_AnimationLibrary;
	VisualSceneLibrary m_VisualSceneLibrary;
	Renderer::Shader *m_Shader;

private:
	const char *m_ColladaFileName;
	Renderer::VertexArray *m_VAO;
	Renderer::IndexBuffer *m_IBO;
	tinyxml2::XMLDocument *m_DOC;
	unsigned short *m_IndicesData;
	int m_IndicesLength;

private:


	void readCollada(const char *colladaFileName);
	void setDataToBuffer();
	void setDataToIndexBuffer(int index);

	void readLibrary(tinyxml2::XMLElement *element);
	
	Geometry readGeometry(tinyxml2::XMLElement *element);
	ColladaMesh readMesh(tinyxml2::XMLElement *element);


	Source readSource(tinyxml2::XMLElement *element);
	Polylist readPolylist(tinyxml2::XMLElement *element);
	FloatArray readFloatArray(tinyxml2::XMLElement *element);
	NameArray readNameArray(tinyxml2::XMLElement *element);
	Accessor readAccessor(tinyxml2::XMLElement *element);
	Skin readSkin(tinyxml2::XMLElement *element);
	Input readInput(tinyxml2::XMLElement *element);
	VertexWeights readVertexWeights(tinyxml2::XMLElement *element);

	Controller readController(tinyxml2::XMLElement *element);

	void readAnimations(tinyxml2::XMLElement *element);
	void readAnimation(tinyxml2::XMLElement *element);



private:
	int getVertexCount() { return m_GeometryLibrary.m_Geometry.m_Mesh.m_Sources[0].m_FloatArray.m_Count; }

	float* getVerticesData() { return (float *)m_GeometryLibrary.m_Geometry.m_Mesh.m_Sources[0].m_FloatArray.m_Floats; }
	int getVerticesLength() { return m_GeometryLibrary.m_Geometry.m_Mesh.m_Sources[0].m_FloatArray.m_Count; }
	
	unsigned short* getIndicesDataByIndex(int index) { return (unsigned short*)m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[index].m_Ps_position.m_Indices; }
	int getIndicesLengthByIndex(int index) { return m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists[index].m_Ps_position.m_Count; }

	int getPolylistSize() { return m_GeometryLibrary.m_Geometry.m_Mesh.m_Polylists.size(); }

private:
	inline bool checkValueIsEqualToKey(tinyxml2::XMLElement *element, std::string key) { return element->Value() == key; }
	std::string getAttributeStringValue(tinyxml2::XMLElement *element, const char *attributeKey);
	int getAttributeUShortValue(tinyxml2::XMLElement *element, const char *attributeKey);
};

