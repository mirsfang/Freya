#include "..\..\src\platform\FreyaPlatform.h"
#include "..\..\src\platform\FreyaPlatform.h"
#include "..\..\src\platform\FreyaPlatform.h"
#include "..\..\src\platform\FreyaPlatform.h"
#include "..\..\src\platform\FreyaPlatform.h"
/**
*  Copyright (c) 2020, MirsFang
*  All rights reserved.
*
*  @file        FreyaPlatform.cpp
*  @author      Mirs(mirsfang@163.com)
*  @date        2020/02/18 11:52
*
*  @brief       GLContext包装的windows实现
*  @note        
*
*/
#include "platform/FreyaPlatform.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "utils/Log.h"


namespace FREYA {

	static void __freya_glfw_error_callback__(int error, const char* description)
	{
		fr_loge("opengl err[%d]: %s", error, description);
		return;
	}

	bool FreyaPlatform::buildContext() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
		glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
		glfwSetErrorCallback(__freya_glfw_error_callback__);

		char win_name[128];
		snprintf(win_name,sizeof win_name,"Freya");

		bool isFullScreen = false;
		GLFWmonitor* pMonitor = isFullScreen ? glfwGetPrimaryMonitor() : NULL;

		//创建窗口
		_glContext = glfwCreateWindow(_width,_height,win_name,pMonitor,nullptr);

		if (_glContext == nullptr) {
			fr_loge("[ Freya_Win ] Failed to create GLFW Window");
			return false;
		}

		//创建OpenGL 环境
		glfwMakeContextCurrent((GLFWwindow*)_glContext);

		if (!gladLoadGL()) {
			fr_loge("[ Freya_Win ] gladLoadGL() failed");
			return false;
		}

		fr_logd("OpenGL:[%d.%d]",GLVersion.major,GLVersion.minor);
		return true;
	}

	void FreyaPlatform::makeCurrentContext()
	{
		if (_glContext == nullptr)
		{
			fr_loge("makeCurrentContext（） failed , _glContext is not init");
			return;
		}

		if (_glContext != glfwGetCurrentContext())
			glfwMakeContextCurrent((GLFWwindow*)_glContext);
	}

	void FreyaPlatform::swapBuffers()
	{
		glfwSwapBuffers((GLFWwindow*)_glContext);
	}

	void FreyaPlatform::swapBuffers(std::shared_ptr<FreyaPlatform> platfrom)
	{
		if (platfrom == nullptr) {
			fr_loge("swap buffer platform is error!");
			return;
		}

		glfwSwapBuffers((GLFWwindow*)platfrom->_glContext);
	}

	void FreyaPlatform::unbindContext()
	{
		glfwMakeContextCurrent(nullptr);
	}

	void FreyaPlatform::destroy()
	{
		if (_glContext == nullptr) return;
		glfwDestroyWindow((GLFWwindow *)_glContext);
		_glContext = nullptr;
	}
	
}