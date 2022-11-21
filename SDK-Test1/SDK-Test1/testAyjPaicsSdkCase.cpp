/*
******		FileName	:	testAyjPaicsSdkCase.app
******		Describe	:	此文件是c++ , 主要用于测试病例管理 包括  病例创建 与 病例获取
******		Date		:	2022-08-16
******		Author		:	WuXiaoXia
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note1		:	1、依赖库..., 2、所有字符编码采用u8格式 3、仅支持64位
******		Note2		:	接口命名规则: 后缀有Cb的, 都为异步 , 否则为同步
*/

#include "pch.h"
#include <string>
#include "testAyjGlobalData.h"
#include "CJsonObject.hpp"


using namespace AYJ;
using namespace std;

namespace AyjPaicsSdkCase {

	stuCheckInfo stuCheckInfoData;

	/////////////////		ABC 检查 数据 		//////////////////
	//	获取检查配置信息 _nCheckId  = 1  , 实时分析的检查配置， 2 ， 质控的检查配置
	//AYJ_PAICS_LIB_API int CheckInfoGet(int _nCheckId, tagCallBackPara& _objCbPara);
	TEST(testAyjPaicsSdkCase, CheckInfoGet) {
		tagCallBackPara tagTmp;
		
		int nRetRa = CheckInfoGet(1, tagTmp);
		EXPECT_EQ(0, nRetRa) << "sdk接口：获取实时分析配置信息 失败" << endl;
		int nRetRaServer = CJsonUtil::parseCheckInfo(tagTmp.strData.c_str(), stuCheckInfoData.oJsonData);
		cout << "实时分析检查配置信息: " << stuCheckInfoData.oJsonData.ToString() << endl;
		EXPECT_EQ(0, nRetRaServer) << "服务接口：获取检查配置信息 失败" << endl;

		int nRetQc = CheckInfoGet(2, tagTmp);
		EXPECT_EQ(0, nRetQc) << "sdk接口：获取质控考核配置信息 失败" << endl;
		int nRetQcServer = CJsonUtil::parseCheckInfo(tagTmp.strData.c_str(), stuCheckInfoData.oJsonData);
		cout << "质控考核检查配置信息: " << stuCheckInfoData.oJsonData.ToString() << endl;
		EXPECT_EQ(0, nRetQcServer) << "服务接口：获取检查配置信息 失败" << endl;
	}

	//	保存检查配置信息
	//AYJ_PAICS_LIB_API int CheckInfoSave(const char* _szDataJson, tagCallBackPara& _objCbPara);
	TEST(testAyjPaicsSdkCase, CheckInfoSave) {
		tagCallBackPara tagTmp;
		int nRet = CheckInfoSave(stuCheckInfoData.oJsonData.ToString().c_str(), tagTmp);
		EXPECT_EQ(0, nRet) << "sdk接口：保存检查配置信息 失败" << endl;
	}

	//	通过检查id 获取已选择的切面列表
	//AYJ_PAICS_LIB_API int CheckListGetById(int _nCheckId, tagCallBackPara& _objCbPara);
	TEST(testAyjPaicsSdkCase, CheckListGetById) {
		tagCallBackPara tagTmp;
		int _nCheckId = std::stoi(stuCheckInfoData.strCaseCheckId);
		int nRet = CheckListGetById(_nCheckId, tagTmp);
		EXPECT_EQ(0, nRet) << "sdk接口：通过检查id 获取已选择的切面列表 失败" << endl;
		//int nRetQcServer = CJsonUtil::parseCheckInfo(tagTmp.strData.c_str(), stuCheckInfoData.oJsonData);

	}

	/////////////////		病例创建		//////////////////
	//	创建病例
	//AYJ_PAICS_LIB_API int CaseCreate(const tagCaseCreateInfo& _tagCreateInfo, tagCallBackPara& _objCbPara);
	TEST(testAyjPaicsSdkCase, CaseCreate) {
		tagCaseCreateInfo tagCheckInfo;
		CJsonUtil::parseOnStartCaseCheckInfo(stuCheckInfoData.oJsonData, tagCheckInfo);
		tagCallBackPara tagTmp;
		int nRet = CaseCreate(tagCheckInfo, tagTmp);
		EXPECT_EQ(0, nRet) << "sdk接口：创建病例 失败" << endl;
	}


}