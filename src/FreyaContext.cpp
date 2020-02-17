#include "FreyaContext.h"

namespace FREYA {

	FreyaContext::FreyaContext()
	{
	}

	FREYA::FreyaContext::~FreyaContext()
	{
	}

	void FreyaContext::useImageProcessingContext()
	{
	}

	std::shared_ptr<FreyaFrameBufferCache> FreyaContext::currentFramebufferCache()
	{
		return std::shared_ptr<FreyaFrameBufferCache>();
	}

}