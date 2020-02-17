/**
*  Copyright (c) 2020, MirsFang
*  All rights reserved.
*
*  @file        FreyaFrameBufferCache.h
*  @author      Mirs(mirsfang@163.com)
*  @date        2020/02/16 19:01
*
*  @brief       FBO缓存相关
*  @note
*
*/
#ifndef FREYA_FRAME_BUFFER_CACHE
#define FREYA_FRAME_BUFFER_CACHE

#include <memory>

#include "Freya.h"
#include "FreyaFrameBuffer.h"

namespace FREYA {
	
	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/16 19:02
	*  @class       FreyaFrameBufferCache
	*  @brief       FBO缓存池
	*/
	class FreyaFrameBufferCache :std::enable_shared_from_this<FreyaFrameBufferCache>
	{
	public:
		FreyaFrameBufferCache();
		~FreyaFrameBufferCache();
	public:

		/**
		*  @date        2020/02/17 12:15
		*  @brief       根据size在fbo的缓存池中获取一个fbo
		*  @param[in]   framebufferSize fbo 的宽高
		*  @param[in]   textureOptions  纹理选项
		*  @param[in]	onlyTexture     只支持纹理
		*  @return      fbo的智能指针
		**/
		std::shared_ptr<FreyaFrameBuffer> fetchFramebufferForSize(FreyaSize framebufferSize, FreyaTextureOptions textureOptions,bool onlyTexture);

		/**
		*  @date        2020/02/16 19:02
		*  @brief       将fbo返回到缓存池中
		*  @param[in]   buffer  fbo
		**/
		void returnFramebufferToCache(std::shared_ptr<FreyaFrameBuffer> buffer);
	private:

	};

	typedef std::shared_ptr<FreyaFrameBufferCache> FreyaFrameBufferCachePtr;

};

#endif //FREYA_FRAME_BUFFER