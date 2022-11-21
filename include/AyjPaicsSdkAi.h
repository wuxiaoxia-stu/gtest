#pragma once

/*
******		FileName	:	AyjPaicsSdkAi.h
******		Describe	:	此文件是c++ 接口，主要用于ai 方面的接口管理
******		Date		:	2021-06-24 (重构时间)
******		Author		:	TangJinFei
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note1		:	1、依赖库..., 2、所有字符编码采用u8格式 3、仅支持64位 
******		Note2		:	接口命名规则: 后缀有Cb的, 都为异步 , 否则为同步
*/



#include "AyjPaicsSdkDefine.h"

#include <string>


namespace AYJ
{
	/////////////////		AI 管理		//////////////////

	//	Ai 模型 运行 提示 回调
	typedef int(__stdcall *OnAiRunTipsCb)(unsigned int _nTipsType, char* _szData, void* _pUserData);

	//	初始化算法库, 释放 在sdkrelease 中释放， 无需单独释放 
	AYJ_PAICS_LIB_API tagRetInfo AiInit(const char* _szLicenceIn, const char* _szLicenceKeyIn, OnAiRunTipsCb _pRunCb);

	//	获取算法版本
	AYJ_PAICS_LIB_API tagRetInfo AiGetVersion(std::string& _strVersion);

	//	打开AI算法
	AYJ_PAICS_LIB_API tagRetInfo AiOpen(const tagAiOpenPara& _tagOpenPara);
	//	关闭AI 算法
	AYJ_PAICS_LIB_API tagRetInfo AiClose();


}
