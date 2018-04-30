#pragma once
#include "BaseMesh.h"

class Quad : public BaseMesh
{
public:
	Quad();
	~Quad();

private:
	virtual void initBufferAndVertexArray();

public:
	void draw();

};

