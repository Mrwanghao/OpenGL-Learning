#include "MtlAndObjModel.h"

MtlAndObjModel::MtlAndObjModel(const char *mtlFileName, const char *objFileName, int vtNumber)
	:
	mVertexArray(new VertexArray())
{
	objLoader = new OBJLoader(mtlFileName, objFileName, vtNumber);
	
}


MtlAndObjModel::~MtlAndObjModel()
{
	if (objLoader) delete objLoader; objLoader = nullptr;

}

void MtlAndObjModel::setDataToBuffer()
{
	//mVertexArray->addBuffer(new Buffer(objLoader->vData, objLoader->vCount * 3, 3), 0);
}
