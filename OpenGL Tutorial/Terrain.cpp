#include "Terrain.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


extern Camera mCamera;
extern Window mWindow;

Terrain::Terrain(const char *fileName)
	:
	mVertexArray(new VertexArray()),
	mShader(new Shader("Terrain.vs", "Terrain.fs")),
	mWidth(1024),
	mCellWidth(1)
{
	loadHeightMap(fileName);
	addTexture("terrain_01.jpg");
	addTexture("terrain_02.jpg");
	mShader->enable();
	mShader->setInt(std::string("texture00"), 0);
	mShader->setInt(std::string("texture01"), 1);
}


Terrain::~Terrain()
{
	if (mVertexArray) delete mVertexArray; mVertexArray = nullptr;
	if (mShader) delete mShader; mShader = nullptr;
	if (mHeightData) free(mHeightData); mHeightData = nullptr;
}

//读取raw文件数据
void Terrain::loadHeightMap(const char * fileName)
{
	FILE* file = NULL;
	file = fopen(fileName, "rb");
	if (file == NULL)
		return;
	mHeightData = (BYTE*)malloc(sizeof(BYTE) * mWidth * mWidth);
	if (fread(mHeightData, sizeof(BYTE), mWidth * mWidth, file) != mWidth * mWidth)
	{
		return;
	}
	if (ferror(file))
		return;
	fclose(file);

	setDataToBuffer();
}

void Terrain::draw() const
{
	mVertexArray->enable();
	for (int i = 0; i < _textureIDs.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, _textureIDs[i]);

	}
	mShader->enable();


	glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom), (float)mWindow.mWidth / (float)mWindow.mHeight, 0.1f, 2000.0f);
	mShader->setMat4("projection", projection);

	glm::mat4 view = mCamera.GetViewMatrix();
	mShader->setMat4("view", view);

	glm::mat4 model;
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	model = glm::translate(model, glm::vec3(-512.0f, -200.0f, -1024.0f));
		
	mShader->setMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, (mWidth - 1) * (mWidth - 1 ) * 6);

	mShader->disable();
	mVertexArray->disable();
}

void Terrain::setSize(int _width, int _cellWidth)
{
	mWidth = _width;
	mCellWidth = _cellWidth;
}

void Terrain::addTexture(const char * fileName)
{
	GLuint _textureID = load_image(fileName);
	_textureIDs.push_back(_textureID);
}

void Terrain::setDataToBuffer()
{
	int verticesCount = 6 * (mWidth - 1) * (mWidth - 1);

	_vertices.reserve(3 * verticesCount);
	for (int row = 0; row < mWidth - 1; row++)
	{
		for (int col = 0; col < mWidth - 1; col++)
		{
			glm::vec3 v1((float)(col	   ), (float)GetHeight(col	  , row    ) , (float)(row	   ));
			glm::vec3 v2((float)(col + 1   ), (float)GetHeight(col + 1, row    ) , (float)(row	   ));
			glm::vec3 v3((float)(col + 1   ), (float)GetHeight(col + 1, row + 1) , (float)(row + 1 ));
			glm::vec3 v4((float)(col	   ), (float)GetHeight(col    , row + 1) , (float)(row + 1 ));

			_vertices.push_back(v1.x);
			_vertices.push_back(v1.y);
			_vertices.push_back(v1.z);
			_vertices.push_back(v2.x);
			_vertices.push_back(v2.y);
			_vertices.push_back(v2.z);
			_vertices.push_back(v3.x);
			_vertices.push_back(v3.y);
			_vertices.push_back(v3.z);
			_vertices.push_back(v1.x);
			_vertices.push_back(v1.y);
			_vertices.push_back(v1.z);
			_vertices.push_back(v3.x);
			_vertices.push_back(v3.y);
			_vertices.push_back(v3.z);
			_vertices.push_back(v4.x);
			_vertices.push_back(v4.y);
			_vertices.push_back(v4.z);
		}
	}
	mVertexArray->addBuffer(new Buffer(_vertices, verticesCount * 3, 3), 0);
		

	_texcoords.reserve(6 * (mWidth - 1) * (mWidth - 1) * 2);
	for (int i = 0; i < verticesCount; i++)
	{
		_texcoords.push_back((float)(_vertices[i * 3	] / mWidth));
		_texcoords.push_back((float)(_vertices[i * 3 + 2] / mWidth));
	}
	mVertexArray->addBuffer(new Buffer(_texcoords, verticesCount * 2, 2), 1);
		
}

//通过x和y索引来获取相应的高度
int Terrain::GetHeight(int _x, int _y)
{
	if (!mHeightData)
	{
		return 0;
	}

	int xx = _x % mWidth;
	int yy = _y % mWidth;

	return mHeightData[yy * mWidth + xx];
}
