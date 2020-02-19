#include "FreyaContext.h"

#include "FreyaProgram.h"
#include "FreyaFrameBuffer.h"
#include "platform/FreyaPlatform.h"

 
namespace FREYA {
	FreyaContext::FreyaContext()
	{
		openGLESContextQueueKey = &openGLESContextQueueKey;
	}

	FreyaContext::~FreyaContext()
	{
	}


	std::shared_ptr<FreyaPlatform> FreyaContext::createPlatform()
	{
		
#ifdef WIN32
		platfrom = std::make_shared<FreyaPlatform>();
#endif 

		return platfrom;
	}



	void* FreyaContext::contextKey()
	{
		return openGLESContextQueueKey;
	}

	std::shared_ptr<FreyaContext> FreyaContext::sharedProcessingContext()
	{
		static std::shared_ptr<FreyaPlatform> sharedImageProcessingContext  = nullptr;
		return nullptr;
	}

	void FreyaContext::useImageProcessingContext()
	{
	}

	void FreyaContext::setActiveShaderProgram(std::shared_ptr<FreyaProgram> shaderProgram)
	{
	}

	GLint FreyaContext::maximumTextureSizeForThisDevice()
	{
		return 0;
	}

	GLint FreyaContext::maximumTextureUnitsForThisDevice()
	{
		return 0;
	}

	GLint FreyaContext::maximumVaryingVectorsForThisDevice()
	{
		return 0;
	}

	bool FreyaContext::deviceSupportsOpenGLESExtension(std::string extension)
	{
		return false;
	}

	bool FreyaContext::deviceSupportsRedTextures()
	{
		return false;
	}

	bool FreyaContext::deviceSupportsFramebufferReads()
	{
		return false;
	}

	std::shared_ptr<FreyaSize> FreyaContext::sizeThatFitsWithinATextureForSize(std::shared_ptr<FreyaSize> inputSize)
	{
		return std::shared_ptr<FreyaSize>();
	}

	void FreyaContext::useAsCurrentContext()
	{
	}

	void FreyaContext::setContextShaderProgram(std::shared_ptr<FreyaProgram> shaderProgram)
	{
	}

	void FreyaContext::presentBufferForDisplay()
	{
	}

	std::shared_ptr<FreyaProgram> FreyaContext::programForVertexShaderString(std::string vertextShaderString, std::string fragmentShaderString)
	{
		return std::shared_ptr<FreyaProgram>();
	}


	std::shared_ptr<FreyaFrameBufferCache> FreyaContext::currentFramebufferCache()
	{
		return std::shared_ptr<FreyaFrameBufferCache>();
	}

}