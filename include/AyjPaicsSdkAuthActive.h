#pragma once

/*
******		FileName	:	AiYunjiSdk.h
******		Describe	:	此文件是c++ 接口
******		Date		:	2021-01-25
******		Author		:	TangJinFei
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note1		:	1、依赖库..., 2、所有字符编码采用u8格式 3、仅支持64位
******		Note2		:	用于产品授权与激活
*/

#include "AyjPaicsSdkDefine.h"

#include <string>


namespace AYJ
{
	//	获取 授权ukey 数量， 只有 一个的情况下，可用
	AYJ_PAICS_LIB_API int AuthGetUkeyCount();
	//	获取 授权ukey 唯一标识符
	AYJ_PAICS_LIB_API int AuthGetUkeyId(std::string& _strAuthUkeyId);
	//	查询ukey 信息(获取Ukey 代号)
	AYJ_PAICS_LIB_API int AuthGetUKeyInfo(const char* _szUkeyId, tagCallBackPara& _objCbPara);


	//	向服务器查询授权状态 ,成功返回授权 license 与check_code
	AYJ_PAICS_LIB_API int AuthQueryStatus(tagCallBackPara& _objCbPara);
	//	获取订单信息
	AYJ_PAICS_LIB_API int AuthGetOderInfo(const char* _szDevId, tagCallBackPara& _objCbPara);
	//	创建证书 (申请授权)
	AYJ_PAICS_LIB_API int AuthCreateLicence(const char* _szAuthKeyId, const char* _szDevId, tagCallBackPara& _objCbPara);

	//	查询激活状态， 未激活， 已激活   (订单升级界面， 如果未激活，表明订单有更新) {"code":0,"data":{"state":1},"msg":"设备已激活"}
	AYJ_PAICS_LIB_API int AuthQueryActivateStatus(const char* _szDevId, const char* _szAuthNum,  tagCallBackPara& _objCbPara);
	//	设备激活
	AYJ_PAICS_LIB_API int AuthActivation(const tagDevActivateInfo& _objActivate, tagCallBackPara& _objCbPara);

	//	验证证书
	AYJ_PAICS_LIB_API tagRetInfo AuthVerifyLicence(const char* _szLicenceIn, const char* _szLicenceKeyIn);
	//	解析证书
	AYJ_PAICS_LIB_API tagRetInfo AuthAnalysisLicence(const char* _szLicenceIn, std::string& _strLicenceOut);
	//	解析激活信息
	AYJ_PAICS_LIB_API tagRetInfo AuthAnalysisActivateInfo(const char* _szActivateInfo, std::string& _strLicenceOut);


	//	客户端 版本检查 (是否有新版本，需要下载，有的话, 返回 下载url )
	AYJ_PAICS_LIB_API int ClientVersionCheck(const char* _szDevId, tagCallBackPara& _objCbPara);

	
}