#pragma once

#include "Renderable2D.h"

namespace Renderer{

	class Renderer2D
	{
	public:
		Renderer2D();
		virtual ~Renderer2D();

	protected:
		virtual void submit(const Renderable2D *pRenderable2D) = 0;
		virtual void flush() = 0;
	};

}
