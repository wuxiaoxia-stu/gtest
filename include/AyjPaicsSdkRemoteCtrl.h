#pragma once

/*
******		FileName	:	AyjPaicsSdkRemoteCtrl.h
******		Describe	:	此文件是c++ 接口，主要用于 专家端远程控制 , 远程实时视频 ,涉及业务为  客户端监视 、远程会诊
******		Date		:	2021-06-17 
******		Author		:	TangJinFei
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note1		:	1、依赖库..., 2、所有字符编码采用u8格式 3、仅支持64位 
******		Note2		:	主要是实时视频的监控
*/



#include "AyjPaicsSdkDefine.h"

#include <string>


namespace AYJ
{
	/////////////////		AI 管理		//////////////////

	//	命令回调
	typedef int(__stdcall *OnRemoteCmdCb)(emRemoteCmdType _nCmdType, char* _szCmdData, int _nDataSize, void* _pUserData);
	//	视频信息回调
	typedef int(__stdcall *OnRemoteStreamCb)(emStreamType _eStreamType, char* _szStreamData, int _nDataSize,  void* _pUserData);

	//	远程控制初始化
	AYJ_PAICS_LIB_API int RemoteCtrlInit(const emRemoteRoleType _eRoleType, const char* _szDevId, OnRemoteCmdCb _pCmdCb, OnRemoteStreamCb _pStreamCb, void* _pUserData, long _lPlayHandle = 0);
	//	远程控制释放
	AYJ_PAICS_LIB_API int RemoteCtrlRelease();

	/////////////////////	PCIAS 端	//////////////////////

	//	PAICS 请求远程协助
	AYJ_PAICS_LIB_API int RemoteCtrlApplyAssist(const char* _szRemoteDevId);
	//	PAICS 结束远程协助
	AYJ_PAICS_LIB_API int RemoteCtrlEndAssist(const char* _szRemoteDevId);

	/////////////////////	PCIAS 端 或 专家端共用	//////////////////////////

	//	PAICS 端 或 专家端 打开语音聊天
	AYJ_PAICS_LIB_API int RemoteCtrlOpenAudio();
	//	PAICS 端 或 专家端 关闭语音聊天
	AYJ_PAICS_LIB_API int RemoteCtrlCloseAudio();

	//	PAICS 端 或 专家端  发送会诊时的聊天信息
	AYJ_PAICS_LIB_API int RemoteCtrlSendChatMsg(const char* _szDataU8, int _nDataSize);

	/////////////////////	专家端	//////////////////////////

	//	专家 接收会诊协助  _szDevId 设备序列号 
	AYJ_PAICS_LIB_API int RemoteCtrlAcceptAssist(const char* _szRemoteDevId);
	//	专家 拒绝会诊协助
	AYJ_PAICS_LIB_API int RemoteCtrlRefuseAssist(const char* _szRemoteDevId);
	
	//	专家 发送会诊 建议
	AYJ_PAICS_LIB_API int RemoteCtrlSendSuggestMsg(const char* _szDataU8, int _nDataSize);

	//	专家 发起监控, 默认是 画面是 paics 全部客户端 画面
	AYJ_PAICS_LIB_API int RemoteCtrlMonitorStart(const char* _szRemoteDevId);
	//	专家 结束监控
	AYJ_PAICS_LIB_API int RemoteCtrlMonitorEnd(const char* _szRemoteDevId);
	//	专家 切换监控画面 , 1 是客户端画面， 2 是超声机画面
	AYJ_PAICS_LIB_API int RemoteCtrlMonitorSwitching(const char* _szRemoteDevId, const emProfessorMonitorType _eMonitorType);

}
