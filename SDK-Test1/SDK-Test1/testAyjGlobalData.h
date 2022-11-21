#pragma once
/*
******		FileName	:	Define.h
******		Describe	:	此文件用于管理全局变量
******		Date		:	2022-08-11
******		Author		:	Xiaoxia
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note		:   暂无
*/



#ifndef CAYJLOGINMANAGER_H
#define CAYJLOGINMANAGER_H

#include <string>
#include "CJsonObject.hpp"

//配置文件 系统数据
struct stuConfigData {

	const char*	cloud_ip = "192.168.1.189";		//	云端服务器IP
	int			cloud_port = 9005;				//	云端服务器端口
	const char* local_ip = "127.0.0.1";			//	本地服务器 IP
	int			local_port = 9006;				//	本地服务器端口
	//	证书 唯一ID
	const char* licence = "";
	const char* author_number = "C_22060015";	//	客户端授权号
	const char* szDevId = "22062217402617101";	//设备编号

	std::string	strProductName = "PUS S300";	//	产品名称
	std::string	strProductVer = "V_1.0.1.0713"; //	产品完整版本
	std::string	strProductVerEx = "V_1.0";		//	产品简易版本

	const char* user_token = "";
	std::string strServerAuthNum;	//	服务端授权码
};

//病例数据
struct stuCheckInfo {

	neb::CJsonObject oJsonData;//实例化CJsonObject,实时分析/质控考核的检查配置信息
	//	基本信息
	std::string	strDevId;				//	设备序列号 必填

	int			nCaseType = 1;			//	病例类型，1  实时分析病例 2 单人质控  3、多人质控 必填
	std::string	strCaseCheckId = "80c9b545-7ea7-4f42-9f2b-df330485e594";		//	检查id， 设置切面的id	必填
	int			nCaseCheckType = 0;		//	病例检查类型， 0 早 1中 2 晚, 必填

};


#endif // CAYJLOGINMANAGER_H