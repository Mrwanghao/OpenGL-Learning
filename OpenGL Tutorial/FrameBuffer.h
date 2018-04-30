#pragma once

#include <glad/glad.h>




class FrameBuffer
{
public:
	GLuint mFBO;
	GLuint mColorTextureID;
	GLuint mRendererBufferID;
public:
	FrameBuffer();
	~FrameBuffer();

public:
	inline void enable() const { glBindFramebuffer(GL_FRAMEBUFFER, mFBO); }
	inline void disable() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

private:
	

};

