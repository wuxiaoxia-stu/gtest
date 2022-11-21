/*
******		FileName	:	testAyjPaicsSdkAuthActive.cpp
******		Describe	:	此文件主要用于测试产品授权与激活
******		Date		:	2022-08-16
******		Author		:	WuXiaoXia
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note1		:	1、依赖库..., 2、所有字符编码采用u8格式 3、仅支持64位
******		Note2		:	接口命名规则: 后缀有Cb的, 都为异步 , 否则为同步
*/

#include "pch.h"
#include <string>
#include "testAyjGlobalData.h"


using namespace AYJ;
using namespace std;

namespace AyjPaicsSdkAuthActive {

	string strAuthUkeyId = ""; //授权Ukey编号
	stuConfigData	teststuConfigData;						//配置文件测试数据
	const char*		szAuthNum = teststuConfigData.author_number;//客户端授权码
	const char*		szDevId = teststuConfigData.szDevId;		//设备编号

	//--------测试AuthGetUkeyCount接口(获取 授权ukey 数量， 只有 一个的情况下，可用)--------
	//AYJ_PAICS_LIB_API int AuthGetUkeyCount();
	TEST(AyjPaicsSdkAuthActiveTest, AuthGetUkeyCount) {
		int nUkeyCount = AuthGetUkeyCount();
		EXPECT_EQ(1, nUkeyCount) << "获取 授权ukey 数量不为1" << endl;
	}

	//--------测试AuthGetUkeyId接口(获取 授权ukey 唯一标识符)--------
	//AYJ_PAICS_LIB_API int AuthGetUkeyId(std::string& _strAuthUkeyId);
	TEST(AyjPaicsSdkAuthActiveTest, AuthGetUkeyId) {
		int ret = AYJ::AuthGetUkeyId(strAuthUkeyId);
		cout << strAuthUkeyId << endl;
		EXPECT_EQ(0, ret) << "获取 授权ukey 唯一标识符 失败" << endl;
	}

	//--------测试AuthGetUKeyInfo接口(查询ukey 信息(获取Ukey 代号))--------
	//	AYJ_PAICS_LIB_API int AuthGetUKeyInfo(const char* _szUkeyId, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkAuthActiveTest, AuthGetUKeyInfo) {
		const char* szUkeyId = strAuthUkeyId.c_str();//c_str()函数返回一个指向正规C字符串的指针常量, 内容与本string串相同。
		tagCallBackPara tagTmp;////	通用回调数据
		//tagTmp.nActionId = 1;//动作ID设为1，表示获取Ukey代号
		int ret = AYJ::AuthGetUKeyInfo(szUkeyId, tagTmp);
		cout <<"szUkeyId:" << szUkeyId << endl;
		cout << "tagTmp:" << tagTmp.pCallBackFun << endl;
		EXPECT_EQ(0, ret) << "获取 授权ukey 唯一标识符 失败" << endl;
	}

	//--------测试AuthQueryStatus接口(向服务器查询授权状态 ,成功返回授权 license 与check_code)--------
	//	AYJ_PAICS_LIB_API int AuthQueryStatus(tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkAuthActiveTest, AuthQueryStatus) {
		tagCallBackPara tagTmp;////	通用回调数据
		tagTmp.nActionId = 1;//动作ID设为1，表示获取Ukey代号
		int ret = AYJ::AuthQueryStatus(tagTmp);
		cout << "tagTmp:" << tagTmp.pCallBackFun << endl;
		EXPECT_EQ(0, ret) << "向服务器查询授权状态 ,成功返回授权 license 与check_code 失败" << endl;
	}

	//--------测试AuthGetOderInfo接口(获取订单信息)--------
	//	AYJ_PAICS_LIB_API int AuthGetOderInfo(const char* _szDevId, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkAuthActiveTest, AuthGetOderInfo) {
		tagCallBackPara tagTmp;////	通用回调数据
		tagTmp.nActionId = 2;//动作ID设为2，表示获取订单信息
		int ret = AYJ::AuthGetOderInfo(szDevId, tagTmp);
		cout << "tagTmp:" << tagTmp.pCallBackFun << endl;
		EXPECT_EQ(0, ret) << "获取订单信息失败" << endl;
	}


	//--------测试AuthCreateLicence接口(创建证书 (申请授权))--------
	//	AYJ_PAICS_LIB_API int AuthCreateLicence(const char* _szAuthKeyId, const char* _szDevId, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkAuthActiveTest, AuthCreateLicence) {
		const char* szUkeyId = strAuthUkeyId.c_str();
		tagCallBackPara tagTmp;////	通用回调数据
		tagTmp.nActionId = 3;//动作ID设为3，表示获取licence
		int ret = AYJ::AuthCreateLicence(szUkeyId, szDevId, tagTmp);
		cout << "szUkeyId:" << szUkeyId << ",szDevId:" << szDevId << endl;
		cout << "tagTmp:" << tagTmp.pCallBackFun << endl;
		EXPECT_EQ(0, ret) << "创建证书 (申请授权) 失败" << endl;
	}

	//--------测试AuthQueryActivateStatus接口(查询激活状态， 未激活， 已激活   
	//(订单升级界面， 如果未激活，表明订单有更新) {"code":0,"data":{"state":1},"msg":"设备已激活"})--------
	//	AYJ_PAICS_LIB_API int AuthQueryActivateStatus(const char* _szDevId, const char* _szAuthNum,  tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkAuthActiveTest, AuthQueryActivateStatus) {
		const char* szUkeyId = strAuthUkeyId.c_str();
		tagCallBackPara tagTmp;////	通用回调数据
		tagTmp.nActionId = 3;//动作ID设为3，表示获取licence
		int ret = AYJ::AuthQueryActivateStatus(szUkeyId, szAuthNum, tagTmp);
		cout << "szUkeyId:" << szUkeyId << ",szAuthNum:" << szAuthNum << endl;
		cout << "tagTmp:" << tagTmp.pCallBackFun << endl;
		EXPECT_EQ(0, ret) << "查询激活状态 失败" << endl;
	}


}