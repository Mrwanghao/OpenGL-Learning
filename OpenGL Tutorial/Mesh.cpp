#include "Mesh.h"

namespace Renderer
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		setupMesh();
	}

	Mesh::~Mesh()
	{
		delete mIndexBuffer;
		delete mVertexArray;
	}

	void Mesh::setupMesh()
	{
#if 1
		mVertexArray = new VertexArray();
		
		Buffer *mBuffer = new Buffer(&vertices[0], vertices.size());
		mVertexArray->addBuffer(mBuffer, 0, 3, sizeof(Vertex), (void *)0, true);
		mVertexArray->addBuffer(mBuffer, 1, 3, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
		mVertexArray->addBuffer(mBuffer, 2, 2, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));
		mVertexArray->addBuffer(mBuffer, 3, 3, sizeof(Vertex), (void *)offsetof(Vertex, Tangent));
		mVertexArray->addBuffer(mBuffer, 4, 3, sizeof(Vertex), (void *)offsetof(Vertex, Bitangent));
		
		//mIndexBuffer = new IndexBuffer(&indices[0], indices.size());
		
#else
		// create buffers/arrays
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		// vertex tangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
		// vertex bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

		glBindVertexArray(0);

#endif
	}

	void Mesh::Draw(const Shader *shader) 
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); 

			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); 
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);
			else if (name == "texture_height")
				number = std::to_string(heightNr++); 

			shader->setInt((name + number).c_str(), i);

			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

#if 1
		mVertexArray->enable();
		mIndexBuffer->enable();

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		mIndexBuffer->disable();
		mVertexArray->disable();
#else
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
#endif

	}

	bool Mesh::loadMesh(std::string & fileName)
	{


		return false;
	}

}