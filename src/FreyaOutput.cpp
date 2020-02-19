#include "FreyaOutput.h"

#include <typeinfo>

#include <algorithm>
#include <iterator>
#include "FreyaImage.h"
#include "glad/glad.h"
#include "utils/Log.h"


namespace FREYA {

	FreyaOutput::FreyaOutput()
	{
		mRunOnDrawQueue = std::make_shared<FreyaQueue<FreyaRunnable>>();

		enable = true;
		allTargetsWantMonochromeData = true;
		usingNextFrameForImageCapture = false;
		
		outputTextureOptions = std::make_shared<FreyaTextureOptions>();
		outputTextureOptions->minFilter = GL_LINEAR;
		outputTextureOptions->magFilter = GL_LINEAR;
		outputTextureOptions->wrapS = GL_CLAMP_TO_EDGE;
		outputTextureOptions->wrapT = GL_CLAMP_TO_EDGE;
		outputTextureOptions->internalFormat = GL_RGBA8;
		outputTextureOptions->format = GL_BGRA;
		outputTextureOptions->type = GL_UNSIGNED_BYTE;

	}

	FreyaOutput::~FreyaOutput()
	{
		removeAllTargets();
	}

	void FreyaOutput::setInputFramebufferForTarget(std::shared_ptr<FreyaInput> target, uint32_t inputTextureIndex)
	{
		target->setInputFramebuffer(framebufferForOutput(),inputTextureIndex);
	}

	std::shared_ptr<FreyaFrameBuffer> FreyaOutput::framebufferForOutput()
	{
		return outputFramebuffer;
	}

	void FreyaOutput::removeOutputFramebuffer()
	{
		outputFramebuffer = nullptr;
	}

	void FreyaOutput::notifyTargetsAboutNewOutputTexture()
	{
		auto iter = targets.begin();

		uint32_t index = 0;
		while (iter != targets.end())
		{
			setInputFramebufferForTarget((*iter), targetTextureIndices[index]);
			index++;
			iter++;
		}
	}

	std::vector<std::shared_ptr<FreyaInput>> FreyaOutput::getTargets()
	{
		return targets;
	}

	void FreyaOutput::addTarget(std::shared_ptr<FreyaInput> newTarget)
	{
		uint32_t nextAvailableTextureIndex =  newTarget->nextAvailableTextureIndex();
		addTarget(newTarget, nextAvailableTextureIndex);
		if (newTarget->shouldIgnoreUpdatesToThisTarget()) {
			targetToIgnoreForUpdates = newTarget;
		}
	}

	void FreyaOutput::addTarget(std::shared_ptr<FreyaInput> newTarget, uint32_t textureLocation)
	{
		auto result = std::find(targets.begin(), targets.end(), newTarget);
		if (result != targets.end()) {
			fr_logw("addTarget error.  newTarget is in targets!");
			return;
		}

		runOnDraw([&] {

			cacheMaximumOutpuSize = std::make_shared<FreyaSize>();
			cacheMaximumOutpuSize->width = 0;
			cacheMaximumOutpuSize->height = 0;

			setInputFramebufferForTarget(newTarget, textureLocation);
			targets.push_back(newTarget);
			targetTextureIndices.push_back(textureLocation);

			allTargetsWantMonochromeData = allTargetsWantMonochromeData && newTarget->watsMonochromeInput();

		});
		
	}

	void FreyaOutput::removeTarget(std::shared_ptr<FreyaInput> targetToRemove)
	{	
		auto iter = std::find(targets.begin(), targets.end(), targetToRemove);
		if (iter == targets.end())
		{
			fr_logw("Could not find remove target!");
			return;
		}

		if (targetToIgnoreForUpdates == targetToRemove) {
			targetToIgnoreForUpdates = nullptr;
		}

		cacheMaximumOutpuSize = std::make_shared<FreyaSize>();
		cacheMaximumOutpuSize->width = 0;
		cacheMaximumOutpuSize->height = 0;
		

		runOnDraw([&] {
			auto fin = std::find(targets.begin(), targets.end(), targetToRemove);
			int64_t index = std::distance(targets.begin(),fin);
			int textureIndexOfTarget = targetTextureIndices[index];

			targetToRemove->setInputSize(cacheMaximumOutpuSize, textureIndexOfTarget);
			targetToRemove->setInputRotation(FreyaImageRoutationMode::FreyaNoRotation,textureIndexOfTarget);

			targetTextureIndices.erase(targetTextureIndices.begin() + textureIndexOfTarget);
			for (auto it = targets.begin(); it != targets.end();) {
				if ((*it) == targetToRemove) {
					targets.erase(it);
					break;
				}
				else {
					it++;
				}
			}
			targetToRemove->endProcessing();
		});

	}

	void FreyaOutput::removeAllTargets()
	{
		cacheMaximumOutpuSize = std::make_shared<FreyaSize>();
		cacheMaximumOutpuSize->width = 0;
		cacheMaximumOutpuSize->height = 0;

		runOnDraw([&] {
			auto iter = targets.begin();
			int index = 0;
			while (iter != targets.end())
			{
				int textureIndexOfTarget = targetTextureIndices[index];
				
				std::shared_ptr<FreyaSize> zeroSize =  std::make_shared<FreyaSize>();
				zeroSize->width = 0;
				zeroSize->height = 0;
				(*iter)->setInputSize(zeroSize,textureIndexOfTarget);
				(*iter)->setInputRotation(FreyaImageRoutationMode::FreyaNoRotation, textureIndexOfTarget);

				index++;
				iter++;
			}

			targets.clear();
			targetTextureIndices.clear();

			allTargetsWantMonochromeData = true;
			 
		});

	}

	void FreyaOutput::forceProcessingAtSize(std::shared_ptr<FreyaSize> frameSize)
	{
	}

	void FreyaOutput::forceProcessingAtSizeRespectingAspectRatio(std::shared_ptr<FreyaSize> frameSize)
	{

	}

	void FreyaOutput::useNextFrameForImageCapture()
	{
	}

	std::shared_ptr<FreyaImage> FreyaOutput::newCGImageFromCurrentlyProcessedOutput()
	{
		return nullptr;
	}

	std::shared_ptr<FreyaImage> FreyaOutput::newCGImageByFilteringCGImage(std::shared_ptr<FreyaImage> imageToFilter)
	{
		return nullptr;
	}

	bool FreyaOutput::providesMonochromeOutput()
	{
		return false;
	}

	void FreyaOutput::runPendingOnDrawTasks()
	{
		while (mRunOnDrawQueue->size() > 0)
		{
			FreyaRunnable runnable;
			mRunOnDrawQueue->pop(runnable);
			runnable();
		}
	}

	bool FreyaOutput::isOnDrawTasksEmpty()
	{
		return mRunOnDrawQueue->size() == 0;
	}

	void FreyaOutput::runOnDraw(FreyaRunnable runnable)
	{
		std::unique_lock<std::mutex> ulk(_lock);
		mRunOnDrawQueue->push(runnable);
	}


}