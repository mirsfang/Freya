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
#pragma once

#include <memory>

namespace FREYA { 
	class FreyeFrameBuffer;
	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/16 19:02
	*  @class       FreyaFrameBufferCache
	*  @brief       FBO缓存池
	*/
	class FreyaFrameBufferCache:std::enable_shared_from_this<FreyaFrameBufferCache>
	{
	public:
		FreyaFrameBufferCache();
		~FreyaFrameBufferCache();
	public:

		/**
		*  @date        2020/02/16 19:02
		*  @brief       将fbo返回到缓存池中
		*  @param[in]   buffer  fbo
		**/
		void returnFramebufferToCache(std::shared_ptr<FreyeFrameBuffer> buffer);
	private:
		
	};

	typedef std::shared_ptr<FreyaFrameBufferCache> FreyaFrameBufferCachePtr;

};