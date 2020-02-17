#ifndef FREYA
#define FREYA	

#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <stdint.h>
#include <string>
#include <vector>

namespace FREYA {

	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/17 15:23
	*  @class       FreyaPoint
	*  @brief       点
	*/
	struct FreyaPoint {

		float x{ 0.0f };
		float y{ 0.0f };

		/**
		*  @date        2020/02/17 15:27
		*  @brief       是否为0点
		*  @return      true 是 false 不是
		**/
		bool empty() const;

		/**
		*  @date        2020/02/17 15:27
		*  @brief       copy 一个新的坐标一样的点
		*  @return      FreyaPoint
		**/
		FreyaPoint copy() const;

		/**
		*  @date        2020/02/17 15:28
		*  @brief       快速构造一个点
		*  @param[in]   ix X 坐标  iy Y 坐标
		*  @param[in]
		*  @return     FreyaPoint
		**/
		static FreyaPoint make(float ix = 0.0f, float iy = 0.0f);

	};

	/**
	*  @author      Mirs(mirsfang@163.com)
	*  @date        2020/02/17 15:33
	*  @class       FreyaSize
	*  @brief       封装宽和高以及相关方法
	*/
	struct FreyaSize
	{
		/// 宽
		float width{ 0.0f };
		/// 高
		float height{ 0.0f };

		/**
		*  @date        2020/02/17 15:35
		*  @brief       是否为空
		*  @return      true 是 false 否
		**/
		bool empty() const;

		/**
		*  @date        2020/02/17 15:36
		*  @brief       获取拷贝
		*  @return		FreyaSize的拷贝
		**/
		FreyaSize copy() const;

		/**
		*  @date        2020/02/17 15:37
		*  @brief       获取宽高比例  w/h
		*  @return      float  w/h
		**/
		float ratioWH() const;

		/**
		*  @date        2020/02/17 15:37
		*  @brief       重置
		**/
		void reset();

		/**
		*  @date        2020/02/17 15:38
		*  @brief       是否相等
		*  @return      true 是 false 不相等
		**/
		bool equals(const FreyaSize& other) const;

		/**
		*  @date        2020/02/17 15:40
		*  @brief       设置缩放
		*  @param[in]   scale 缩放系数
		*  @return		缩放后的Size         
		**/
		FreyaSize scale(float scale) const;
	
		/**
		*  @date        2020/02/17 15:44
		*  @brief       设置缩放 使用整数
		*  @param[in]   scale 缩放系数
		*  @return      缩放后的Size
		**/
		FreyaSize scaleInt(float scale) const;

		/**
		*  @date        2020/02/17 15:47
		*  @brief       对角线长度
		*  @return      对角线长度
		**/
		float diagonal() const;

		/**
		*  @date        2020/02/17 15:47
		*  @brief       获取宽高比例
		*  @return      宽高比例
		**/
		float ratio() const;

		/**
		*  @date        2020/02/17 15:51
		*  @brief       快速构建FreyaSize
		*  @param[in]   iwidth 宽度
		*  @param[in]   iheight 高度 
		*  @return      FreyaSize
		**/
		static FreyaSize make(float iwidth = 0.0f,float iheight = 0.0f);
	};
}
#endif