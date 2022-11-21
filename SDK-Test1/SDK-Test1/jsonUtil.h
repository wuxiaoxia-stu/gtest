#pragma once

#ifndef CJSONUTIL_H
#define CJSONUTIL_H

#include "pch.h"
#include "CJsonObject.hpp"

//JSON���ݴ�����
class CJsonUtil
{
public:
	CJsonUtil();
	~CJsonUtil();

public:
	//�����û���¼���ص�json���ݣ������û�token����¼�ɹ�����0��ʧ�ܷ���-1
	static int parseUserTokenJson(const char* str);

	//�������ص�json���ݣ��ɹ�����0��ʧ�ܷ���code
	static int parseCodeJson(const char* str);

	//�������ص�json�����е���ʾ��Ϣ���ɹ�����0��ʧ�ܷ���code
	static int parseMsgJson(const char* str);

	//�������״̬���ݣ��޸ķ�����Ȩ�룬�ɹ�����0
	static int CJsonUtil::parsePairStatus(const char* str, std::string &strServerAuthNum);

	//����ʵʱ����/�ʿؿ��˵�������Ϣ���ɹ�����0
	static int CJsonUtil::parseCheckInfo(const char* str, neb::CJsonObject &oJson);

	//	���� ��ʼ����������ļ����Ϣ
	static int CJsonUtil::parseOnStartCaseCheckInfo(neb::CJsonObject &oJson, tagCaseCreateInfo& _objCheckInfo);
};

#endif // !CJSONUTIL_H
