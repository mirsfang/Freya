#ifndef FREYA_CONTEXT
#define FREYA_CONTEXT

#include <memory>
#include <map>
#include <vector>
#include <glad/glad.h>

#include "Freya.h"


namespace FREYA {

	class FreyaProgram;
	class FreyaFrameBuffer;
	class FreyaFrameBufferCache;
	class FreyaPlatform;

	enum class FreyaImageRoutationMode
	{
		FreyaNoRotation,
		FreyaRotateLeft,
		FreyaRotateRight,
		FreyaFilpVertical,
		FreyaFilpHorizonal,
		FreyaRotateRightFilpVertical,
		FreyaRotateLeftFilpHorizontal,
		FreyaRotate180
	};


	class FreyaContext
	{
	public:
		FreyaContext();
		~FreyaContext();
	public:
		static void* openGLESContextQueueKey;
	public:
		/// 当前使用的program
		std::shared_ptr<FreyaProgram> currentShaderProgram;
		/// 平台封装
		std::shared_ptr<FreyaPlatform> platfrom;
		/// fbo  缓存
		std::shared_ptr<FreyaFrameBufferCache> frameBufferCache;
	private:
		/// program cache
		std::map<std::string,std::shared_ptr<FreyaProgram>> shaderProgramCache;
		/// hash cache
		std::vector<std::string> shaderProgramUsageHistory;
	public:
		/**
		*  @date        2020/02/18 12:37
		*  @brief       Context 的 key
		*  @return      void * 指针      
		**/
		void* contextKey();

		/**
		*  @date        2020/02/18 12:47
		*  @brief       
		*  @return      FreyaContext的智能指针
		**/
		std::shared_ptr<FreyaContext> sharedProcessingContext();

		/**
		*  @date        2020/02/16 19:55
		*  @brief       获取当前的fbo缓存池
		*  @return		fbo 缓存池
		**/
		static std::shared_ptr<FreyaFrameBufferCache> currentFramebufferCache();

		/**
		*  @date        2020/02/16 18:09
		*  @brief       使用当前的GLContext
		**/
		static void useImageProcessingContext();

		static void setActiveShaderProgram(std::shared_ptr<FreyaProgram> shaderProgram);
	
		static GLint maximumTextureSizeForThisDevice();

		static GLint maximumTextureUnitsForThisDevice();

		static GLint maximumVaryingVectorsForThisDevice();

		static bool deviceSupportsOpenGLESExtension(std::string extension);

		static bool deviceSupportsRedTextures();

		static bool deviceSupportsFramebufferReads();

		static std::shared_ptr<FreyaSize> sizeThatFitsWithinATextureForSize(std::shared_ptr<FreyaSize> inputSize);
	public:
		void useAsCurrentContext();
	
		void setContextShaderProgram(std::shared_ptr<FreyaProgram> shaderProgram);

		void presentBufferForDisplay();

		std::shared_ptr<FreyaProgram>  programForVertexShaderString(std::string vertextShaderString,std::string fragmentShaderString);
	private:
		/**
		*  @date        2020/02/19 21:23
		*  @brief       创建一个Context
		*  @return		创建平台相关的Context      
		**/
		std::shared_ptr<FreyaPlatform> createContext();
	};

	typedef std::shared_ptr<FreyaContext> FreyaContextPtr;

	/************************************************************************/
	/*                               FreyaInput                             */
	/************************************************************************/
	
	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/18 13:33
	*  @class       FreyaInput
	*  @brief       输入接口
	*/
	class FreyaInput {
	public:
		virtual void newFrameReadyAtTime(uint64_t frameTimeNN,uint32_t textureIndex) = 0;
		
		virtual void setInputFramebuffer(std::shared_ptr<FreyaFrameBuffer> newInputFramebuffer,uint32_t atIndex) = 0;

		virtual uint32_t nextAvailableTextureIndex() = 0;

		virtual void setInputSize(std::shared_ptr<FreyaSize> newSize,uint32_t textureIndex) = 0;

		virtual void setInputRotation(FreyaImageRoutationMode newInputRotation,uint32_t textureIndex) = 0;

		virtual std::shared_ptr<FreyaSize> maximumOutputSize() = 0;

		virtual void endProcessing() = 0;

		virtual bool shouldIgnoreUpdatesToThisTarget() = 0;

		virtual bool enable() =0;

		virtual bool watsMonochromeInput() = 0;

		virtual void setCurrentlyReceivingMonochromeInput(bool newValue) = 0;
	};
	
	std::shared_ptr<FreyaInput> FreyaInputPtr;
};

#endif