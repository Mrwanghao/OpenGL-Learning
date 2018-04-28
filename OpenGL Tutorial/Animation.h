#pragma once
#include <glm/matrix.hpp>
#include <string>
#include <vector>

struct Joint
{
	glm::mat4 m_bindShapeMatrix;
	std::string m_Name;
	unsigned short m_ParentIndex;
};

struct Skeleton
{
	unsigned int m_JointCount;
	std::vector<Joint> m_Joints;

};