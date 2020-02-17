/**
*  Copyright (c) 2020, MirsFang
*  All rights reserved.
*
*  @file        Log.h
*  @author      Mirs(mirsfang@163.com)
*  @date        2020/02/15 21:01
*
*  @brief       文件工具类
*  @note		需要各个平台实现该类
*
*/
#ifndef FREYA_LOG
#define FREYA_LOG


#include <string>
#include <stdarg.h>

#define FREYA_TAG "Freay" ///< 定义FREYA_TAG 用于默认的格式化输出。
#define FREYA_SEPARATOR	 " : "
#define FREYA_LOG_TYPE_INFO "INFO"
#define FREYA_LOG_TYPE_DEBUG "DEBUG"
#define FREYA_LOG_TYPE_WARNING "WARNING"
#define FREYA_LOG_TYPE_ERROR "ERROR"

#define fr_logd(msg,...) FREYA::FLOG::FLOGD(msg,##__VA_ARGS__);
#define fr_logw(msg,...) FREYA::FLOG::FLOGW(msg,##__VA_ARGS__);
#define fr_loge(msg,...) FREYA::FLOG::FLOGE(msg,##__VA_ARGS__);

namespace FREYA {
	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/15 23:24
	*  @class       LogType
	*  @brief       日志等级枚举类
	*/
	enum class LogType
	{
		FREYA_INFO = 1,
		FREYA_DEBUG,
		FREYA_WARNING,
		FREYA_ERROR
	};

	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/15 23:25
	*  @class       FLOG
	*  @brief       日志打印类
	*/
	class FLOG {
	public:
		/**
		*  @date        2020/02/15 22:40
		*  @brief       根据LogType获取相应的字符
		*  @param[in]   LogType 枚举
		*  @return      枚举对应的字符串
		**/
		static char* get_log_type(FREYA::LogType type) {
			switch (type)
			{
			case FREYA::LogType::FREYA_INFO:
				return FREYA_LOG_TYPE_INFO;
			case FREYA::LogType::FREYA_DEBUG:
				return FREYA_LOG_TYPE_DEBUG;
			case FREYA::LogType::FREYA_WARNING:
				return FREYA_LOG_TYPE_WARNING;
			case FREYA::LogType::FREYA_ERROR:
				return FREYA_LOG_TYPE_ERROR;
			default:
				return FREYA_LOG_TYPE_INFO;
			}
		}


		/**
		*  @date        2020/02/15 22:07
		*  @brief       获取格式化之后的字符串
		*  @param[out]  str_formatted 格式化之后的字符串
		*  @param[in]   str_format    需要格式化的字符串
		*  @param[in]   arglist		  需要格式化的可变变量
		*  @return      格式化之后的字符串
		**/
		static std::string& format_str(std::string& str_formatted, const char* str_format, va_list arglist) {
			const int MAX_FORMATTED_STR_LEN = 2048;
			char strResult[MAX_FORMATTED_STR_LEN] = { 0 };
			vsprintf_s(strResult, str_format, arglist);
			str_formatted = strResult;
			return str_formatted;
		}


		/**
		*  打印错误信息
		*
		*  @date        2020/02/15 21:42
		*  @brief       错误日志输出
		*  @param[in]   TAG 标志
		*  @param[in]   msg 消息内容
		*  @param[in]   ... 需要格式化输出的变量
		*  @return
		*/
		static void print_log(FREYA::LogType type, const char* msg, va_list arg_list);


		/**
		*  @date        2020/02/15 21:48
		*  @brief       错误日志输出
		*  @param[in]	msg 消息内容
		*  @param[in]   ... 需要格式化输出的变量
		*  @return
		*/
		static void FLOGE(const char* msg, ...) {
			va_list arglist;
			va_start(arglist, msg);
			print_log(LogType::FREYA_ERROR, msg, arglist);
			va_end(msg);
		}

		/**
		*  @date        2020/02/15 21:48
		*  @brief       警告日志输出
		*  @param[in]	msg 消息内容
		*  @param[in]   ... 需要格式化输出的变量
		*  @return
		*/
		static void FLOGW(const char* msg, ...) {
			va_list arglist;
			va_start(arglist, msg);
			print_log(LogType::FREYA_WARNING, msg, arglist);
			va_end(msg);
		}

		/**
		*  @date        2020/02/15 21:51
		*  @brief       输出debug日志
		*  @param[in]   TAG 标志
		*  @param[in]   msg 消息内容
		*  @param[in]   ... 需要格式化输出的变量
		*  @return
		**/
		static void FLOGD(const char* msg, ...) {
			va_list arglist;
			va_start(arglist, msg);
			print_log(LogType::FREYA_DEBUG, msg, arglist);
			va_end(msg);
		}
	};
}

#endif