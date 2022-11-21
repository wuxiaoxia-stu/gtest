#pragma once
/*
******		FileName	:	Define.h
******		Describe	:	���ļ����ڹ���ȫ�ֱ���
******		Date		:	2022-08-11
******		Author		:	Xiaoxia
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note		:   ����
*/



#ifndef CAYJLOGINMANAGER_H
#define CAYJLOGINMANAGER_H

#include <string>
#include "CJsonObject.hpp"

//�����ļ� ϵͳ����
struct stuConfigData {

	const char*	cloud_ip = "192.168.1.189";		//	�ƶ˷�����IP
	int			cloud_port = 9005;				//	�ƶ˷������˿�
	const char* local_ip = "127.0.0.1";			//	���ط����� IP
	int			local_port = 9006;				//	���ط������˿�
	//	֤�� ΨһID
	const char* licence = "";
	const char* author_number = "C_22060015";	//	�ͻ�����Ȩ��
	const char* szDevId = "22062217402617101";	//�豸���

	std::string	strProductName = "PUS S300";	//	��Ʒ����
	std::string	strProductVer = "V_1.0.1.0713"; //	��Ʒ�����汾
	std::string	strProductVerEx = "V_1.0";		//	��Ʒ���װ汾

	const char* user_token = "";
	std::string strServerAuthNum;	//	�������Ȩ��
};

//��������
struct stuCheckInfo {

	neb::CJsonObject oJsonData;//ʵ����CJsonObject,ʵʱ����/�ʿؿ��˵ļ��������Ϣ
	//	������Ϣ
	std::string	strDevId;				//	�豸���к� ����

	int			nCaseType = 1;			//	�������ͣ�1  ʵʱ�������� 2 �����ʿ�  3�������ʿ� ����
	std::string	strCaseCheckId = "80c9b545-7ea7-4f42-9f2b-df330485e594";		//	���id�� ���������id	����
	int			nCaseCheckType = 0;		//	����������ͣ� 0 �� 1�� 2 ��, ����

};


#endif // CAYJLOGINMANAGER_H