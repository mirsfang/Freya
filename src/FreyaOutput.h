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
#ifndef FREYA_OUTPUT
#define FREYA_OUTPUT

#include <functional>
#include <memory>
#include <vector>
#include <mutex>

#include "Freya.h"
#include "FreyaContext.h"
#include "FreyaFrameBuffer.h"
#include "extend/FreyaQueue.h"



namespace FREYA {

	
	class FreyaImage;
	class FreyaInput;


	/// 任务对象
	typedef std::function<void(void)> FreyaRunnable;

	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/18 15:35 
	*  @class       FreyaImageOrientation
	*  @brief       方向枚举
	*  @note        无
	*/
	enum class FreyaImageOrientation
	{
		FreyaImageOrientationUp,			///	default orientation
		FreyaImageOrientationDown,			/// 180 deg rotation
		FreyaImageOrientationLeft,			/// 90 deg CCW
		FreyaImageOrientationRight,			/// 90 deg CW
		FreyaImageOrientationUpMirrored,	/// as above but image mirrored along other axis. horizontal flip
		FreyaImageOrientationDownMirrored,	/// horizontal flip
		FreyaImageOrientationLeftMirrored,  /// vertical flip
		FreyaImageOrientationRightMirrored	/// vertical flip
	};

	/**
	*  @date        2020/02/18 15:36
	*  @brief       输出基类
	*  @param[in]   
	*  @param[out]  
	*  @return      
	**/
	class FreyaOutput
	{
	public:
		FreyaOutput();
		~FreyaOutput();
	public:
		bool shuouldSmoothlyScaleOutput;
		
		bool shouldIgnoreUpdatesToThisTarget;
		
		std::shared_ptr<FreyaInput> targetToIgnoreForUpdates;
		// 帧处理完成回调
		void(*_frameProcessingCompletionBlock) (std::shared_ptr<FreyaOutput>,uint64_t timeNN);
		
		bool enable;
		
		std::shared_ptr<FreyaTextureOptions> outputTextureOptions;
	protected:
		// 运行在渲染线程的队列
		std::shared_ptr<FreyaQueue<FreyaRunnable>> mRunOnDrawQueue;
		/// 输出的fbo
		std::shared_ptr<FreyaFrameBuffer> outputFramebuffer;
		/// 目标输入
		std::vector<std::shared_ptr<FreyaInput>> targets; 
		/// 目标纹理
		std::vector<int> targetTextureIndices;
		/// 输入目标纹理的大小
		std::shared_ptr<FreyaSize> inputTextureSize;

		std::shared_ptr<FreyaSize> cacheMaximumOutpuSize;

		std::shared_ptr<FreyaSize> forcedMaximumSize;

		bool overrideInputSize;

		bool allTargetsWantMonochromeData;

		bool usingNextFrameForImageCapture;

		std::mutex _lock;
	public:

		void setInputFramebufferForTarget(std::shared_ptr<FreyaInput> target,uint32_t inputTextureIndex);
	
		std::shared_ptr<FreyaFrameBuffer> framebufferForOutput();

		void removeOutputFramebuffer();

		void notifyTargetsAboutNewOutputTexture();

		std::vector<std::shared_ptr<FreyaInput>> getTargets();

		void addTarget(std::shared_ptr<FreyaInput> newTarget);

		void addTarget(std::shared_ptr<FreyaInput> newTarget,uint32_t textureLocation);

		void removeTarget(std::shared_ptr<FreyaInput> targetToRemove);

		void removeAllTargets();

		void forceProcessingAtSize(std::shared_ptr<FreyaSize> frameSize);

		void forceProcessingAtSizeRespectingAspectRatio(std::shared_ptr<FreyaSize> frameSize);

		void useNextFrameForImageCapture();

		std::shared_ptr<FreyaImage> newCGImageFromCurrentlyProcessedOutput();

		std::shared_ptr<FreyaImage> newCGImageByFilteringCGImage(std::shared_ptr<FreyaImage> imageToFilter);
	
		bool providesMonochromeOutput();
	protected:
		/**
		*  @date        2020/02/19 16:15
		*  @brief       执行渲染队列内的所有Runnable
		**/
		void runPendingOnDrawTasks();

		/**
		*  @date        2020/02/19 16:16
		*  @brief       渲染队列是否为空
		**/
		bool isOnDrawTasksEmpty();


		/**
		*  @date        2020/02/19 16:17
		*  @brief       添加到渲染队列
		**/
		void runOnDraw(FreyaRunnable runnable);
	};
};
#endif // FREYA_OUTPUT