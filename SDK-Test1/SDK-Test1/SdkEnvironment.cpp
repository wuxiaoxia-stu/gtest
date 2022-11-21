#include "pch.h"

class SdkEnvironment:public testing::Environment
{
public:
	virtual void SetUp()
	{
		std::cout << "Sdk SdkEnvironment SetUP" << std::endl;
		AYJ::SdkInit(5, "sdk", 5);//初始化sdk

	}
	virtual void TearDown()
	{
		std::cout << "Foo FooEnvironment TearDown" << std::endl;
		AYJ::SdkRelease();//释放sdk
	}
};