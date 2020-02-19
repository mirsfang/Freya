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

#include "Freya.h"

#include <memory>
#include <map>
#include <vector>
#include <string>

namespace FREYA {

	class FreyaTextureOptions;
	class FreyaFrameBuffer;
	
	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/16 19:02
	*  @class       FreyaFrameBufferCache
	*  @brief       FBO缓存池
	*/
	class FreyaFrameBufferCache :std::enable_shared_from_this<FreyaFrameBufferCache>
	{
		typedef std::vector<std::shared_ptr<FreyaFrameBuffer>> FrameBuffers;
	public:
		FreyaFrameBufferCache();
		~FreyaFrameBufferCache();
	private:
		/// fbo 缓存映射
		std::map<std::string, std::shared_ptr<FreyaFrameBuffer>> framebufferCache;
		/// 不同类型的fbo集合
		std::map<std::string, int> framebufferTypeCounts;
		/// 需要捕获图像的fbo列表
		std::vector<std::shared_ptr<FreyaFrameBuffer>> activeImageCaptureList;
	public:

		/**
		*  @date        2020/02/17 12:15
		*  @brief       根据size在fbo的缓存池中获取一个fbo
		*  @param[in]   framebufferSize fbo 的宽高
		*  @param[in]   textureOptions  纹理选项
		*  @param[in]	onlyTexture     只支持纹理
		*  @return      fbo 的智能指针
		*  @note		必须在GL线程内调用
		**/
		std::shared_ptr<FreyaFrameBuffer> fetchFramebufferForSize(FreyaSize framebufferSize, FreyaTextureOptions textureOptions,bool onlyTexture);

		/**
		*  @date        2020/02/17 17:50
		*  @brief       根据size在fbo的缓存池中获取一个fbo
		*  @param[in]   framebufferSize fbo 宽高
		*  @param[in]   onlyTexture  是否只是纹理
		*  @return      fbo 的智能指针 
		**/
		std::shared_ptr<FreyaFrameBuffer> fetchFramebufferForSize(FreyaSize framebufferSize,bool onlyTexture);

		/**
		*  @date        2020/02/16 19:02
		*  @brief       将fbo返回到缓存池中
		*  @param[in]   buffer  fbo
		**/
		void returnFramebufferToCache(std::shared_ptr<FreyaFrameBuffer> buffer);

		/**
		*  @date        2020/02/17 17:53
		*  @brief       净化全部未分配的fbo
		**/
		void purgeAllUnassignedFramebuffers();

		/**
		*  @date        2020/02/17 17:54
		*  @brief       添加fbo到捕获图像队列
		*  @param[in]   要捕获图像的fbo
		**/
		void addFramebufferToActiveImageCaptureList(std::shared_ptr<FreyaFrameBuffer> framebuffer);

		/**
		*  @date        2020/02/17 17:55
		*  @brief       从捕获队列中移除指定的fbo
		*  @param[in]   framebuffer 需要移除的fbo
		*  @return      
		**/
		void removeFramebufferFromActiveImageCaptureList(std::shared_ptr<FreyaFrameBuffer> framebuffer);
	private:

		/**
		*  @date        2020/02/17 17:57
		*  @brief       获取hash值
		*  @param[in]   size fbo 大小
		*  @param[in]   textureOptions 纹理选项
		*  @param[in]   是否仅为Texture
		*  @return      hash值
		**/
		std::string& hashForSize(std::string& hash,FreyaSize size,FreyaTextureOptions textureOptions,bool onlyTexture);

		/**
		*  @date        2020/02/18 12:15
		*  @brief       获取format之后的hash值
		*  @param[out]  hash_formatted 
		*  @param[in]   str_hash 
		*  @param[in]   ...
		*  @return      hash_formatted
		**/
		std::string& format_hash(std::string& hash_formatted, const char* str_hash, ...);

	};

	typedef std::shared_ptr<FreyaFrameBufferCache> FreyaFrameBufferCachePtr;

};

#endif //FREYA_FRAME_BUFFER