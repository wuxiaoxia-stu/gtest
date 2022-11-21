#include "pch.h"
#include "AyjPaicsSdkPublic.h"


//ȫ�ֵ��¼�����(����������Գ���)
class SdkEnvironment :public testing::Environment
{
public:
	//SetUp()�����������в��Կ�ʼǰִ�С�
	virtual void SetUp()
	{
		stuConfigData testConfigData;
		std::cout << "Sdk SdkEnvironment SetUP" << std::endl;
		int result = AYJ::SdkInit(5, "sdk", 5);//��ʼ��sdk
		ASSERT_EQ(0, result) << "��ʼ��sdkʧ��" << "����ֵ��" << result << std::endl;
		EXPECT_EQ(0, AYJ::SdkSetCloudAddr(testConfigData.cloud_ip, testConfigData.cloud_port));
		EXPECT_EQ(0, AYJ::SdkSetLocalAddr(testConfigData.local_ip, testConfigData.local_port));

		int _nUserId = 1;//����ԱID
		const char* _szUserPwd = "12369";//����
		tagCallBackPara tagTemp;
		EXPECT_EQ(0, AYJ::UserLogin(_nUserId, _szUserPwd, testConfigData.author_number, tagTemp))
			<< "�û���¼ ʧ��" << std::endl;
		int ret = CJsonUtil::parseUserTokenJson(tagTemp.strData.c_str());//�����û���¼���ݣ������û�tokenֵ����Ϊ�û��˳��ӿڵ�header

	}
	//TearDown()�����������в��Խ�����ִ�С�
	virtual void TearDown()
	{
		std::cout << "Sdk SdkEnvironment TearDown" << std::endl;
		int result = AYJ::SdkRelease();//�ͷ�sdk
		ASSERT_EQ(0, result) << "�ͷ�sdkʧ��" << "����ֵ��" << result << std::endl;
	}
};

int main(int argc, char* argv[])
{
	printf("Running main() from %s\n", __FILE__);
	testing::AddGlobalTestEnvironment(new SdkEnvironment);//ע��ȫ���¼�
	

	//testing::GTEST_FLAG(filter) = "-Class1Test.*";//���в���Ӧ����Class1Test���������е����в���

	//testing::GTEST_FLAG(filter) = "-testSdkInit.*";//����testSdkInit������

	//testing::GTEST_FLAG(filter) = "AyjPaicsSdkPublicTest*:AyjPaicsSdkUserTest*";//ֻ����SdkTest������
	testing::GTEST_FLAG(filter) = "testAyjPaicsSdkCase*";//ֻ����SdkTest������

	testing::GTEST_FLAG(output) = "xml:I:/bd/googletest-release-1.8.1/SDK_new/xml/sdk_new.xml";  // ָ���������·��,������InitGoogleTest֮ǰ
	//testing::GTEST_FLAG(output) = "xml:d:/1.xml";//������InitGoogleTest֮ǰ
	testing::InitGoogleTest(&argc, argv); 

	return RUN_ALL_TESTS();//����ȫ����������
}