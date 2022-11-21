//导入头文件
#include <iostream>
//#include <string>
#include "pch.h" 
#include "AyjPaicsSdkPublic.h"


using namespace std;
using namespace AYJ;	//使用命名空间AYJ
using testing::Values;
using testing::Types;



namespace AyjPaicsSdkPublic {

	stuConfigData testConfigData;

	//---TEST宏，测试SdkSetCloudAddr接口---
	//AYJ_PAICS_LIB_API int SdkSetCloudAddr(const char* _szCloudIp, int _nCloudPort);
	TEST(AyjPaicsSdkPublicTest, SdkSetCloudAddr) {
		EXPECT_EQ(0, SdkSetCloudAddr(testConfigData.cloud_ip, testConfigData.cloud_port))
			<< "设置云端IP:" << testConfigData.cloud_ip << " 端口：" << testConfigData.cloud_port << "失败" << endl;
	}

	//--------测试SdkSetLocalAddr接口（设置本地服务器 IP 与 端口）--------
	//AYJ_PAICS_LIB_API int SdkSetLocalAddr(const char* _szLocalIp, int _nLocalPort);
	TEST(AyjPaicsSdkPublicTest, SdkSetLocalAddr) {
		EXPECT_EQ(0, SdkSetLocalAddr(testConfigData.local_ip, testConfigData.local_port))
			<< "设置本地服务器IP:" << testConfigData.local_ip << " 端口：" << testConfigData.local_port << "失败" << endl;
	}

	//--------测试SdkSetLicenceNumber接口（设置证书 唯一ID, 授权成功后或程序启动后，需要设置）--------
	//AYJ_PAICS_LIB_API int SdkSetLicenceNumber(const char* _szLicenceNumber);
	TEST(AyjPaicsSdkPublicTest, SdkSetLicenceNumber) {
		EXPECT_EQ(0, SdkSetLicenceNumber(testConfigData.licence))
			<< "设置证书 唯一ID:" << testConfigData.licence << "失败" << endl;
	}

	//--------测试SdkSetAuthNumber接口（设置授权 唯一ID, 授权成功后或程序启动后，需要设置）--------
	//AYJ_PAICS_LIB_API int SdkSetAuthNumber(const char* _szAuthNumber);
	TEST(AyjPaicsSdkPublicTest, SdkSetAuthNumber) {
		EXPECT_EQ(0, SdkSetAuthNumber(testConfigData.author_number))
			<< "设置授权 唯一ID:" << testConfigData.author_number << "失败" << endl;
	}

	//--------测试SdkSetUserToken接口（设置用户登录后的token,  2小时 token 失效, 需要重新获取）--------
	//AYJ_PAICS_LIB_API int SdkSetUserToken(const char* _szUserToken);
	TEST(AyjPaicsSdkPublicTest, SdkSetUserToken) {
		EXPECT_EQ(0, SdkSetUserToken(testConfigData.user_token))
			<< "设置用户登录后的token:" << testConfigData.user_token << "失败" << endl;
	}

	//--------测试SdkGetClientVer接口（获取客户端 完整版本 与 简易版本）--------
	//AYJ_PAICS_LIB_API int SdkGetClientVer(std::string& _strVer, std::string& _strVerEx);
	TEST(AyjPaicsSdkPublicTest, SdkGetClientVer) {
		EXPECT_EQ(0, SdkGetClientVer(testConfigData.strProductVerEx, testConfigData.strProductVer));
	}

	//--------测试SdkGetProductName接口（获取 产品名称）--------
	//AYJ_PAICS_LIB_API int SdkGetProductName(std::string& _strProductName);
	TEST(AyjPaicsSdkPublicTest, SdkGetProductName) {
		EXPECT_EQ(0, SdkGetProductName(testConfigData.strProductName));
	}
}