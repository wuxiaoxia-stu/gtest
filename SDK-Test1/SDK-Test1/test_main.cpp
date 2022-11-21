#include "pch.h"
#include "AyjPaicsSdkPublic.h"


//全局的事件机制(针对整个测试程序)
class SdkEnvironment :public testing::Environment
{
public:
	//SetUp()函数是在所有测试开始前执行。
	virtual void SetUp()
	{
		stuConfigData testConfigData;
		std::cout << "Sdk SdkEnvironment SetUP" << std::endl;
		int result = AYJ::SdkInit(5, "sdk", 5);//初始化sdk
		ASSERT_EQ(0, result) << "初始化sdk失败" << "返回值：" << result << std::endl;
		EXPECT_EQ(0, AYJ::SdkSetCloudAddr(testConfigData.cloud_ip, testConfigData.cloud_port));
		EXPECT_EQ(0, AYJ::SdkSetLocalAddr(testConfigData.local_ip, testConfigData.local_port));

		int _nUserId = 1;//管理员ID
		const char* _szUserPwd = "12369";//密码
		tagCallBackPara tagTemp;
		EXPECT_EQ(0, AYJ::UserLogin(_nUserId, _szUserPwd, testConfigData.author_number, tagTemp))
			<< "用户登录 失败" << std::endl;
		int ret = CJsonUtil::parseUserTokenJson(tagTemp.strData.c_str());//解释用户登录数据，设置用户token值，作为用户退出接口的header

	}
	//TearDown()函数是在所有测试结束后执行。
	virtual void TearDown()
	{
		std::cout << "Sdk SdkEnvironment TearDown" << std::endl;
		int result = AYJ::SdkRelease();//释放sdk
		ASSERT_EQ(0, result) << "释放sdk失败" << "返回值：" << result << std::endl;
	}
};

int main(int argc, char* argv[])
{
	printf("Running main() from %s\n", __FILE__);
	testing::AddGlobalTestEnvironment(new SdkEnvironment);//注册全局事件
	

	//testing::GTEST_FLAG(filter) = "-Class1Test.*";//运行测试应跳过Class1Test测试用例中的所有测试

	//testing::GTEST_FLAG(filter) = "-testSdkInit.*";//跳过testSdkInit的用例

	//testing::GTEST_FLAG(filter) = "AyjPaicsSdkPublicTest*:AyjPaicsSdkUserTest*";//只运行SdkTest用例集
	testing::GTEST_FLAG(filter) = "testAyjPaicsSdkCase*";//只运行SdkTest用例集

	testing::GTEST_FLAG(output) = "xml:I:/bd/googletest-release-1.8.1/SDK_new/xml/sdk_new.xml";  // 指定报告输出路径,这句放置InitGoogleTest之前
	//testing::GTEST_FLAG(output) = "xml:d:/1.xml";//这句放置InitGoogleTest之前
	testing::InitGoogleTest(&argc, argv); 

	return RUN_ALL_TESTS();//运行全部测试用例
}