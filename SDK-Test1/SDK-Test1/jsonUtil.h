#pragma once

#ifndef CJSONUTIL_H
#define CJSONUTIL_H

#include "pch.h"
#include "CJsonObject.hpp"

//JSON数据处理类
class CJsonUtil
{
public:
	CJsonUtil();
	~CJsonUtil();

public:
	//解析用户登录返回的json数据，设置用户token，登录成功返回0，失败返回-1
	static int parseUserTokenJson(const char* str);

	//解析返回的json数据，成功返回0，失败返回code
	static int parseCodeJson(const char* str);

	//解析返回的json数据中的提示信息，成功返回0，失败返回code
	static int parseMsgJson(const char* str);

	//解析配对状态数据，修改服务授权码，成功返回0
	static int CJsonUtil::parsePairStatus(const char* str, std::string &strServerAuthNum);

	//解析实时分析/质控考核的配置信息，成功返回0
	static int CJsonUtil::parseCheckInfo(const char* str, neb::CJsonObject &oJson);

	//	解析 开始病例，传入的检查信息
	static int CJsonUtil::parseOnStartCaseCheckInfo(neb::CJsonObject &oJson, tagCaseCreateInfo& _objCheckInfo);
};

#endif // !CJSONUTIL_H
