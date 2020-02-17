#ifndef FREYA_PROGRAM
#define FREYA_PROGRAM

#include <glad/glad.h>
#include <memory>
#include <vector>
#include <string>

namespace FREYA {

	class FreyaProgram {
	public:
		FreyaProgram();
		~FreyaProgram();
	public:
		bool initialized = { false };
		std::string programLog;
	protected:
		std::vector<std::string> attributes;
		std::vector<std::string> uniforms;
		GLuint program = { 0 };
		GLuint verShader = { 0 };
		GLuint fragShader = { 0 };

	public:
		/**
		*  @date        2020/02/15 23:48
		*  @brief       直接根据顶点Shader和片段shader初始化
		*  @param[in]   vShaderString 顶点shader
		*  @param[in]   fShaderFileName 片段shader的文件路径
		**/
		void initWithVertexShaderString(const std::string& vShaderString, const std::string& fShaderString);

		/**
		*  @date        2020/02/15 23:58
		*  @brief       添加一个顶点变量
		*  @param[in]   attributeName 顶点变量名称
		**/
		void addAttribute(const std::string& attributeName);

		/**
		*  @date        2020/02/16 00:01
		*  @brief       获取属性索引
		*  @param[in]   attributeName 属性名称
		*  @return      属性的索引值
		**/
		GLuint attributeIndex(const std::string& attributeName);

		/**
		*  @date        2020/02/16 00:02
		*  @brief       获取uniform的索引
		*  @param[in]   uniformName uniform 的名称
		*  @return      属性的索引值
		**/
		GLuint uniformIndex(const std::string& uniformName);

		/**
		*  @date        2020/02/16 00:04
		*  @brief       链接
		**/
		bool link();

		/**
		*  @date        2020/02/16 00:04
		*  @brief       使用当前program
		**/
		void use();

		/**
		*  @date        2020/02/16 00:05
		*  @brief       验证当前program （输出Log的形式）
		**/
		void validate();
	private:

		/**
		*  @date        2020/02/16 12:18
		*  @brief       编译shader
		*  @param[in]   shader
		*  @param[in]   type shader 的类型
		*  @return      编译是否成功 true 成功 false 失败
		**/
		bool compileShader(GLuint* shader, GLenum type, const std::string& shaderString);

	};

	typedef std::shared_ptr<FreyaProgram> FreyaProgramPtr;

}
#endif