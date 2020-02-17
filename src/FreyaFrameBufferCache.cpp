#include "FreyaFrameBufferCache.h"


namespace FREYA {

	FreyaFrameBufferCache::FreyaFrameBufferCache()
	{
	}

	FreyaFrameBufferCache::~FreyaFrameBufferCache()
	{
	}

	std::shared_ptr<FreyaFrameBuffer> FreyaFrameBufferCache::fetchFramebufferForSize(FreyaSize framebufferSize, FreyaTextureOptions textureOptions, bool onlyTexture)
	{
		return std::shared_ptr<FreyaFrameBuffer>();
	}

	void FreyaFrameBufferCache::returnFramebufferToCache(std::shared_ptr<FreyaFrameBuffer> buffer)
	{
	}
};