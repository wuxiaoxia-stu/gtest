#include "pch.h"
#include <stdio.h>
#include <iostream>
#include "testAyjGlobalData.h"

using namespace AYJ;
using namespace std;


namespace AyjPaicsSdkUser {

	//CJsonUtil jsonutil;//实例化CJsonUtil
	stuConfigData	teststuConfigData;										//配置文件测试数据
	const char*		szAuthNub = teststuConfigData.author_number;			//客户端授权码
	const char*		szDevId = teststuConfigData.szDevId;					//设备编号
	std::string		strId;													//主任密钥ID
	//std::string		strServerAuthNum = teststuConfigData.strServerAuthNum;	//	服务端授权码

	/////////////////		用户操作		//////////////////

	//	获取用户列表 全部获取
	//AYJ_PAICS_LIB_API int UserListGet(tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkUserTest, UserListGet) {
		tagCallBackPara tagTemp;
		tagTemp.nActionId = 1; //获取用户列表
		EXPECT_EQ(0, UserListGet(tagTemp))
			<< "获取用户列表 失败" << endl;
		cout << "获取用户列表::"<< tagTemp.strData << endl;

	}

	//	用户登录
	//AYJ_PAICS_LIB_API int UserLogin(int _nUserId, const char* _szUserPwd, const char* _szAuthNub, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkUserTest, UserLogin) {
		int _nUserId = 1;//管理员ID
		const char* _szUserPwd = "12369";//密码
		tagCallBackPara tagTemp;
		tagTemp.nActionId = 2; //用户登录
		EXPECT_EQ(0, UserLogin(_nUserId, _szUserPwd, szAuthNub, tagTemp))
			<< "用户登录 失败" << endl;
		
		cout << "用户登录::" << tagTemp.strData.c_str() << endl;
		cout << "parseUserTokenJson" << endl;
		int ret = CJsonUtil::parseUserTokenJson(tagTemp.strData.c_str());//解释用户登录数据，设置用户token值，作为用户退出接口的header
		EXPECT_EQ(0, ret) <<  "用户登录 失败" << endl;//返回0登录成功
		//EXPECT_EQ(0, UserLogout(tagTemp))//用户登出
		//	<< "用户登出 失败" << endl;
		//cout << "用户登出::" << tagTemp.strData.c_str() << endl;
	}

	//	用户刷新user token ,登录token 2小时失效, 2小时刷新一次
	//AYJ_PAICS_LIB_API int UserRefreshToken(tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkUserTest, UserRefreshToken) {
		tagCallBackPara tagPara;
		EXPECT_EQ(0, UserRefreshToken(tagPara))
			<< "sdk接口 用户刷新user token 失败" << endl;
		cout << "用户刷新数据::" << tagPara.strData << endl;
		int ret = CJsonUtil::parseCodeJson(tagPara.strData.c_str());
		EXPECT_EQ(0, ret) << "本地接口：用户刷新数据 失败" << endl;
	}


	//	用户列表数据修改后 保存到服务器，同时需要保存到主任秘钥
	//AYJ_PAICS_LIB_API int UserListSave(const char* _szUserDataJson, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkUserTest, UserListSave){
		tagCallBackPara tagTemp;
		UserListGet(tagTemp);//获取列表信息
		int nRetListSave = UserListSave(tagTemp.strData.c_str(), tagTemp);
		EXPECT_EQ(0, nRetListSave) << "sdk接口：用户列表数据修改后 保存到服务器，同时需要保存到主任秘钥 失败" << endl;
		//int nRetServer = CJsonUtil::parseCodeJson(_strUserDataJson.c_str());
		//EXPECT_EQ(0, nRetServer) << "云服务接口：保存主任秘钥的信息 失败" << endl;
	}

	//	用户退出登录
	//AYJ_PAICS_LIB_API int UserLogout(tagCallBackPara& _objPara);
	TEST(AyjPaicsSdkUserTest, UserLogout) {
		tagCallBackPara tagTmp;
		EXPECT_EQ(0, UserLogout(tagTmp))
			<< "sdk接口：用户登出 失败" << endl;
		cout << "用户登出: " << tagTmp.strData << endl;
		int ret = CJsonUtil::parseCodeJson(tagTmp.strData.c_str());
		EXPECT_EQ(0, ret) << "服务接口：用户退出 失败" << endl;
	}

	/////////////////		主任秘钥操作		//////////////////

	//	获取主任秘钥数量
	//AYJ_PAICS_LIB_API int LeaderKeyGetCount();
	TEST(AyjPaicsSdkLeaderTest, LeaderKeyGetCount) {
		int nRet = LeaderKeyGetCount();
		EXPECT_EQ(0, nRet) << "sdk接口：获取主任秘钥数量 失败" << endl;
	}

	//	获取主任秘钥id
	//AYJ_PAICS_LIB_API int LeaderKeyGetId(std::string& _strKeyId);
	//	获取主任秘钥信息.在云端服务器，获取主任秘钥的状态
	//AYJ_PAICS_LIB_API int LeaderKeyGetInfo(const std::string& _strKeyId, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkLeaderTest, LeaderKeyGetIdinfo) {
		int nRetGetId = LeaderKeyGetId(strId);
		cout << "主任秘钥id: " << strId << endl;
		EXPECT_EQ(0, nRetGetId) << "sdk接口：获取主任秘钥id 失败" << endl;

		tagCallBackPara tagTmp;
		int nRetGetInfo = AYJ::LeaderKeyGetInfo(strId, tagTmp);
		EXPECT_EQ(0, nRetGetInfo) << "sdk接口：获取主任秘钥信息 失败" << endl;
		cout << "主任秘钥信息: " << tagTmp.strData << endl;
		int nRetServer = CJsonUtil::parseCodeJson(tagTmp.strData.c_str());
		EXPECT_EQ(0, nRetServer) << "服务接口：获取主任秘钥的状态 失败" << endl;
	}

	//	获取主任秘钥内部 用户数据列表
	//AYJ_PAICS_LIB_API int LeaderKeyGetUserData(std::string& _strUserDataJson);

	//	保存 用户列表数据	到主任秘钥, 保存服务器成功后，再保存到主任秘钥
	//AYJ_PAICS_LIB_API int LeaderKeySaveUserData(std::string& _strUserDataJson);

	TEST(AyjPaicsSdkLeaderTest, LeaderKeyGetSaveUserData) {
		std::string _strUserDataJson = "";
		int nRetGetUserData = AYJ::LeaderKeyGetUserData(_strUserDataJson);
		//cout << "用户数据列表: " << _strUserDataJson << endl;
		EXPECT_EQ(0, nRetGetUserData) << "sdk接口：获取主任秘钥内部 用户数据列表 失败" << endl;
		int nRetSaveUserData = AYJ::LeaderKeySaveUserData(_strUserDataJson);
		EXPECT_EQ(0, nRetSaveUserData) << "sdk接口：保存 用户列表数据	到主任秘钥, 保存服务器成功后，再保存到主任秘钥 失败" << endl;
		//cout << "保存后用户数据列表: " << _strUserDataJson << endl;

	}

	//	查询主任秘钥绑定状态
	//AYJ_PAICS_LIB_API int LeaderKeyQueryState(const char*_szAuthNub, tagCallBackPara& _objPara);
	TEST(AyjPaicsSdkLeaderTest, LeaderKeyQueryState) {
		const char*		szAuthNub = teststuConfigData.author_number;
		tagCallBackPara tagTmp;
		int nRet = AYJ::LeaderKeyQueryState(szAuthNub, tagTmp);
		EXPECT_EQ(0, nRet) << "sdk接口：查询主任秘钥绑定状态 失败" << endl;
		int nRetServer = CJsonUtil::parseCodeJson(tagTmp.strData.c_str());
		EXPECT_EQ(0, nRetServer) << "服务接口：查询主任秘钥绑定状态 失败" << endl;
	}

	//	绑定主任秘钥到本地服务器
	//AYJ_PAICS_LIB_API int LeaderKeyBind(const char*_szKeyId, const char* _szAuthNub, const char* _szUserData, tagCallBackPara& _objPara);
	TEST(AyjPaicsSdkLeaderTest, LeaderKeyBind) {
		tagCallBackPara tagTmp;
		int nRetGetId = LeaderKeyGetId(strId);
		const char* szAuthNub = teststuConfigData.author_number;
		AYJ::LeaderKeyGetInfo(strId, tagTmp);
		int nRet = AYJ::LeaderKeyBind(strId.c_str(), szAuthNub, tagTmp.strData.c_str(), tagTmp);
		EXPECT_EQ(0, nRet) << "sdk接口：绑定主任秘钥到本地服务器 失败" << endl;
		int nRetServer = CJsonUtil::parseMsgJson(tagTmp.strData.c_str());
		EXPECT_EQ(0, nRetServer) << "服务接口：查询主任秘钥绑定状态 失败" << endl;
	}

	/////////////////		客户端配对操作		//////////////////
	//	查询配对状态
	//AYJ_PAICS_LIB_API int PairQureyStatus(const char* _szAuthNub, const char* _szDevId, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkPairTest, PairQureyStatus) {
		tagCallBackPara tagTmp;
		int nRet = PairQureyStatus(szAuthNub, szDevId, tagTmp);
		EXPECT_EQ(0, nRet) << "sdk接口：查询配对状态 失败" << endl;
		int nRetServer = CJsonUtil::parsePairStatus(tagTmp.strData.c_str(), teststuConfigData.strServerAuthNum);//成功返回0，并且修改了了服务授权码的值
		cout << "teststuConfigData.strServerAuthNum:" << teststuConfigData.strServerAuthNum << endl;
		EXPECT_EQ(0, nRetServer) << "服务接口：查询配对状态 失败" << endl;
	}
	
	//	解除配对
	//AYJ_PAICS_LIB_API int PairBreak(const char* _szAuthNub, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkPairTest, PairBreak) {
		tagCallBackPara tagTmp;
		int nRet = PairBreak(szAuthNub, tagTmp);
		EXPECT_EQ(0, nRet) << "sdk接口：解除配对 失败" << endl;
		int nRetServer = CJsonUtil::parseCodeJson(tagTmp.strData.c_str());
		EXPECT_EQ(0, nRetServer) << "服务接口：查询主任秘钥绑定状态 失败" << endl;

	}

	//	申请配对
	//AYJ_PAICS_LIB_API int PairApply(const char* _szAuthNub, const char* _szDevId, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkPairTest, PairApply) {
		tagCallBackPara tagTmp;
		int nRet = PairApply(szAuthNub, szDevId, tagTmp);
		EXPECT_EQ(0, nRet) << "sdk接口：申请配对 失败" << endl;
		int nRetServer = CJsonUtil::parseCodeJson(tagTmp.strData.c_str());
		EXPECT_EQ(0, nRetServer) << "服务接口：查询主任秘钥绑定状态 失败" << endl;
	}
}
