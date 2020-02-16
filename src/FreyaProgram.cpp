#include "FreyaProgram.h"

#include <algorithm>
/**
*  Copyright (c) 2020, MirsFang
*  All rights reserved.
*
*  @file        FreyaProgram.cpp
*  @author      Mirs(mirsfang@163.com)
*  @date        2020/02/16 14:08
*
*  @brief       FreyaProgram
*
*/
#include "utils/Log.h"

namespace FREYA {
	FreyaProgram::FreyaProgram() {
	}

	FreyaProgram::~FreyaProgram()
	{
		if (verShader)
			glDeleteShader(verShader);

		if (fragShader)
			glDeleteShader(fragShader);

		if (program)
			glDeleteShader(program);
	}

	void FreyaProgram::initWithVertexShaderString(const std::string& vShaderString, const std::string& fShaderString)
	{
		initialized = false;
		program = glCreateProgram();

		//编译顶点shader
		if (!compileShader(&verShader, GL_VERTEX_SHADER, vShaderString)) {
			fr_loge("Failed to compile vertes shader!");
		}

		//编译片段shader
		if (!compileShader(&fragShader, GL_FRAGMENT_SHADER, fShaderString)) {
			fr_loge("Failed to compile fragment shader!");
		}

		glAttachShader(program, verShader);
		glAttachShader(program, fragShader);

	}

	void FreyaProgram::addAttribute(const std::string& attributeName)
	{
		if (std::find(attributes.begin(), attributes.end(), attributeName) != attributes.end())
		{
			attributes.push_back(attributeName);
			glBindAttribLocation(program, attributes.size() - 1, attributeName.c_str());
		}
	}

	GLuint FreyaProgram::attributeIndex(const std::string& attributeName)
	{
		auto iterator = attributes.begin();
		int index = -1;
		while (iterator != attributes.end())
		{
			index++;
			if (*iterator == attributeName) {
				break;
			}
			iterator++;
		}
		return index;
	}

	GLuint FreyaProgram::uniformIndex(const std::string& uniformName)
	{
		return glGetUniformLocation(program, uniformName.c_str());
	}

	bool FreyaProgram::link()
	{
		GLint status;
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			return false;
		}

		if (verShader)
		{
			glDeleteShader(verShader);
			verShader = 0;
		}

		if (fragShader)
		{
			glDeleteShader(fragShader);
			fragShader = 0;
		}
		initialized = true;
		return true;
	}

	void FreyaProgram::use()
	{
		if (program == 0) {
			fr_logw("Use program is 0 ,are you sure init success ?");
		}
		glUseProgram(program);
	}

	void FreyaProgram::validate()
	{
		GLint logLength;
		glValidateProgram(program);
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			GLchar* log = (GLchar*)malloc(logLength);
			glGetProgramInfoLog(program, logLength, &logLength, log);
			fr_logd(log);
		}

	}

	bool FreyaProgram::compileShader(GLuint* shader, GLenum type, const std::string& shaderString)
	{
		GLint status;
		const GLchar* source;
		source = shaderString.c_str();
		if (!source) {
			fr_loge("Failed to load  %s shader !", type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			return false;
		}
		//编译shader
		*shader = glCreateShader(type);
		glShaderSource(*shader, 1, &source, NULL);
		glCompileShader(*shader);

		glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) {
			GLint longLength;
			glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &longLength);
			if (longLength > 0) {
				GLchar* log = (GLchar*)malloc(longLength);
				glGetShaderInfoLog(*shader, longLength, &longLength, log);
				if (shader == &verShader) {
					this->vertexShaderLog = log;
				}
				else {
					this->fragmentShaderLog = log;
				}
				fr_loge(log);
				free(log);
			}
		}
		return status == GL_TRUE;
	}

}