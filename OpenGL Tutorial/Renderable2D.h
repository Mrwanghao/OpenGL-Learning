#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Renderer
{
	class Renderable2D
	{
	public:
		Renderable2D(glm::vec3 &pPosition, glm::vec2 &pSize, glm::vec4 &mColor, Shader *pShader);
		~Renderable2D();

		inline const VertexArray* getVAO() const { return mVertexArray; }
		inline const IndexBuffer* getIBO() const { return mIndexBuffer; }
		inline const Shader* getShader() const { return mShader; }

	protected:
		glm::vec3 mPosition;
		glm::vec2 mSize;
		glm::vec4 mColor;

		VertexArray *mVertexArray;
		IndexBuffer *mIndexBuffer;
		Shader *mShader;

		inline const glm::vec3& getPosition() const { return mPosition; }
		inline const glm::vec2& getSize() const { return mSize; }
		inline const glm::vec4 getColor() const { return mColor; }

	};
};

