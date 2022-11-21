//����ͷ�ļ�
#include <iostream>
//#include <string>
#include "pch.h" 
#include "AyjPaicsSdkPublic.h"
#include "testAyjPaicsSdkPublic.h"



using namespace std;
using namespace AYJ;	//ʹ�������ռ�AYJ
using testing::Values;
using testing::Types;


namespace AyjPaicsSdkPublicTest {
	//---����SdkInit�ӿں�SdkRelease�ӿ�---

	//����1-������ʼ��sdk,��ʼ���ɹ�����0
	TEST(testSdkInit, SdkInit_normal) {
		cout << endl << endl;
		cout << "����1-������ʼ��sdk,��ʼ���ɹ�����0" << endl;
		int result = SdkInit(5, "sdk", 5);
		ASSERT_EQ(0, result) << "��ʼ��sdkʧ��" << "����ֵ��" << result << endl;
		if (result == 0) {
			int result_SdkRelease = SdkRelease();	//�ͷ�sdk
			cout << "�ͷ�sdk�ķ���ֵ��" << result_SdkRelease << endl;
		}
	}

	//����2-��ʼ��sdk����־�����쳣,����ֵΪ0
	TEST(testSdkInit, SdkInit_nLogLevel) {
		cout << endl << endl;
		cout << "����2-��ʼ��sdk����־�����쳣,����ֵ��Ϊ0" << endl;
		int nLogLevel[3] = { -1, 6, NULL };
		for (int i = 0; i < 3; i++) {
			int result = SdkInit(nLogLevel[i], "sdk", 5);
			EXPECT_EQ(0, result) << "��־����Ϊ��" << nLogLevel[i] << "����ֵ��" << result << endl;
			if (result == 0) {
				SdkRelease();	//�ͷ�sdk
			}
		}
	}

	//����3-��ʼ��sdk����־�����쳣,����ֵΪ0
	TEST(testSdkInit, SdkInit_pLogName) {
		cout << endl << endl;
		cout << "����3-��ʼ��sdk����־�����쳣,����ֵ��Ϊ0" << endl;
		char* pLogName[3] = { "", u8"����", NULL };//�ַ�������
		for (int i = 0; i < 3; i++) {
			int result = SdkInit(5, pLogName[i], 5);
			EXPECT_EQ(0, result) << "��־����Ϊ��" << pLogName[i] << "����ֵ��" << result << endl;
			if (result == 0) {
				SdkRelease();	//�ͷ�sdk
			}
		}
	}

	//����4-��ʼ��sdk����ʱʱ���쳣,����ֵΪ0��NULL��ʾ0
	TEST(testSdkInit, SdkInit_nHttpTimeOut) {
		cout << endl << endl;
		cout << "����4-��ʼ��sdk����ʱʱ���쳣,����ֵ��Ϊ0��NULL��ʾ0" << endl;
		int nHttpTimeOut[3] = { -2147483648, 2147483647, NULL };//�ַ�������
		for (int i = 0; i < 3; i++) {
			int result = SdkInit(5, "sdk", nHttpTimeOut[i]);
			EXPECT_EQ(0, result) << "ʱ��Ϊ��" << nHttpTimeOut[i] << " ����ֵ��" << result << endl;
			if (result == 0) {
				SdkRelease();	//�ͷ�sdk
			}
		}
	}
}
//
//---TEST�꣬����SdkSetCloudAddr�ӿ�---
TEST(SdkSetCloudAddrTest1, DISABLED_SdkSetCloudAddr_positive) {
	//cout << "����1-���������ƶ�IP �� �˿�,Ӧ����������" << endl;
	const char* _szCloudIp = "192.168.1.8";
	int _nCloudPort = 8005;
	EXPECT_EQ(0, SdkSetCloudAddr(_szCloudIp, _nCloudPort))
		<< "�����ƶ�IP:" << _szCloudIp << " �˿ڣ�" << _nCloudPort << "ʧ��" << endl;
}

//--------����SdkSetCloudAddr�ӿ�(�����ƶ�IP �� �˿�)--------

//�������ڶ������ڲ����У�ʹ��TestWithParam <T>���GetParam�����������ʲ��Բ�����
TEST_P(SdkSetCloudAddrTest, SdkSetCloudAddr) {
	////const char* _szCloudIp = GetParam();
	////int _nCloudPort = 8005;
	//const char* _szCloudIp = GetParam()._szCloudIp;
	//int _nCloudPort = GetParam()._nCloudPort;
	/*EXPECT_EQ(0, SdkSetCloudAddr(_szCloudIp, _nCloudPort))
	<< "�����ƶ�IP:" << _szCloudIp << " �˿ڣ�" << _nCloudPort << "ʧ��" << endl;*/
	EXPECT_EQ(0, SdkSetCloudAddr(SdkSetAddrStructTest._szchar, SdkSetAddrStructTest._nint))
		<< "�����ƶ�IP:" << SdkSetAddrStructTest._szchar << " �˿ڣ�" << SdkSetAddrStructTest._nint << "ʧ��" << endl;
}


//����������������һ��������ǰ׺���ڶ������������������ǲ���������
//��ע�⣬INSTANTIATE_TEST_CASE_P��ʵ�����������������е����в��ԣ�
//�������ǵĶ�������INSTANTIATE_TEST_CASE_P���֮ǰ����֮��

INSTANTIATE_TEST_CASE_P(OnThePublicSetCloudAddr,
	SdkSetCloudAddrTest,
	Values(SdkSetAddrStruct{ "192.168.1.8", 8005 }, SdkSetAddrStruct{ "" , 8005 },
		SdkSetAddrStruct{ "192.168.1.8", NULL }, SdkSetAddrStruct{ "", NULL }));

//--------����SdkSetLocalAddr�ӿڣ����ñ��ط����� IP �� �˿ڣ�--------

TEST_P(SdkSetLocalAddrTest, SdkSetLocalAddr) {
	EXPECT_EQ(0, SdkSetLocalAddr(SdkSetAddrStructTest._szchar, SdkSetAddrStructTest._nint))
		<< "���ñ��ط�����IP:" << SdkSetAddrStructTest._szchar << " �˿ڣ�" << SdkSetAddrStructTest._nint << "ʧ��" << endl;
}

INSTANTIATE_TEST_CASE_P(OnThePublicSetLocalAddr,
	SdkSetLocalAddrTest,
	Values(SdkSetAddrStruct{ "127.0.0.1", 8007 }, SdkSetAddrStruct{ "", 8007 },
		SdkSetAddrStruct{ "127.0.0.1", NULL }, SdkSetAddrStruct{ "", NULL }));

//--------����SdkSetLicenceNumber�ӿڣ�����֤�� ΨһID, ��Ȩ�ɹ���������������Ҫ���ã�--------
TEST_P(SdkSetLicenceNumberTest, SdkSetLicenceNumber) {
	EXPECT_EQ(0, SdkSetLicenceNumber(_szchar))
		<< "����֤�� ΨһID:" << _szchar << "ʧ��" << endl;
}

INSTANTIATE_TEST_CASE_P(OnThePublicSetLicenceNumber,
	SdkSetLicenceNumberTest,
	Values("0123456789abcABC", "", "~!@#$%^&*()_+;''"));

//--------����SdkSetAuthNumber�ӿڣ�������Ȩ ΨһID, ��Ȩ�ɹ���������������Ҫ���ã�--------
TEST_P(SdkSetAuthNumberTest, SdkSetAuthNumber) {
	EXPECT_EQ(0, SdkSetAuthNumber(_szchar))
		<< "������Ȩ ΨһID:" << _szchar << "ʧ��" << endl;
}

INSTANTIATE_TEST_CASE_P(OnThePublicSetAuthNumber,
	SdkSetAuthNumberTest,
	Values("22050003_C", ""));


//--------����SdkSetUserToken�ӿڣ������û���¼���token,  2Сʱ token ʧЧ, ��Ҫ���»�ȡ��--------
TEST_P(SdkSetUserTokenTest, SdkSetUserToken) {
	EXPECT_EQ(0, SdkSetUserToken(_szchar))
		<< "�����û���¼���token:" << _szchar << "ʧ��" << endl;
}

INSTANTIATE_TEST_CASE_P(OnThePublicSetUserToken,
	SdkSetUserTokenTest,
	Values("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6IjAwMDIwMDAzIiwidXVpZCI6IjRhY2E5ZWMwLTZiMTEtNDlmMi05N2U2LTEzMzIxZmRlNmUxMyIsInVpZCI6MCwic3RhdGUiOjEsImF1dGhvcl9udW1iZXIiOiIyMjA1MDAwM19DIiwidGVhbSI6MSwiZXhwIjoxNjU4OTM1MjE2LCJpc3MiOiJnaW4tYmxvZyJ9.4shkXtdoao5EUh4fZ8VsV-WpBMSvrU3aFOyymbLun9w", ""));

//--------����SdkGetClientVer�ӿڣ���ȡ�ͻ��� �����汾 �� ���װ汾��--------
TEST(SdkGetClientVerTest, SdkGetClientVer) {
	string str_ver1 = "PUS S300";//string��ֵ����
	string str_ver2 = "V_1.0.1.0713";//string��ֵ����
	EXPECT_EQ(0, SdkGetClientVer(str_ver1, str_ver2))
		<< "��ȡ�ͻ��� �����汾 �� ���װ汾" << str_ver1 << str_ver2 << "ʧ��" << endl;
	EXPECT_EQ(0, SdkGetClientVer(string(""), string("")))
		<< "��ȡ�ͻ��� �����汾 �� ���װ汾��Ϊ��" << "ʧ��" << endl;
}

//--------����SdkGetProductName�ӿڣ���ȡ ��Ʒ���ƣ�--------
TEST(SdkGetProductNameTest, SdkGetProductName) {
	string str_ver1 = "PUS S300";//string��ֵ����
	EXPECT_EQ(0, SdkGetProductName(str_ver1))
		<< "��ȡ ��Ʒ����" << str_ver1 << "ʧ��" << endl;
	EXPECT_EQ(0, SdkGetProductName(string("")))
		<< "��ȡ ��Ʒ����" << "ʧ��" << endl;
}