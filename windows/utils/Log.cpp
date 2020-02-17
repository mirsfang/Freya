#include "utils/Log.h"

#include <iostream>

namespace FREYA {

	void FLOG::print_log(FREYA::LogType type, const char* msg, va_list arg_list) {
		std::string res;
		if (type == LogType::FREYA_ERROR) {
			std::cout << "\033[31m" << get_log_type(type) << FREYA_SEPARATOR << format_str(res, msg, arg_list) << "\n\033[0m" << std::endl;
		}
		else 
		{
			std::cout << "\033[32m" << get_log_type(type) << FREYA_SEPARATOR << format_str(res, msg, arg_list) << "\n\033[0m" << std::endl;
		}
	}

}