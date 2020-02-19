#include "FreyaFrameBuffer.h"

#include "utils/Log.h"
#include "FreyaImage.h"
#include "extend/FreyaSemaphore.h"

namespace FREYA {
	FreyaFrameBuffer::FreyaFrameBuffer(GLint width, GLint height, FreyaTextureOptions textureOptions, bool onlyGenerateTexture)
	{
		this->width = width;
		this->height = height;
		this->textureOptions = textureOptions;
		this->missingFramebuffer = onlyGenerateTexture;

		if (missingFramebuffer)
		{
			generateTexture();
			framebuffer = 0;
		}
		else
		{
			generateFramebuffer();
		}

		_imageCaptureSemaphore = std::make_shared<FreyaSemaphore>(0);
		_imageCaptureSemaphore->signal();
	}

	FreyaFrameBuffer::FreyaFrameBuffer(GLint width, GLint height, GLuint inputTexture)
	{
		FreyaTextureOptions defaultTextureOptions;
		defaultTextureOptions.minFilter = GL_LINEAR;
		defaultTextureOptions.magFilter = GL_LINEAR;
		defaultTextureOptions.wrapS = GL_CLAMP_TO_EDGE;
		defaultTextureOptions.wrapT = GL_CLAMP_TO_EDGE;
		defaultTextureOptions.internalFormat = GL_RGBA8;
		defaultTextureOptions.format = GL_BGRA;
		defaultTextureOptions.type = GL_UNSIGNED_BYTE;
		missingFramebuffer = true;

		textureOptions = defaultTextureOptions;
		this->width = width;
		this->height = height;
		framebufferReferenceCount = 0;
		referenceCountingDisabled = true;
		texture = inputTexture;
	}

	FreyaFrameBuffer::~FreyaFrameBuffer()
	{
		destoryFramebuffer();
	}

	void FreyaFrameBuffer::activateFramebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glViewport(0, 0, width, height);
	}

	void FreyaFrameBuffer::lock()
	{
		if (referenceCountingDisabled)
		{
			return;
		}

		framebufferReferenceCount++;
	}

	void FreyaFrameBuffer::unlock()
	{
		if (referenceCountingDisabled)
		{
			return;
		}

		framebufferReferenceCount--;

		if (framebufferReferenceCount < 1)
		{
			//FreyaContext::currentFramebufferCache()->returnFramebufferToCache(this->shared_from_this());
		}
	}

	void FreyaFrameBuffer::clearAllLocks()
	{
		framebufferReferenceCount = 0;
	}

	void FreyaFrameBuffer::disableReferenceCounting()
	{
		referenceCountingDisabled = true;
	}

	void FreyaFrameBuffer::enableReferenceCounting()
	{
		referenceCountingDisabled = false;
	}

	std::shared_ptr<FreyaImage> FreyaFrameBuffer::newImageFromFramebufferContents()
	{
		if (_imageCaptureSemaphore == nullptr) return nullptr;
	
		std::shared_ptr<FreyaImage> image = std::make_shared<FreyaImage>();

		GLubyte* rawImagePixels;
		activateFramebuffer();
		rawImagePixels = (GLubyte*)malloc((size_t)width * (size_t)height * (size_t)4);
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, rawImagePixels);
		image->data = rawImagePixels;

		return image;
	}


	void FreyaFrameBuffer::generateFramebuffer()
	{

		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		/// 生成与FBO绑定的texture
		generateTexture();

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, textureOptions.internalFormat, width, height, 0, textureOptions.format, textureOptions.type, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE) {
			fr_logw("generate framebuffer error ! :%d", status);
		}

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void FreyaFrameBuffer::generateTexture()
	{
		glActiveTexture(GL_TEXTURE1);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureOptions.minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureOptions.magFilter);
		// This is necessary for non-power-of-two textures
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureOptions.wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureOptions.wrapT);

		// TODO: handle mipmaps	 
	}

	void FreyaFrameBuffer::destoryFramebuffer()
	{

		if (framebuffer) {
			glDeleteFramebuffers(1, &framebuffer);
			framebuffer = 0;
		}

		glDeleteTextures(1, &texture);
	}
}



