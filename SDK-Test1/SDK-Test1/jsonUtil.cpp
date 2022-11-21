#include <stdio.h>
#include <iostream>
#include "json/json.h"
#include <string>
#include "jsonUtil.h"

using namespace std;
using namespace neb;

// json 解析器
Json::Reader reader;//Json::Reader可以通过对Json源目标进行解析，得到一个解析好了的Json::Value，通常字符串或者文件输入流可以作为源目标。
// json 根对象
Json::Value root;//Json::Value 用来表示Json中的任何一种value抽象数据类型


CJsonUtil::CJsonUtil()
{
}

CJsonUtil::~CJsonUtil()
{
}

int CJsonUtil::parseUserTokenJson(const char* str)
{

	//// 将 str 解析到 root 
	if (reader.parse(str, root))
	{
		if (!root["data"].isNull())//如果data不为null，设置用户token值
		{
			string token = root["data"]["token"].asString();
			AYJ::SdkSetUserToken(token.c_str());
			cout << "SdkSetUserToken = " << AYJ::SdkSetUserToken(token.c_str()) << endl;
			cout << token << endl;
			return AYJ::SdkSetUserToken(token.c_str());//成功返回0
		}
		else
		{
			cout << "data:" << root["data"] << endl;
			return -1;//登录失败返回-1
		}
	}
}

int CJsonUtil::parseCodeJson(const char* str)
{


	//从字符串中读取数据  
	if (reader.parse(str, root))
	{
		if (!root["code"] == 0)//如果server_author_number不为null，设置用户server_author_number值
		{
			return 0;//成功返回0
		}
		else
		{
			cout << "code:" << root["code"] << endl;
			return -1;//登录失败返回-1
		}
	}
}


int CJsonUtil::parseMsgJson(const char* str)
{
	//从字符串中读取数据  
	if (reader.parse(str, root))
	{
		string Msg = root["msg"].asString();
		int code = root["code"].asInt();
		if (Msg == "ok")//如果Msg为ok，成功
		{
			return 0;//成功返回0
		}
		else
		{
			cout << "msg:" << Msg << endl;
			return -1;//如果Msg不为ok，失败
		}
	}
}

int CJsonUtil::parsePairStatus(const char* str, std::string &strServerAuthNum)
{
	//从字符串中读取数据  
	if (reader.parse(str, root))
	{
		
		if (!root["data"]["server_author_number"].isNull())////如果server_author_number不为null，设置用户server_author_number值
		{
			strServerAuthNum = root["data"]["server_author_number"].asString();
			return 0;//成功返回0
		}
		else
		{
			cout << "strServerAuthNum:NULL" << endl;
			return -1;//失败返回-1
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

//	解析 开始病例，传入的检查信息
int CJsonUtil::parseOnStartCaseCheckInfo(neb::CJsonObject &oJson, tagCaseCreateInfo& _objCheckInfo)
{
	neb::CJsonObject oJsonData = oJson;
	if (oJsonData.IsEmpty())
		return -1;
	
	if (oJsonData.KeyExist("check_type"))
		_objCheckInfo.nCaseType = std::stoi(oJsonData["check_type"].ToString()); // 检查类型id， 可以区分检查类型

	if (oJsonData.KeyExist("check_id"))
	{
		_objCheckInfo.nCaseCheckId = std::stoi(oJsonData["check_id"].ToString()); // 检查id， 可以区分检查级别

	}

	return 0;
}
