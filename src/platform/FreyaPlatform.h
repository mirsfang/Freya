/**
*  Copyright (c) 2020, MirsFang
*  All rights reserved.
*
*  @file        FreyaPlatform.h
*  @author      Mirs(mirsfang@163.com)
*  @date        2020/02/18 11:31
*
*  @brief       包装GLContext的类，需要各个平台自己去实现相关不同的GLContext
*  @note        
*
*/
#ifndef FREYA_PLATFORM
#define FREYA_PLATFORM

#include <memory>

namespace FREYA {

	class FreyaPlatform
	{
	protected:
		/// gl context
		void* _glContext;
		/// 窗口宽度
		uint32_t _width{ 0 };
		/// 窗口高度
		uint32_t _height{ 0 };
	public:
		uint32_t width() {
			return _width;
		}

		uint32_t height() {
			return _height;
		}
	public:
		void setWH(uint32_t width,uint32_t height) {
			_width = width;
			_height = height;
		}
	public:
		/**
		*  @date        2020/02/18 11:43
		*  @brief       创建上下文
		*  @return      true 创建成功 false 创建失败
		**/
		bool buildContext();

		/**
		*  @date        2020/02/18 11:44
		*  @brief       切换到当前上下文
		**/
		void makeCurrentContext();

		/**
		*  @date        2020/02/18 11:45
		*  @brief       取消上下文绑定
		**/
		void unbindContext();

		/**
		*  @date        2020/02/18 11:48
		*  @brief       销毁
		**/
		void destroy();
	};

	typedef std::shared_ptr<FreyaPlatform> FreyaPlatformPtr;

}

#endif