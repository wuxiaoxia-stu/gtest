#include "pch.h"
#include <stdio.h>
#include <iostream>
#include "testAyjGlobalData.h"

using namespace AYJ;
using namespace std;


namespace AyjPaicsSdkUser {

	//CJsonUtil jsonutil;//ʵ����CJsonUtil
	stuConfigData	teststuConfigData;										//�����ļ���������
	const char*		szAuthNub = teststuConfigData.author_number;			//�ͻ�����Ȩ��
	const char*		szDevId = teststuConfigData.szDevId;					//�豸���
	std::string		strId;													//������ԿID
	//std::string		strServerAuthNum = teststuConfigData.strServerAuthNum;	//	�������Ȩ��

	/////////////////		�û�����		//////////////////

	//	��ȡ�û��б� ȫ����ȡ
	//AYJ_PAICS_LIB_API int UserListGet(tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkUserTest, UserListGet) {
		tagCallBackPara tagTemp;
		tagTemp.nActionId = 1; //��ȡ�û��б�
		EXPECT_EQ(0, UserListGet(tagTemp))
			<< "��ȡ�û��б� ʧ��" << endl;
		cout << "��ȡ�û��б�::"<< tagTemp.strData << endl;

	}

	//	�û���¼
	//AYJ_PAICS_LIB_API int UserLogin(int _nUserId, const char* _szUserPwd, const char* _szAuthNub, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkUserTest, UserLogin) {
		int _nUserId = 1;//����ԱID
		const char* _szUserPwd = "12369";//����
		tagCallBackPara tagTemp;
		tagTemp.nActionId = 2; //�û���¼
		EXPECT_EQ(0, UserLogin(_nUserId, _szUserPwd, szAuthNub, tagTemp))
			<< "�û���¼ ʧ��" << endl;
		
		cout << "�û���¼::" << tagTemp.strData.c_str() << endl;
		cout << "parseUserTokenJson" << endl;
		int ret = CJsonUtil::parseUserTokenJson(tagTemp.strData.c_str());//�����û���¼���ݣ������û�tokenֵ����Ϊ�û��˳��ӿڵ�header
		EXPECT_EQ(0, ret) <<  "�û���¼ ʧ��" << endl;//����0��¼�ɹ�
		//EXPECT_EQ(0, UserLogout(tagTemp))//�û��ǳ�
		//	<< "�û��ǳ� ʧ��" << endl;
		//cout << "�û��ǳ�::" << tagTemp.strData.c_str() << endl;
	}

	//	�û�ˢ��user token ,��¼token 2СʱʧЧ, 2Сʱˢ��һ��
	//AYJ_PAICS_LIB_API int UserRefreshToken(tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkUserTest, UserRefreshToken) {
		tagCallBackPara tagPara;
		EXPECT_EQ(0, UserRefreshToken(tagPara))
			<< "sdk�ӿ� �û�ˢ��user token ʧ��" << endl;
		cout << "�û�ˢ������::" << tagPara.strData << endl;
		int ret = CJsonUtil::parseCodeJson(tagPara.strData.c_str());
		EXPECT_EQ(0, ret) << "���ؽӿڣ��û�ˢ������ ʧ��" << endl;
	}


	//	�û��б������޸ĺ� ���浽��������ͬʱ��Ҫ���浽������Կ
	//AYJ_PAICS_LIB_API int UserListSave(const char* _szUserDataJson, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkUserTest, UserListSave){
		tagCallBackPara tagTemp;
		UserListGet(tagTemp);//��ȡ�б���Ϣ
		int nRetListSave = UserListSave(tagTemp.strData.c_str(), tagTemp);
		EXPECT_EQ(0, nRetListSave) << "sdk�ӿڣ��û��б������޸ĺ� ���浽��������ͬʱ��Ҫ���浽������Կ ʧ��" << endl;
		//int nRetServer = CJsonUtil::parseCodeJson(_strUserDataJson.c_str());
		//EXPECT_EQ(0, nRetServer) << "�Ʒ���ӿڣ�����������Կ����Ϣ ʧ��" << endl;
	}

	//	�û��˳���¼
	//AYJ_PAICS_LIB_API int UserLogout(tagCallBackPara& _objPara);
	TEST(AyjPaicsSdkUserTest, UserLogout) {
		tagCallBackPara tagTmp;
		EXPECT_EQ(0, UserLogout(tagTmp))
			<< "sdk�ӿڣ��û��ǳ� ʧ��" << endl;
		cout << "�û��ǳ�: " << tagTmp.strData << endl;
		int ret = CJsonUtil::parseCodeJson(tagTmp.strData.c_str());
		EXPECT_EQ(0, ret) << "����ӿڣ��û��˳� ʧ��" << endl;
	}

	/////////////////		������Կ����		//////////////////

	//	��ȡ������Կ����
	//AYJ_PAICS_LIB_API int LeaderKeyGetCount();
	TEST(AyjPaicsSdkLeaderTest, LeaderKeyGetCount) {
		int nRet = LeaderKeyGetCount();
		EXPECT_EQ(0, nRet) << "sdk�ӿڣ���ȡ������Կ���� ʧ��" << endl;
	}

	//	��ȡ������Կid
	//AYJ_PAICS_LIB_API int LeaderKeyGetId(std::string& _strKeyId);
	//	��ȡ������Կ��Ϣ.���ƶ˷���������ȡ������Կ��״̬
	//AYJ_PAICS_LIB_API int LeaderKeyGetInfo(const std::string& _strKeyId, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkLeaderTest, LeaderKeyGetIdinfo) {
		int nRetGetId = LeaderKeyGetId(strId);
		cout << "������Կid: " << strId << endl;
		EXPECT_EQ(0, nRetGetId) << "sdk�ӿڣ���ȡ������Կid ʧ��" << endl;

		tagCallBackPara tagTmp;
		int nRetGetInfo = AYJ::LeaderKeyGetInfo(strId, tagTmp);
		EXPECT_EQ(0, nRetGetInfo) << "sdk�ӿڣ���ȡ������Կ��Ϣ ʧ��" << endl;
		cout << "������Կ��Ϣ: " << tagTmp.strData << endl;
		int nRetServer = CJsonUtil::parseCodeJson(tagTmp.strData.c_str());
		EXPECT_EQ(0, nRetServer) << "����ӿڣ���ȡ������Կ��״̬ ʧ��" << endl;
	}

	//	��ȡ������Կ�ڲ� �û������б�
	//AYJ_PAICS_LIB_API int LeaderKeyGetUserData(std::string& _strUserDataJson);

	//	���� �û��б�����	��������Կ, ����������ɹ����ٱ��浽������Կ
	//AYJ_PAICS_LIB_API int LeaderKeySaveUserData(std::string& _strUserDataJson);

	TEST(AyjPaicsSdkLeaderTest, LeaderKeyGetSaveUserData) {
		std::string _strUserDataJson = "";
		int nRetGetUserData = AYJ::LeaderKeyGetUserData(_strUserDataJson);
		//cout << "�û������б�: " << _strUserDataJson << endl;
		EXPECT_EQ(0, nRetGetUserData) << "sdk�ӿڣ���ȡ������Կ�ڲ� �û������б� ʧ��" << endl;
		int nRetSaveUserData = AYJ::LeaderKeySaveUserData(_strUserDataJson);
		EXPECT_EQ(0, nRetSaveUserData) << "sdk�ӿڣ����� �û��б�����	��������Կ, ����������ɹ����ٱ��浽������Կ ʧ��" << endl;
		//cout << "������û������б�: " << _strUserDataJson << endl;

	}

	//	��ѯ������Կ��״̬
	//AYJ_PAICS_LIB_API int LeaderKeyQueryState(const char*_szAuthNub, tagCallBackPara& _objPara);
	TEST(AyjPaicsSdkLeaderTest, LeaderKeyQueryState) {
		const char*		szAuthNub = teststuConfigData.author_number;
		tagCallBackPara tagTmp;
		int nRet = AYJ::LeaderKeyQueryState(szAuthNub, tagTmp);
		EXPECT_EQ(0, nRet) << "sdk�ӿڣ���ѯ������Կ��״̬ ʧ��" << endl;
		int nRetServer = CJsonUtil::parseCodeJson(tagTmp.strData.c_str());
		EXPECT_EQ(0, nRetServer) << "����ӿڣ���ѯ������Կ��״̬ ʧ��" << endl;
	}

	//	��������Կ�����ط�����
	//AYJ_PAICS_LIB_API int LeaderKeyBind(const char*_szKeyId, const char* _szAuthNub, const char* _szUserData, tagCallBackPara& _objPara);
	TEST(AyjPaicsSdkLeaderTest, LeaderKeyBind) {
		tagCallBackPara tagTmp;
		int nRetGetId = LeaderKeyGetId(strId);
		const char* szAuthNub = teststuConfigData.author_number;
		AYJ::LeaderKeyGetInfo(strId, tagTmp);
		int nRet = AYJ::LeaderKeyBind(strId.c_str(), szAuthNub, tagTmp.strData.c_str(), tagTmp);
		EXPECT_EQ(0, nRet) << "sdk�ӿڣ���������Կ�����ط����� ʧ��" << endl;
		int nRetServer = CJsonUtil::parseMsgJson(tagTmp.strData.c_str());
		EXPECT_EQ(0, nRetServer) << "����ӿڣ���ѯ������Կ��״̬ ʧ��" << endl;
	}

	/////////////////		�ͻ�����Բ���		//////////////////
	//	��ѯ���״̬
	//AYJ_PAICS_LIB_API int PairQureyStatus(const char* _szAuthNub, const char* _szDevId, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkPairTest, PairQureyStatus) {
		tagCallBackPara tagTmp;
		int nRet = PairQureyStatus(szAuthNub, szDevId, tagTmp);
		EXPECT_EQ(0, nRet) << "sdk�ӿڣ���ѯ���״̬ ʧ��" << endl;
		int nRetServer = CJsonUtil::parsePairStatus(tagTmp.strData.c_str(), teststuConfigData.strServerAuthNum);//�ɹ�����0�������޸����˷�����Ȩ���ֵ
		cout << "teststuConfigData.strServerAuthNum:" << teststuConfigData.strServerAuthNum << endl;
		EXPECT_EQ(0, nRetServer) << "����ӿڣ���ѯ���״̬ ʧ��" << endl;
	}
	
	//	������
	//AYJ_PAICS_LIB_API int PairBreak(const char* _szAuthNub, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkPairTest, PairBreak) {
		tagCallBackPara tagTmp;
		int nRet = PairBreak(szAuthNub, tagTmp);
		EXPECT_EQ(0, nRet) << "sdk�ӿڣ������� ʧ��" << endl;
		int nRetServer = CJsonUtil::parseCodeJson(tagTmp.strData.c_str());
		EXPECT_EQ(0, nRetServer) << "����ӿڣ���ѯ������Կ��״̬ ʧ��" << endl;

	}

	//	�������
	//AYJ_PAICS_LIB_API int PairApply(const char* _szAuthNub, const char* _szDevId, tagCallBackPara& _objCbPara);
	TEST(AyjPaicsSdkPairTest, PairApply) {
		tagCallBackPara tagTmp;
		int nRet = PairApply(szAuthNub, szDevId, tagTmp);
		EXPECT_EQ(0, nRet) << "sdk�ӿڣ�������� ʧ��" << endl;
		int nRetServer = CJsonUtil::parseCodeJson(tagTmp.strData.c_str());
		EXPECT_EQ(0, nRetServer) << "����ӿڣ���ѯ������Կ��״̬ ʧ��" << endl;
	}
}
