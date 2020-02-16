#include "FreyaContext.h"

#include "FreyaFrameBufferCache.h"

FREYA::FreyaContext::FreyaContext()
{
}

FREYA::FreyaContext::~FreyaContext()
{
}

void FREYA::FreyaContext::useImageProcessingContext()
{
}

std::shared_ptr<FREYA::FreyaFrameBufferCache> FREYA::FreyaContext::currentFramebufferCache()
{
	return std::shared_ptr<FreyaFrameBufferCache>();
}



