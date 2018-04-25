#pragma once
#include <string>
#include <vector>

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
	std::string *m_Names;

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


class Collada
{

public:
	void readCollada();

public:
	GeometryLibrary m_GeometryLibrary;

};

