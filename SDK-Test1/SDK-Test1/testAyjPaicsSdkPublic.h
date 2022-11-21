#pragma once
#include "gtest/gtest.h"
#include <list>
#include <string>


using ::testing::TestWithParam;

struct SdkSetAddrStruct
{
	const char* _szchar;
	int _nint;
};


//定义SdkSetCloudAddrTest类
class SdkSetCloudAddrTest : public ::testing::TestWithParam<struct SdkSetAddrStruct>
{
	//在这里面可以实现fixture类的所有成员
protected:
	virtual void SetUp() {
		SdkSetAddrStructTest._szchar = GetParam()._szchar;
		SdkSetAddrStructTest._nint = GetParam()._nint;
	}
	virtual void TearDown() {}

	struct SdkSetAddrStruct SdkSetAddrStructTest;
};

//定义SdkSetLocalAddrTest类,继承SdkSetAddrTest
class SdkSetLocalAddrTest : public SdkSetCloudAddrTest
{
};

//定义SdkSetLicenceNumberTest类
class SdkSetLicenceNumberTest : public ::testing::TestWithParam<const char*>
{
protected:
	virtual void SetUp() {
		_szchar = GetParam();
	}
	virtual void TearDown() {}
	const char* _szchar;
};

//定义SdkSetLicenceNumberTest类
class SdkSetAuthNumberTest : public SdkSetLicenceNumberTest
{
};

//定义SdkSetUserToken类
class SdkSetUserTokenTest : public SdkSetLicenceNumberTest
{
};

//定义SdkGetProductName类
class SdkGetClientVerTest : public ::testing::TestWithParam<std::string> {

};



