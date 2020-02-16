/**
*  Copyright (c) 2020, MirsFang
*  All rights reserved.
*
*  @file        FreyaOutput.h
*  @author      Mirs(mirsfang@163.com)
*  @date        2020/02/16 23:35
*
*  @brief       输出基类
*  @note         
*
*/
#pragma once

#include <functional>
namespace FREYA {

	/// 任务对象
	typedef std::function<void(void)> FreyaRunnable;

	/**
	*  @date        2020/02/16 18:04
	*  @brief       异步执行操作
	*  @param[in]   runable 任务对象
	**/
	void runSynchronouslyOnVideoProcessingQueue(FreyaRunnable runable);

};