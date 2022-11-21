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


//����SdkSetCloudAddrTest��
class SdkSetCloudAddrTest : public ::testing::TestWithParam<struct SdkSetAddrStruct>
{
	//�����������ʵ��fixture������г�Ա
protected:
	virtual void SetUp() {
		SdkSetAddrStructTest._szchar = GetParam()._szchar;
		SdkSetAddrStructTest._nint = GetParam()._nint;
	}
	virtual void TearDown() {}

	struct SdkSetAddrStruct SdkSetAddrStructTest;
};

//����SdkSetLocalAddrTest��,�̳�SdkSetAddrTest
class SdkSetLocalAddrTest : public SdkSetCloudAddrTest
{
};

//����SdkSetLicenceNumberTest��
class SdkSetLicenceNumberTest : public ::testing::TestWithParam<const char*>
{
protected:
	virtual void SetUp() {
		_szchar = GetParam();
	}
	virtual void TearDown() {}
	const char* _szchar;
};

//����SdkSetLicenceNumberTest��
class SdkSetAuthNumberTest : public SdkSetLicenceNumberTest
{
};

//����SdkSetUserToken��
class SdkSetUserTokenTest : public SdkSetLicenceNumberTest
{
};

//����SdkGetProductName��
class SdkGetClientVerTest : public ::testing::TestWithParam<std::string> {

};



