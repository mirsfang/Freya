#ifndef FREYA_FILTER
#define FREYA_FILTER

#include <memory>

namespace FREYA {

	class FreyaInput;
	class FreyaOutput;
	

	class FreyaFilter
	{
	public:
		FreyaFilter();
		~FreyaFilter();

	private:

	};

	typedef std::shared_ptr<FreyaFilter> FreyaFilterPtr;

}

#endif // FREYA_FILTER