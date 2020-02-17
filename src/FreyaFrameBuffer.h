/**
*  Copyright (c) 2020, MirsFang
*  All rights reserved.
*
*  @file        FreyaFrameBuffer.h
*  @author      Mirs(mirsfang@163.com)
*  @date        2020/02/16 14:07
*
*  @brief       FrameBuffer封装类
*
*/
#ifndef FREYA_FRAME_BUFFER
#define FREYA_FRAME_BUFFER

#include <memory>
#include <glad/glad.h>

namespace FREYA {

	class FreyaContext;
	class FreyaImage;
	class FreyaSemaphore;

	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/16 14:09
	*  @class       FreyaTextureOptions
	*  @brief       纹理相关属性的配置
	*/
	class FreyaTextureOptions {
	public:
		GLenum minFilter;
		GLenum magFilter;
		GLenum wrapS;
		GLenum wrapT;
		GLenum internalFormat;
		GLenum format;
		GLenum type;
	};

	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/16 14:09
	*  @class       FreyeFrameBuffer
	*  @brief       帧缓冲的封装类
	*/
	class FreyaFrameBuffer :public std::enable_shared_from_this<FreyaFrameBuffer>
	{
	public:
		FreyaFrameBuffer(GLint width, GLint height, FreyaTextureOptions textureOptions, bool onlyGenerateTexture);

		FreyaFrameBuffer(GLint width, GLint height, GLuint inputTexture);

		~FreyaFrameBuffer();
	private:
		/// fbo 的宽度
		GLint width{ 0 };
		/// fbo 的高度
		GLint height{ 0 };
		/// 纹理的配置参数
		FreyaTextureOptions textureOptions;
		/// 纹理Id
		GLuint texture{ 0 };

		bool missingFramebuffer = false;
	private:
		/// fbo
		GLuint framebuffer = { 0 };
		/// 引用的数量
		unsigned int framebufferReferenceCount = { 0 };
		/// 是否关闭引用计数
		bool referenceCountingDisabled = false;
		/// 信号量
		std::shared_ptr<FreyaSemaphore> _imageCaptureSemaphore;
	public:
		/**
		*  @date        2020/02/16 15:36
		*  @brief       激活当前fbo对象
		**/
		void activateFramebuffer();

		/**
		*  @date        2020/02/16 15:37
		*  @brief       当前fbo上锁，避免回收进cache里
		*  @see			unlock()
		**/
		void lock();

		/**
		*  @date        2020/02/16 15:38
		*  @brief       解锁当前FBO 使当前fbo可进入cache
		*  @see			lock()
		**/
		void unlock();

		/**
		*  @date        2020/02/16 15:39
		*  @brief       清除所有lock
		*  @see         lock()  unlock()
		**/
		void clearAllLocks();

		/**
		*  @date        2020/02/16 15:40
		*  @brief       关闭引用计数
		**/
		void disableReferenceCounting();

		/**
		*  @date        2020/02/16 15:40
		*  @brief       开启引用计数
		*  @see
		**/
		void enableReferenceCounting();

		/**
		*  @date        2020/02/16 15:45
		*  @brief       从fbo中获取当前fbo里的图像
		*  @return      FreyaImage的智能指针
		**/
		std::shared_ptr<FreyaImage> newImageFromFramebufferContents();
	private:
		/**
		*  @date        2020/02/16 15:53
		*  @brief       生成FBO
		**/
		void generateFramebuffer();

		/**
		*  @date        2020/02/16 15:54
		*  @brief       生成Texture
		**/
		void generateTexture();

		/**
		*  @date        2020/02/16 15:54
		*  @brief       销毁fbo
		**/
		void destoryFramebuffer();
	};

	typedef std::shared_ptr<FreyaFrameBuffer>  FreyaFrameBufferPtr;

};
#endif // FREYA_FRAME_BUFFER