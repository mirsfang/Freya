#ifndef FREYA_CONTEXT
#define FREYA_CONTEXT

#include <memory>

namespace FREYA {

	class FreyaFrameBufferCache;

	class FreyaContext
	{
	public:
		FreyaContext();
		~FreyaContext();
	public:
		/**
		*  @date        2020/02/16 18:09
		*  @brief       使用当前的GLContext
		**/
		static void useImageProcessingContext();

	public:
		
		/**
		*  @date        2020/02/16 19:55
		*  @brief       获取当前的fbo缓存池
		*  @return		fbo 缓存池
		**/
		static std::shared_ptr<FreyaFrameBufferCache> currentFramebufferCache();

	private:

	};

	typedef std::shared_ptr<FreyaContext> FreyaContextPtr;

};

#endif