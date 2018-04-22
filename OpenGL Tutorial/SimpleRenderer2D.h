#pragma once

#include "Renderer2D.h"

#include <deque>

namespace Renderer {

	class SimpleRenderer2D : public Renderer2D
	{
	private:
		std::deque<const Renderable2D*> mRendererDeque;

	public:
		void submit(const Renderable2D *pRenderable2D) override;
		void flush() override;

	public:
		SimpleRenderer2D();
		~SimpleRenderer2D();
	};

}
