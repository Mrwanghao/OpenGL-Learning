#include "FrameBuffer.h"
#include "Window.h"

extern Renderer::Window mWindow;

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &mFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

	glGenTextures(1, &mColorTextureID);
	glBindTexture(GL_TEXTURE_2D, mColorTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWindow.mWidth, mWindow.mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorTextureID, 0);

	glGenRenderbuffers(1, &mRendererBufferID);
	glBindRenderbuffer(GL_TEXTURE_2D, mRendererBufferID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWindow.mWidth, mWindow.mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);



	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


FrameBuffer::~FrameBuffer()
{
}


