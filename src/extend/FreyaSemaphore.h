/**
*  Copyright (c) 2020, MirsFang
*  All rights reserved.
*
*  @file        FreyaSemaphore.h
*  @author      Mirs(mirsfang@163.com)
*  @date        2020/02/16 21:27
*
*  @brief       信号量
*  @note        
*
*/
#pragma once

#include <memory>
#include <mutex>
#include <condition_variable>

namespace FREYA {
	
	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/16 21:44
	*  @class       FreyaSemaphore
	*  @brief       信号量
	*/
	class FreyaSemaphore {
	public:
		explicit FreyaSemaphore(int permits = 0);
		~FreyaSemaphore();
	private:
		std::mutex _mutex;
		std::condition_variable _cv;
		int _count{ 0 };
	public:
		/**
		*  @date        2020/02/16 21:53
		*  @brief       释放一个许可
		**/
		void signal();

		/**
		*  @date        2020/02/16 21:54
		*  @brief       等待
		**/
		void wait();

		/**
		*  @date        2020/02/16 21:59
		*  @brief       减少一个信号，超过毫秒，true等待成功 flase 等待失败
		*  @param[in]   timeoutMs 超时毫秒数
		*  @return      true 等待成功 false 等待失败
		**/
		bool waitSignal(uint64_t timeoutMs);

		/**
		*  @date        2020/02/16 22:05
		*  @brief       消费指定个信号 超过毫秒，true等待成功 flase 等待失败
		*  @param[in]   permits 信号数量
		*  @param[in]	timeoutMs 超时好描述  
		*  @return      true 等待成功 false 等待失败
		**/
		bool waitSignal(int permits,uint64_t timeoutMS);

		/**
		*  @date        2020/02/16 22:07
		*  @brief       释放所有信号
		**/
		void release();
	};

	typedef std::shared_ptr<FreyaSemaphore> FreyaSemaphorePtr;

};