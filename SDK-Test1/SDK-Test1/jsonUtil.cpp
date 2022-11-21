#include <stdio.h>
#include <iostream>
#include "json/json.h"
#include <string>
#include "jsonUtil.h"

using namespace std;
using namespace neb;

// json ������
Json::Reader reader;//Json::Reader����ͨ����JsonԴĿ����н������õ�һ���������˵�Json::Value��ͨ���ַ��������ļ�������������ΪԴĿ�ꡣ
// json ������
Json::Value root;//Json::Value ������ʾJson�е��κ�һ��value������������


CJsonUtil::CJsonUtil()
{
}

CJsonUtil::~CJsonUtil()
{
}

int CJsonUtil::parseUserTokenJson(const char* str)
{

	//// �� str ������ root 
	if (reader.parse(str, root))
	{
		if (!root["data"].isNull())//���data��Ϊnull�������û�tokenֵ
		{
			string token = root["data"]["token"].asString();
			AYJ::SdkSetUserToken(token.c_str());
			cout << "SdkSetUserToken = " << AYJ::SdkSetUserToken(token.c_str()) << endl;
			cout << token << endl;
			return AYJ::SdkSetUserToken(token.c_str());//�ɹ�����0
		}
		else
		{
			cout << "data:" << root["data"] << endl;
			return -1;//��¼ʧ�ܷ���-1
		}
	}
}

int CJsonUtil::parseCodeJson(const char* str)
{


	//���ַ����ж�ȡ����  
	if (reader.parse(str, root))
	{
		if (!root["code"] == 0)//���server_author_number��Ϊnull�������û�server_author_numberֵ
		{
			return 0;//�ɹ�����0
		}
		else
		{
			cout << "code:" << root["code"] << endl;
			return -1;//��¼ʧ�ܷ���-1
		}
	}
}


int CJsonUtil::parseMsgJson(const char* str)
{
	//���ַ����ж�ȡ����  
	if (reader.parse(str, root))
	{
		string Msg = root["msg"].asString();
		int code = root["code"].asInt();
		if (Msg == "ok")//���MsgΪok���ɹ�
		{
			return 0;//�ɹ�����0
		}
		else
		{
			cout << "msg:" << Msg << endl;
			return -1;//���Msg��Ϊok��ʧ��
		}
	}
}

int CJsonUtil::parsePairStatus(const char* str, std::string &strServerAuthNum)
{
	//���ַ����ж�ȡ����  
	if (reader.parse(str, root))
	{
		
		if (!root["data"]["server_author_number"].isNull())////���server_author_number��Ϊnull�������û�server_author_numberֵ
		{
			strServerAuthNum = root["data"]["server_author_number"].asString();
			return 0;//�ɹ�����0
		}
		else
		{
			cout << "strServerAuthNum:NULL" << endl;
			return -1;//ʧ�ܷ���-1
		}
	}

}


int CJsonUtil::parseCheckInfo(const char* str, neb::CJsonObject& oJson)
{
	neb::CJsonObject oJsonData(str);
	std::string strData = oJsonData.ToString();
	cout << "strData" << strData << endl;
	if (oJsonData["data"].IsEmpty())
	{
		cout << "IsEmpty" << endl;
		return -1;
	}
	else
	{
		oJson = oJsonData["data"];
		//std::cout << "oJson:" << oJson.ToString() << endl;
		return 0;
	}
	//return -2;
}

//	���� ��ʼ����������ļ����Ϣ
int CJsonUtil::parseOnStartCaseCheckInfo(neb::CJsonObject &oJson, tagCaseCreateInfo& _objCheckInfo)
{
	neb::CJsonObject oJsonData = oJson;
	if (oJsonData.IsEmpty())
		return -1;
	
	if (oJsonData.KeyExist("check_type"))
		_objCheckInfo.nCaseType = std::stoi(oJsonData["check_type"].ToString()); // �������id�� �������ּ������

	if (oJsonData.KeyExist("check_id"))
	{
		_objCheckInfo.nCaseCheckId = std::stoi(oJsonData["check_id"].ToString()); // ���id�� �������ּ�鼶��

	}

	return 0;
}
