//导入头文件
#include <iostream>
//#include <string>
#include "pch.h" 
#include "AyjPaicsSdkPublic.h"
#include "testAyjPaicsSdkPublic.h"



using namespace std;
using namespace AYJ;	//使用命名空间AYJ
using testing::Values;
using testing::Types;


namespace AyjPaicsSdkPublicTest {
	//---测试SdkInit接口和SdkRelease接口---

	//用例1-正常初始化sdk,初始化成功返回0
	TEST(testSdkInit, SdkInit_normal) {
		cout << endl << endl;
		cout << "用例1-正常初始化sdk,初始化成功返回0" << endl;
		int result = SdkInit(5, "sdk", 5);
		ASSERT_EQ(0, result) << "初始化sdk失败" << "返回值：" << result << endl;
		if (result == 0) {
			int result_SdkRelease = SdkRelease();	//释放sdk
			cout << "释放sdk的返回值：" << result_SdkRelease << endl;
		}
	}

	//用例2-初始化sdk，日志级别异常,返回值为0
	TEST(testSdkInit, SdkInit_nLogLevel) {
		cout << endl << endl;
		cout << "用例2-初始化sdk，日志级别异常,返回值不为0" << endl;
		int nLogLevel[3] = { -1, 6, NULL };
		for (int i = 0; i < 3; i++) {
			int result = SdkInit(nLogLevel[i], "sdk", 5);
			EXPECT_EQ(0, result) << "日志级别为：" << nLogLevel[i] << "返回值：" << result << endl;
			if (result == 0) {
				SdkRelease();	//释放sdk
			}
		}
	}

	//用例3-初始化sdk，日志名称异常,返回值为0
	TEST(testSdkInit, SdkInit_pLogName) {
		cout << endl << endl;
		cout << "用例3-初始化sdk，日志名称异常,返回值不为0" << endl;
		char* pLogName[3] = { "", u8"中文", NULL };//字符串数组
		for (int i = 0; i < 3; i++) {
			int result = SdkInit(5, pLogName[i], 5);
			EXPECT_EQ(0, result) << "日志名称为：" << pLogName[i] << "返回值：" << result << endl;
			if (result == 0) {
				SdkRelease();	//释放sdk
			}
		}
	}

	//用例4-初始化sdk，超时时间异常,返回值为0，NULL表示0
	TEST(testSdkInit, SdkInit_nHttpTimeOut) {
		cout << endl << endl;
		cout << "用例4-初始化sdk，超时时间异常,返回值不为0，NULL表示0" << endl;
		int nHttpTimeOut[3] = { -2147483648, 2147483647, NULL };//字符串数组
		for (int i = 0; i < 3; i++) {
			int result = SdkInit(5, "sdk", nHttpTimeOut[i]);
			EXPECT_EQ(0, result) << "时间为：" << nHttpTimeOut[i] << " 返回值：" << result << endl;
			if (result == 0) {
				SdkRelease();	//释放sdk
			}
		}
	}
}
//
//---TEST宏，测试SdkSetCloudAddr接口---
TEST(SdkSetCloudAddrTest1, DISABLED_SdkSetCloudAddr_positive) {
	//cout << "用例1-正常设置云端IP 与 端口,应可正常设置" << endl;
	const char* _szCloudIp = "192.168.1.8";
	int _nCloudPort = 8005;
	EXPECT_EQ(0, SdkSetCloudAddr(_szCloudIp, _nCloudPort))
		<< "设置云端IP:" << _szCloudIp << " 端口：" << _nCloudPort << "失败" << endl;
}

//--------测试SdkSetCloudAddr接口(设置云端IP 与 端口)--------

//参数化第二步，在测试中，使用TestWithParam <T>类的GetParam（）方法访问测试参数：
TEST_P(SdkSetCloudAddrTest, SdkSetCloudAddr) {
	////const char* _szCloudIp = GetParam();
	////int _nCloudPort = 8005;
	//const char* _szCloudIp = GetParam()._szCloudIp;
	//int _nCloudPort = GetParam()._nCloudPort;
	/*EXPECT_EQ(0, SdkSetCloudAddr(_szCloudIp, _nCloudPort))
	<< "设置云端IP:" << _szCloudIp << " 端口：" << _nCloudPort << "失败" << endl;*/
	EXPECT_EQ(0, SdkSetCloudAddr(SdkSetAddrStructTest._szchar, SdkSetAddrStructTest._nint))
		<< "设置云端IP:" << SdkSetAddrStructTest._szchar << " 端口：" << SdkSetAddrStructTest._nint << "失败" << endl;
}


//参数化第三步，第一个参数是前缀；第二个是类名；第三个是参数生成器
//请注意，INSTANTIATE_TEST_CASE_P将实例化给定测试用例中的所有测试，
//无论它们的定义是在INSTANTIATE_TEST_CASE_P语句之前还是之后。

INSTANTIATE_TEST_CASE_P(OnThePublicSetCloudAddr,
	SdkSetCloudAddrTest,
	Values(SdkSetAddrStruct{ "192.168.1.8", 8005 }, SdkSetAddrStruct{ "" , 8005 },
		SdkSetAddrStruct{ "192.168.1.8", NULL }, SdkSetAddrStruct{ "", NULL }));

//--------测试SdkSetLocalAddr接口（设置本地服务器 IP 与 端口）--------

TEST_P(SdkSetLocalAddrTest, SdkSetLocalAddr) {
	EXPECT_EQ(0, SdkSetLocalAddr(SdkSetAddrStructTest._szchar, SdkSetAddrStructTest._nint))
		<< "设置本地服务器IP:" << SdkSetAddrStructTest._szchar << " 端口：" << SdkSetAddrStructTest._nint << "失败" << endl;
}

INSTANTIATE_TEST_CASE_P(OnThePublicSetLocalAddr,
	SdkSetLocalAddrTest,
	Values(SdkSetAddrStruct{ "127.0.0.1", 8007 }, SdkSetAddrStruct{ "", 8007 },
		SdkSetAddrStruct{ "127.0.0.1", NULL }, SdkSetAddrStruct{ "", NULL }));

//--------测试SdkSetLicenceNumber接口（设置证书 唯一ID, 授权成功后或程序启动后，需要设置）--------
TEST_P(SdkSetLicenceNumberTest, SdkSetLicenceNumber) {
	EXPECT_EQ(0, SdkSetLicenceNumber(_szchar))
		<< "设置证书 唯一ID:" << _szchar << "失败" << endl;
}

INSTANTIATE_TEST_CASE_P(OnThePublicSetLicenceNumber,
	SdkSetLicenceNumberTest,
	Values("0123456789abcABC", "", "~!@#$%^&*()_+;''"));

//--------测试SdkSetAuthNumber接口（设置授权 唯一ID, 授权成功后或程序启动后，需要设置）--------
TEST_P(SdkSetAuthNumberTest, SdkSetAuthNumber) {
	EXPECT_EQ(0, SdkSetAuthNumber(_szchar))
		<< "设置授权 唯一ID:" << _szchar << "失败" << endl;
}

INSTANTIATE_TEST_CASE_P(OnThePublicSetAuthNumber,
	SdkSetAuthNumberTest,
	Values("22050003_C", ""));


//--------测试SdkSetUserToken接口（设置用户登录后的token,  2小时 token 失效, 需要重新获取）--------
TEST_P(SdkSetUserTokenTest, SdkSetUserToken) {
	EXPECT_EQ(0, SdkSetUserToken(_szchar))
		<< "设置用户登录后的token:" << _szchar << "失败" << endl;
}

INSTANTIATE_TEST_CASE_P(OnThePublicSetUserToken,
	SdkSetUserTokenTest,
	Values("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6IjAwMDIwMDAzIiwidXVpZCI6IjRhY2E5ZWMwLTZiMTEtNDlmMi05N2U2LTEzMzIxZmRlNmUxMyIsInVpZCI6MCwic3RhdGUiOjEsImF1dGhvcl9udW1iZXIiOiIyMjA1MDAwM19DIiwidGVhbSI6MSwiZXhwIjoxNjU4OTM1MjE2LCJpc3MiOiJnaW4tYmxvZyJ9.4shkXtdoao5EUh4fZ8VsV-WpBMSvrU3aFOyymbLun9w", ""));

//--------测试SdkGetClientVer接口（获取客户端 完整版本 与 简易版本）--------
TEST(SdkGetClientVerTest, SdkGetClientVer) {
	string str_ver1 = "PUS S300";//string赋值操作
	string str_ver2 = "V_1.0.1.0713";//string赋值操作
	EXPECT_EQ(0, SdkGetClientVer(str_ver1, str_ver2))
		<< "获取客户端 完整版本 与 简易版本" << str_ver1 << str_ver2 << "失败" << endl;
	EXPECT_EQ(0, SdkGetClientVer(string(""), string("")))
		<< "获取客户端 完整版本 与 简易版本均为空" << "失败" << endl;
}

//--------测试SdkGetProductName接口（获取 产品名称）--------
TEST(SdkGetProductNameTest, SdkGetProductName) {
	string str_ver1 = "PUS S300";//string赋值操作
	EXPECT_EQ(0, SdkGetProductName(str_ver1))
		<< "获取 产品名称" << str_ver1 << "失败" << endl;
	EXPECT_EQ(0, SdkGetProductName(string("")))
		<< "获取 产品名称" << "失败" << endl;
}