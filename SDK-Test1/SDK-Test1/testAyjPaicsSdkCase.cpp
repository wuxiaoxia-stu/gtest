/*
******		FileName	:	testAyjPaicsSdkCase.app
******		Describe	:	���ļ���c++ , ��Ҫ���ڲ��Բ������� ����  �������� �� ������ȡ
******		Date		:	2022-08-16
******		Author		:	WuXiaoXia
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note1		:	1��������..., 2�������ַ��������u8��ʽ 3����֧��64λ
******		Note2		:	�ӿ���������: ��׺��Cb��, ��Ϊ�첽 , ����Ϊͬ��
*/

#include "pch.h"
#include <string>
#include "testAyjGlobalData.h"
#include "CJsonObject.hpp"


using namespace AYJ;
using namespace std;

namespace AyjPaicsSdkCase {

	stuCheckInfo stuCheckInfoData;

	/////////////////		ABC ��� ���� 		//////////////////
	//	��ȡ���������Ϣ _nCheckId  = 1  , ʵʱ�����ļ�����ã� 2 �� �ʿصļ������
	//AYJ_PAICS_LIB_API int CheckInfoGet(int _nCheckId, tagCallBackPara& _objCbPara);
	TEST(testAyjPaicsSdkCase, CheckInfoGet) {
		tagCallBackPara tagTmp;
		
		int nRetRa = CheckInfoGet(1, tagTmp);
		EXPECT_EQ(0, nRetRa) << "sdk�ӿڣ���ȡʵʱ����������Ϣ ʧ��" << endl;
		int nRetRaServer = CJsonUtil::parseCheckInfo(tagTmp.strData.c_str(), stuCheckInfoData.oJsonData);
		cout << "ʵʱ�������������Ϣ: " << stuCheckInfoData.oJsonData.ToString() << endl;
		EXPECT_EQ(0, nRetRaServer) << "����ӿڣ���ȡ���������Ϣ ʧ��" << endl;

		int nRetQc = CheckInfoGet(2, tagTmp);
		EXPECT_EQ(0, nRetQc) << "sdk�ӿڣ���ȡ�ʿؿ���������Ϣ ʧ��" << endl;
		int nRetQcServer = CJsonUtil::parseCheckInfo(tagTmp.strData.c_str(), stuCheckInfoData.oJsonData);
		cout << "�ʿؿ��˼��������Ϣ: " << stuCheckInfoData.oJsonData.ToString() << endl;
		EXPECT_EQ(0, nRetQcServer) << "����ӿڣ���ȡ���������Ϣ ʧ��" << endl;
	}

	//	������������Ϣ
	//AYJ_PAICS_LIB_API int CheckInfoSave(const char* _szDataJson, tagCallBackPara& _objCbPara);
	TEST(testAyjPaicsSdkCase, CheckInfoSave) {
		tagCallBackPara tagTmp;
		int nRet = CheckInfoSave(stuCheckInfoData.oJsonData.ToString().c_str(), tagTmp);
		EXPECT_EQ(0, nRet) << "sdk�ӿڣ�������������Ϣ ʧ��" << endl;
	}

	//	ͨ�����id ��ȡ��ѡ��������б�
	//AYJ_PAICS_LIB_API int CheckListGetById(int _nCheckId, tagCallBackPara& _objCbPara);
	TEST(testAyjPaicsSdkCase, CheckListGetById) {
		tagCallBackPara tagTmp;
		int _nCheckId = std::stoi(stuCheckInfoData.strCaseCheckId);
		int nRet = CheckListGetById(_nCheckId, tagTmp);
		EXPECT_EQ(0, nRet) << "sdk�ӿڣ�ͨ�����id ��ȡ��ѡ��������б� ʧ��" << endl;
		//int nRetQcServer = CJsonUtil::parseCheckInfo(tagTmp.strData.c_str(), stuCheckInfoData.oJsonData);

	}

	/////////////////		��������		//////////////////
	//	��������
	//AYJ_PAICS_LIB_API int CaseCreate(const tagCaseCreateInfo& _tagCreateInfo, tagCallBackPara& _objCbPara);
	TEST(testAyjPaicsSdkCase, CaseCreate) {
		tagCaseCreateInfo tagCheckInfo;
		CJsonUtil::parseOnStartCaseCheckInfo(stuCheckInfoData.oJsonData, tagCheckInfo);
		tagCallBackPara tagTmp;
		int nRet = CaseCreate(tagCheckInfo, tagTmp);
		EXPECT_EQ(0, nRet) << "sdk�ӿڣ��������� ʧ��" << endl;
	}


}