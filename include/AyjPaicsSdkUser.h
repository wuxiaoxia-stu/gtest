#pragma once

/*
******		FileName	:	AyjPaicsSdkUser.h
******		Describe	:	此文件是c++ 接口
******		Date		:	2021-01-25 (重构时间)
******		Author		:	TangJinFei
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note1		:	1、依赖库..., 2、所有字符编码采用u8格式 3、仅支持64位 
******		Note2		:	接口命名规则: 后缀有Cb的, 都为异步 , 否则为同步
*/


#include "AyjPaicsSdkDefine.h"

namespace AYJ
{
	/////////////////		用户操作		//////////////////

	//	获取用户列表 全部获取
	AYJ_PAICS_LIB_API int UserListGet(tagCallBackPara& _objCbPara);

	//	用户登录
	AYJ_PAICS_LIB_API int UserLogin(int _nUserId, const char* _szUserPwd, const char* _szAuthNub, tagCallBackPara& _objCbPara);
	//	用户退出登录
	AYJ_PAICS_LIB_API int UserLogout(tagCallBackPara& _objPara);
	//	用户刷新user token ,登录token 2小时失效, 2小时刷新一次
	AYJ_PAICS_LIB_API int UserRefreshToken(tagCallBackPara& _objCbPara);

	//	用户列表数据修改后 保存到服务器，同时需要保存到主任秘钥
	AYJ_PAICS_LIB_API int UserListSave(const char* _szUserDataJson, tagCallBackPara& _objCbPara);


	/////////////////		主任秘钥操作		//////////////////

	//	获取主任秘钥数量
	AYJ_PAICS_LIB_API int LeaderKeyGetCount();
	//	获取主任秘钥id
	AYJ_PAICS_LIB_API int LeaderKeyGetId(std::string& _strKeyId);
	//	获取主任秘钥信息
	AYJ_PAICS_LIB_API int LeaderKeyGetInfo(const std::string& _strKeyId, tagCallBackPara& _objCbPara);

	//	获取主任秘钥内部 用户数据列表
	AYJ_PAICS_LIB_API int LeaderKeyGetUserData(std::string& _strUserDataJson);
	//	保存 用户列表数据	到主任秘钥, 保存服务器成功后，再保存到主任秘钥
	AYJ_PAICS_LIB_API int LeaderKeySaveUserData(std::string& _strUserDataJson);


	//	查询主任秘钥绑定状态
	AYJ_PAICS_LIB_API int LeaderKeyQueryState(const char*_szAuthNub, tagCallBackPara& _objPara);
	//	绑定主任秘钥到本地服务器
	AYJ_PAICS_LIB_API int LeaderKeyBind(const char*_szKeyId, const char* _szAuthNub, const char* _szUserData, tagCallBackPara& _objPara);
	//	重新绑定主任秘钥到本地服务器(替换)
	AYJ_PAICS_LIB_API int LeaderKeyRebind(const char*_szKeyId, const char* _szAuthNub, const char* _szUserData, tagCallBackPara& _objPara);
	
	/////////////////		客户端配对操作		//////////////////
	
	//	查询配对状态
	AYJ_PAICS_LIB_API int PairQureyStatus(const char* _szAuthNub, const char* _szDevId, tagCallBackPara& _objCbPara);
	//	申请配对
	AYJ_PAICS_LIB_API int PairApply(const char* _szAuthNub, const char* _szDevId, tagCallBackPara& _objCbPara);
	//	解除配对
	AYJ_PAICS_LIB_API int PairBreak(const char* _szAuthNub, tagCallBackPara& _objCbPara);


}
