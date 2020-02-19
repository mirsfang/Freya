/**
*  Copyright (c) 2020, MirsFang
*  All rights reserved.
*
*  @file        FreyaQueue.h
*  @author      Mirs(mirsfang@163.com)
*  @date        2020/02/17 19:11
*
*  @brief       线程安全队列
*  @note        
*
*/
#ifndef FREYA_QUEUE
#define FREYA_QUEUE	

#include <queue>
#include <mutex>

namespace FREYA {

	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/17 19:12
	*  @class       FreyaQueue
	*  @brief       线程安全的队列
	*/
	template <typename T>
	class FreyaQueue
	{
		typedef std::unique_lock<std::mutex> MutexLockGuard;
	public:
		FreyaQueue() {};
	private:
		std::queue<T> _qu;
		std::mutex _mutex;
	public:
		void push(const T& x)
		{
			MutexLockGuard ulk(_mutex);
			_qu.push(x);
		}

		void pop(T& x)
		{
			MutexLockGuard ulk(_mutex);
			x = _qu.front();
			_qu.pop();
		}

		void clear()
		{
			MutexLockGuard ulk(_mutex);
			while (!_qu.empty())
				_qu.pop();
		}

		bool empty()
		{
			MutexLockGuard ulk(_mutex);
			return _qu.empty();
		}

		size_t size()
		{
			MutexLockGuard ulk(_mutex);
			return _qu.size();
		}
	};
}

#endif // FREYA_QUEUE
