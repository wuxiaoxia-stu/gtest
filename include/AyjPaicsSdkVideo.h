#pragma once

/*
******		FileName	:	AyjPaicsSdkVideo.h
******		Describe	:	此文件是c++ 接口, 主要用于视频方面， 包括  视频采集 与 视频存储及 视频读取
******		Date		:	2021-06-06 (重构时间)
******		Author		:	TangJinFei
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note1		:	1、依赖库..., 2、所有字符编码采用u8格式 3、仅支持64位 
******		Note2		:	接口命名规则: 后缀有Cb的, 都为异步 , 否则为同步
*/


#include "AyjPaicsSdkDefine.h"
#include "detector_struct.h"


namespace AYJ
{
	/////////////////		视频采集		//////////////////

	//	采集实时 视频 数据回调
	typedef int(__stdcall *OnCaptureFrameCb)(unsigned int _nCapId, tagVdieoFrame* _objFrameInfo, detection_result* _objDectData, void* _pUserData);
	//	采集视频 状态 数据回调
	typedef int(__stdcall *OnCaptureStatusCb)(unsigned int _nCapId, emCaptureState _emStatus, void* _pUserData);

	/**
		* @brief	设置采集回调函数
		* @param[in] _nCapId	采集卡id 默认为0 < 0 采集桌面 - 1 gdi - 2 gxgi(性能较好)
		* @param[in] _pFrameCb	采集帧回调函数
		* @param[in] _pStatusCb	采集状态回调函数
		* @param[in] _lShowWnd	渲染显示窗口句柄(测试使用)
		* @return 0 成功，非0 失败
	**/
	AYJ_PAICS_LIB_API tagRetInfo CaptureSetCallback(int _nCapId, OnCaptureFrameCb _pFrameCb, OnCaptureStatusCb _pStatusCb, void* _pUserData, long _lShowWnd = 0);

	/**
	@brief	初始化采集卡
	* @param[in] _nCapId	采集卡id 默认为0 < 0 采集桌面 - 1 gdi - 2 gxgi(性能较好)
	* @param[in] _tagCapPara 采集参数， 用默认的
	* @return 0 成功，非0 失败
	*/
	AYJ_PAICS_LIB_API tagRetInfo CaptureInit(int _nCapId, const tagCaptureInitPara _tagCapPara);

	//	采集卡释放
	AYJ_PAICS_LIB_API tagRetInfo CaptureRelease(int _nCapId);

	//	采集开始
	AYJ_PAICS_LIB_API tagRetInfo CaptureStart(int _nCapId);
	//	采集停止
	AYJ_PAICS_LIB_API tagRetInfo CaptureStop(int _nCapId);

	//	设置采集卡裁剪的参数
	AYJ_PAICS_LIB_API tagRetInfo CaptureSetCropPara(int _nCapId, const tagCaptureCropPara& _tagPara);



	/////////////////		病例视频管理		//////////////////

	//	病例视频 播放 数据回调
	typedef int(__stdcall *OnCaseVideoFrameCb)(void* _pCaseVideoObj, tagVdieoFrame* _objFrameInfo, detection_result* _objDectData, void* _pUserData);
	//	病例视频 播放 状态回调		
	typedef int(__stdcall *OnCaseVideoStatusCb)(void* _pCaseVideoObj, emCaseVideoStatus _emStatus, void* _pUserData);

	//	获取 病例视频 长度，可单独使用
	AYJ_PAICS_LIB_API long long GetCaseVideoLength(const char* _szCaseFilePath, const char* _szCaseFileName);

	//	创建 病例视频 对象
	AYJ_PAICS_LIB_API void* CreateCaseVideoObj();
	//	释放 病例视频 对象
	AYJ_PAICS_LIB_API tagRetInfo ReleaseCaseVideoObj(void* _pCaseVideoObj);

	//	 _pCbFrame	帧回调, _pCbStatus	 播放状态回调, _pUserData	 用户数据
	AYJ_PAICS_LIB_API tagRetInfo CaseVideoSetPara(void* _pCaseVideoObj, OnCaseVideoFrameCb _pCbFrame, OnCaseVideoStatusCb _pCbStatus, void* _pUserData);

	//	病例视频 初始化， 成功放回视频总时长  毫秒, 失败小于 0 
	AYJ_PAICS_LIB_API tagRetInfo CaseVideoInit(void* _pCaseVideoObj, const char* _szCaseFilePath, const char* _szCaseFileName, bool _bIsLaodAiInfo, long long& _llCaseVideoLengthOut,  long _lPlayHandle = 0);
	//	病例视频 释放
	AYJ_PAICS_LIB_API tagRetInfo CaseVideoRelease(void* _pCaseVideoObj);

	//	病例视频 播放
	AYJ_PAICS_LIB_API tagRetInfo CaseVideoPlay(void* _pCaseVideoObj, long long _llPlayStart = 0, long long _llPlayEnd = 0, long long _llThisTimePlay = 0);
	//	病例视频 暂停
	AYJ_PAICS_LIB_API tagRetInfo CaseVideoPuase(void* _pCaseVideoObj);

	//	病例视频 seek, 输入为毫秒 seek 后之前是暂停的继续暂停， 是播放的继续播放, 播放状态不变
	AYJ_PAICS_LIB_API tagRetInfo CaseVideoSeek(void* _pCaseVideoObj, long long _llSeekTime);

	// 病例播放速度
	// _nPlayType	播放类型1 ,正常速度播放， 2， 0.5 倍, 3. 0.25倍数, 4, 正常速度顺序播放。 直接播放到尾部,取消区间
	AYJ_PAICS_LIB_API tagRetInfo CaseVideoSpeedSet(void* _pCaseVideoObj, int _nPlayType);

	


}
