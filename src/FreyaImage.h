#pragma once

#include <memory>
#include <glad/glad.h>

namespace FREYA {

	class FreyaImage:std::enable_shared_from_this<FreyaImage>
	{
	public:
		FreyaImage();
		~FreyaImage();
	public:
		/// read pixel 的数据 需要手动调用free来释放
		GLubyte * data;
	private:

	};

	typedef std::shared_ptr<FreyaImage> FreyaImagePtr;

};