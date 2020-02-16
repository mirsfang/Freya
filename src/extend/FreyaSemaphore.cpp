#include "FreyaSemaphore.h"

#include <chrono>

FREYA::FreyaSemaphore::FreyaSemaphore(int permits):_count(permits)
{
}

FREYA::FreyaSemaphore::~FreyaSemaphore()
{
	release();
}

void FREYA::FreyaSemaphore::signal()
{
	std::unique_lock<std::mutex> lock(_mutex);
	++_count;
	_cv.notify_one();

}

void FREYA::FreyaSemaphore::wait()
{
	std::unique_lock<std::mutex> lock(_mutex);
	_cv.wait(lock, [=] {return _count > 0; });
	--_count;
}

bool FREYA::FreyaSemaphore::waitSignal(uint64_t timeoutMs)
{
	std::unique_lock<std::mutex> lock(_mutex);
	bool ret = _cv.wait_for(lock, std::chrono::milliseconds(timeoutMs), [=] {return _count > 0; });
	if (ret) --_count;
	return ret;
}

bool FREYA::FreyaSemaphore::waitSignal(int permits, uint64_t timeoutMS)
{
	std::unique_lock<std::mutex> lock(_mutex);
	bool ret = _cv.wait_for(lock, std::chrono::microseconds(timeoutMS), [=] {return _count > 0; });
	if (ret) _count -= permits;
	return ret;
}

void FREYA::FreyaSemaphore::release()
{
	_cv.notify_all();
}
