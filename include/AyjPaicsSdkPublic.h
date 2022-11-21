#pragma once

/*
******		FileName	:	AyjPaicsSdkPublic.h
******		Describe	:	此文件是c++ 接口
******		Date		:	2021-01-25 (重构时间)
******		Author		:	TangJinFei
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note1		:	1、依赖库..., 2、所有字符编码采用u8格式 3、仅支持64位 
******		Note2		:	接口命名规则: 后缀有Cb的, 都为异步 , 否则为同步
*/



#include "AyjPaicsSdkDefine.h"

#include <string>


namespace AYJ
{
	//	初始化sdk
	AYJ_PAICS_LIB_API int SdkInit(int _nLogLevel, const char* _pLogName, int _nHttpTimeOut);

	//	释放sdk
	AYJ_PAICS_LIB_API int SdkRelease();

	//	设置云端IP 与 端口
	AYJ_PAICS_LIB_API int SdkSetCloudAddr(const char* _szCloudIp, int _nCloudPort);
	//	设置本地服务器 IP 与 端口
	AYJ_PAICS_LIB_API int SdkSetLocalAddr(const char* _szLocalIp, int _nLocalPort);


	//	设置证书 唯一ID, 授权成功后或程序启动后，需要设置
	AYJ_PAICS_LIB_API int SdkSetLicenceNumber(const char* _szLicenceNumber);
	//	设置授权 唯一ID, 授权成功后或程序启动后，需要设置
	AYJ_PAICS_LIB_API int SdkSetAuthNumber(const char* _szAuthNumber);
	//	设置用户登录后的token,  2小时 token 失效, 需要重新获取
	AYJ_PAICS_LIB_API int SdkSetUserToken(const char* _szUserToken);

	//	获取客户端 完整版本 与 简易版本
	AYJ_PAICS_LIB_API int SdkGetClientVer(std::string& _strVer, std::string& _strVerEx);
	//	获取 产品名称
	AYJ_PAICS_LIB_API int SdkGetProductName(std::string& _strProductName);

}
