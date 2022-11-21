//����ͷ�ļ�
#include <iostream>
//#include <string>
#include "pch.h" 
#include "AyjPaicsSdkPublic.h"


using namespace std;
using namespace AYJ;	//ʹ�������ռ�AYJ
using testing::Values;
using testing::Types;



namespace AyjPaicsSdkPublic {

	stuConfigData testConfigData;

	//---TEST�꣬����SdkSetCloudAddr�ӿ�---
	//AYJ_PAICS_LIB_API int SdkSetCloudAddr(const char* _szCloudIp, int _nCloudPort);
	TEST(AyjPaicsSdkPublicTest, SdkSetCloudAddr) {
		EXPECT_EQ(0, SdkSetCloudAddr(testConfigData.cloud_ip, testConfigData.cloud_port))
			<< "�����ƶ�IP:" << testConfigData.cloud_ip << " �˿ڣ�" << testConfigData.cloud_port << "ʧ��" << endl;
	}

	//--------����SdkSetLocalAddr�ӿڣ����ñ��ط����� IP �� �˿ڣ�--------
	//AYJ_PAICS_LIB_API int SdkSetLocalAddr(const char* _szLocalIp, int _nLocalPort);
	TEST(AyjPaicsSdkPublicTest, SdkSetLocalAddr) {
		EXPECT_EQ(0, SdkSetLocalAddr(testConfigData.local_ip, testConfigData.local_port))
			<< "���ñ��ط�����IP:" << testConfigData.local_ip << " �˿ڣ�" << testConfigData.local_port << "ʧ��" << endl;
	}

	//--------����SdkSetLicenceNumber�ӿڣ�����֤�� ΨһID, ��Ȩ�ɹ���������������Ҫ���ã�--------
	//AYJ_PAICS_LIB_API int SdkSetLicenceNumber(const char* _szLicenceNumber);
	TEST(AyjPaicsSdkPublicTest, SdkSetLicenceNumber) {
		EXPECT_EQ(0, SdkSetLicenceNumber(testConfigData.licence))
			<< "����֤�� ΨһID:" << testConfigData.licence << "ʧ��" << endl;
	}

	//--------����SdkSetAuthNumber�ӿڣ�������Ȩ ΨһID, ��Ȩ�ɹ���������������Ҫ���ã�--------
	//AYJ_PAICS_LIB_API int SdkSetAuthNumber(const char* _szAuthNumber);
	TEST(AyjPaicsSdkPublicTest, SdkSetAuthNumber) {
		EXPECT_EQ(0, SdkSetAuthNumber(testConfigData.author_number))
			<< "������Ȩ ΨһID:" << testConfigData.author_number << "ʧ��" << endl;
	}

	//--------����SdkSetUserToken�ӿڣ������û���¼���token,  2Сʱ token ʧЧ, ��Ҫ���»�ȡ��--------
	//AYJ_PAICS_LIB_API int SdkSetUserToken(const char* _szUserToken);
	TEST(AyjPaicsSdkPublicTest, SdkSetUserToken) {
		EXPECT_EQ(0, SdkSetUserToken(testConfigData.user_token))
			<< "�����û���¼���token:" << testConfigData.user_token << "ʧ��" << endl;
	}

	//--------����SdkGetClientVer�ӿڣ���ȡ�ͻ��� �����汾 �� ���װ汾��--------
	//AYJ_PAICS_LIB_API int SdkGetClientVer(std::string& _strVer, std::string& _strVerEx);
	TEST(AyjPaicsSdkPublicTest, SdkGetClientVer) {
		EXPECT_EQ(0, SdkGetClientVer(testConfigData.strProductVerEx, testConfigData.strProductVer));
	}

	//--------����SdkGetProductName�ӿڣ���ȡ ��Ʒ���ƣ�--------
	//AYJ_PAICS_LIB_API int SdkGetProductName(std::string& _strProductName);
	TEST(AyjPaicsSdkPublicTest, SdkGetProductName) {
		EXPECT_EQ(0, SdkGetProductName(testConfigData.strProductName));
	}
}