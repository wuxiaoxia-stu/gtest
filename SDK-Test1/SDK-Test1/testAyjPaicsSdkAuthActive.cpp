/*
******		FileName	:	testAyjPaicsSdkAuthActive.cpp
******		Describe	:	���ļ���Ҫ���ڲ��Բ�Ʒ��Ȩ�뼤��
******		Date		:	2022-08-16
******		Author		:	WuXiaoXia
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note1		:	1��������..., 2�������ַ��������u8��ʽ 3����֧��64λ
******		Note2		:	�ӿ���������: ��׺��Cb��, ��Ϊ�첽 , ����Ϊͬ��
*/

#include "pch.h"
#include <string>
#include "testAyjGlobalData.h"


using namespace AYJ;
using namespace std;

namespace AyjPaicsSdkAuthActive {

	string strAuthUkeyId = ""; //��ȨUkey���
	stuConfigData	teststuConfigData;						//�����ļ���������
	const char*		szAuthNum = teststuConfigData.author_number;//�ͻ�����Ȩ��
	const char*		szDevId = teststuConfigData.szDevId;		//�豸���

	//--------����AuthGetUkeyCount�ӿ�(��ȡ ��Ȩukey ������ ֻ�� һ��������£�����)--------
	//AYJ_PAICS_LIB_API int AuthGetUkeyCount();
	TEST(AyjPaicsSdkAuthActiveTest, AuthGetUkeyCount) {
		int nUkeyCount = AuthGetUkeyCount();
		EXPECT_EQ(1, nUkeyCount) << "��ȡ ��Ȩukey ������Ϊ1" << endl;
	}

	//--------����AuthGetUkeyId�ӿ�(��ȡ ��Ȩukey Ψһ��ʶ��)--------
	//AYJ_PAICS_LIB_API int AuthGetUkeyId(std::string& _strAuthUkeyId);
	TEST(AyjPaicsSdkAuthActiveTest, AuthGetUkeyId) {
		int ret = AYJ::AuthGetUkeyId(strAuthUkeyId);
		cout << strAuthUkeyId << endl;
		EXPECT_EQ(0, ret) << "��ȡ ��Ȩukey Ψһ��ʶ�� ʧ��" << endl;
	}

	//--------����AuthGetUKeyInfo�ӿ�(��ѯukey ��Ϣ(��ȡUkey ����))--------
	//	AYJ_PAICS_LIB_API int AuthGetUKeyInfo(const char* _szUkeyId, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkAuthActiveTest, AuthGetUKeyInfo) {
		const char* szUkeyId = strAuthUkeyId.c_str();//c_str()��������һ��ָ������C�ַ�����ָ�볣��, �����뱾string����ͬ��
		tagCallBackPara tagTmp;////	ͨ�ûص�����
		//tagTmp.nActionId = 1;//����ID��Ϊ1����ʾ��ȡUkey����
		int ret = AYJ::AuthGetUKeyInfo(szUkeyId, tagTmp);
		cout <<"szUkeyId:" << szUkeyId << endl;
		cout << "tagTmp:" << tagTmp.pCallBackFun << endl;
		EXPECT_EQ(0, ret) << "��ȡ ��Ȩukey Ψһ��ʶ�� ʧ��" << endl;
	}

	//--------����AuthQueryStatus�ӿ�(���������ѯ��Ȩ״̬ ,�ɹ�������Ȩ license ��check_code)--------
	//	AYJ_PAICS_LIB_API int AuthQueryStatus(tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkAuthActiveTest, AuthQueryStatus) {
		tagCallBackPara tagTmp;////	ͨ�ûص�����
		tagTmp.nActionId = 1;//����ID��Ϊ1����ʾ��ȡUkey����
		int ret = AYJ::AuthQueryStatus(tagTmp);
		cout << "tagTmp:" << tagTmp.pCallBackFun << endl;
		EXPECT_EQ(0, ret) << "���������ѯ��Ȩ״̬ ,�ɹ�������Ȩ license ��check_code ʧ��" << endl;
	}

	//--------����AuthGetOderInfo�ӿ�(��ȡ������Ϣ)--------
	//	AYJ_PAICS_LIB_API int AuthGetOderInfo(const char* _szDevId, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkAuthActiveTest, AuthGetOderInfo) {
		tagCallBackPara tagTmp;////	ͨ�ûص�����
		tagTmp.nActionId = 2;//����ID��Ϊ2����ʾ��ȡ������Ϣ
		int ret = AYJ::AuthGetOderInfo(szDevId, tagTmp);
		cout << "tagTmp:" << tagTmp.pCallBackFun << endl;
		EXPECT_EQ(0, ret) << "��ȡ������Ϣʧ��" << endl;
	}


	//--------����AuthCreateLicence�ӿ�(����֤�� (������Ȩ))--------
	//	AYJ_PAICS_LIB_API int AuthCreateLicence(const char* _szAuthKeyId, const char* _szDevId, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkAuthActiveTest, AuthCreateLicence) {
		const char* szUkeyId = strAuthUkeyId.c_str();
		tagCallBackPara tagTmp;////	ͨ�ûص�����
		tagTmp.nActionId = 3;//����ID��Ϊ3����ʾ��ȡlicence
		int ret = AYJ::AuthCreateLicence(szUkeyId, szDevId, tagTmp);
		cout << "szUkeyId:" << szUkeyId << ",szDevId:" << szDevId << endl;
		cout << "tagTmp:" << tagTmp.pCallBackFun << endl;
		EXPECT_EQ(0, ret) << "����֤�� (������Ȩ) ʧ��" << endl;
	}

	//--------����AuthQueryActivateStatus�ӿ�(��ѯ����״̬�� δ��� �Ѽ���   
	//(�����������棬 ���δ������������и���) {"code":0,"data":{"state":1},"msg":"�豸�Ѽ���"})--------
	//	AYJ_PAICS_LIB_API int AuthQueryActivateStatus(const char* _szDevId, const char* _szAuthNum,  tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkAuthActiveTest, AuthQueryActivateStatus) {
		const char* szUkeyId = strAuthUkeyId.c_str();
		tagCallBackPara tagTmp;////	ͨ�ûص�����
		tagTmp.nActionId = 3;//����ID��Ϊ3����ʾ��ȡlicence
		int ret = AYJ::AuthQueryActivateStatus(szUkeyId, szAuthNum, tagTmp);
		cout << "szUkeyId:" << szUkeyId << ",szAuthNum:" << szAuthNum << endl;
		cout << "tagTmp:" << tagTmp.pCallBackFun << endl;
		EXPECT_EQ(0, ret) << "��ѯ����״̬ ʧ��" << endl;
	}


}