#pragma once

/*
******		FileName	:	AiYunjiSdk.h
******		Describe	:	此文件是c++ 接口
******		Date		:	2021-01-25
******		Author		:	TangJinFei
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note		:	1、依赖库..., 2、所有字符编码采用u8格式 3、仅支持64位
*/


#ifdef ABCS//_DEBUG
#define LOAD_AI_MODULE
#endif


#ifdef LPMPAICSSDK_EXPORTS
#define AYJ_PAICS_LIB_API  __declspec(dllexport)
#else
#define AYJ_PAICS_LIB_API  __declspec(dllimport)
#endif

#include <string>

#include "detector_struct.h"

class ICallBackInterface;
//	通用回调数据
typedef struct tagCallBackPara
{
	std::string	strData = "";		//	返回数据
	std::string	strDataEx = "";		//	扩展数据

	int		nReturn = -1;			//	请求返回值
	void*	pUserData = nullptr;	//	用户数据
	int		nActionId = -1;			//	动作ID

	ICallBackInterface*	pCallBackFun = nullptr;	//	赋值就是异步， 为空就是同步

	void SetData(const std::string _strData)
	{
		strData = _strData;
	}

	void SetDataEx(const std::string _strDataEx)
	{
		strDataEx = _strDataEx;
	}

	tagCallBackPara()
	{
		nReturn = -1;
		strData = "{\"code\":-1, \"msg\":u8\"对象未初始化\"}";
		strData.clear();
		strDataEx.clear();
	}

	tagCallBackPara(const std::string _strData, const std::string _strDataEx, ICallBackInterface* _pCallBackFun, void*	_pUserData, int _nActionId, int _nReturn)
	{
		strData = _strData;
		strDataEx = _strDataEx;
		nActionId = _nActionId;
		nReturn = _nReturn;

		pUserData = _pUserData;
		pCallBackFun = _pCallBackFun;
	}
	tagCallBackPara& operator=(const tagCallBackPara& _tagObj)
	{
		if (this != &_tagObj)
		{
			strData = _tagObj.strData;
			strDataEx = _tagObj.strDataEx;

			nActionId = _tagObj.nActionId;
			nReturn = _tagObj.nReturn;

			pUserData = _tagObj.pUserData;
			pCallBackFun = _tagObj.pCallBackFun;
		}

		return *this;
	}
	~tagCallBackPara()
	{
		strData.clear();
		strDataEx.clear();

		nActionId = 0;
		nReturn = 0;

		pUserData = nullptr;
		pCallBackFun = nullptr;
	}

}tagCallBackPara;

//	同步接口返回结果
typedef struct tagRetInfo
{
	int nReturn = 0;		//	0 返回成功， 非0 失败
	std::string strRetMsg;	//	失败原因

	tagRetInfo()
	{
		nReturn = 0;
		strRetMsg = u8"成功";
	}
	tagRetInfo(const int _nRet)
	{
		nReturn = _nRet;
		if(_nRet != 0)
			strRetMsg = u8"管理对象未初始化";
	}
	tagRetInfo(const int _nRet,const std::string _strMsg)
	{
		nReturn = _nRet;
		strRetMsg = _strMsg;
	}

}tagRetInfo;

//	设备激活数据
typedef struct tagDevActivateInfo
{
	std::string strDevId;			//	设备序列号
	std::string strAuthNum;			//	授权ID

	std::string strMachineBrand;	//	超声机品牌
	std::string strMachineInfo;		//	超声机简称
	std::string strFloor;			//	楼层
	std::string strRoom;			//	房号
}tagDevActivateInfo;

//	视频输出数据
typedef struct tagVdieoFrame
{
	long long		llSeq = 0;	//	视频序号, 以开始采集为第一帧序号
	long long		llPts = 0;	//	视频显示时间戳
	unsigned int	unWidth = 0;	//	视频宽度
	unsigned int	unHeight = 0;	//	视频长度
	int				nFrameFormat = -1;	//	图像格式 2== RGB24  3==BGR24

	unsigned char*	pDataBGR24 = nullptr;	//	视频数据，BGR24  格式 == 3 , 给客户端后，会转成RGB24  == 2
	unsigned int	unDataSize = 0;			//	视频数据大小	

	int				nAiTime = 0;	//	AI 耗时 毫秒

	tagVdieoFrame()
	{
	}

	tagVdieoFrame(int _nFrameFormat, int _nW, int _nH)
	{
		pDataBGR24 = new unsigned char[_nW*_nH * 3];
		memset(pDataBGR24, 0, _nW*_nH * 3);
		unWidth = _nW;
		unHeight = _nH;
		unDataSize = _nW * _nH * 3;
		nFrameFormat = _nFrameFormat;
	}

	tagVdieoFrame& operator=(const tagVdieoFrame& other)
	{
		if (this == &other)
			return *this;

		if (unDataSize != other.unDataSize)
		{
			delete[] pDataBGR24;
			pDataBGR24 = new uint8_t[other.unDataSize];
		}

		memcpy(pDataBGR24, other.pDataBGR24, other.unDataSize);

		llSeq = other.llSeq;
		llPts = other.llPts;
		unWidth = other.unWidth;
		unHeight = other.unHeight;
		nFrameFormat = other.nFrameFormat;
		unDataSize = other.unDataSize;
		nAiTime = other.nAiTime;

		return *this;
	}
	
	~tagVdieoFrame()
	{
		if (pDataBGR24)
		{
			delete[]pDataBGR24;
			pDataBGR24 = nullptr;
			unDataSize = 0;
		}
	}

}tagVdieoFrame;

//	采集卡状态
typedef enum emCaptureState
{
	State_Capture_Error = -1,		//	采集错误

	State_Capture_SigAbnormal = 3,	// 无信号 (采集设备掉线 -- 检查线路是否出错)
	State_Capture_Signormal = 4,	// 信号正常 (采集设备重新插入了)
}emCaptureState;

//	病例视频播放状态
typedef enum emCaseVideoStatus
{
	eNull = -1,
	ePlaying = 0,		//	已经播放
	eStopped = 1,		//	停止
	ePaused = 2,		//	暂停
	eEndReached = 3,	//	播放已到文件尾部
	ePlaybackEnd = 4,	//	区间播放结束, 此消息触发， 播放状态为停止
}emCaseVideoStatus;

//	采集参数数据
typedef struct tagCaptureInitPara
{
			//	采集设备 id ,  采集卡id 默认为0   <0 采集桌面 -1 gdi    -2 gxgi(性能较好)
	int nCaptureW = 1920;	//	采集的视频宽度
	int nCaputreH = 1080;	//	采集的视频高度
	int nCaputerFps = 25;	//	采集的帧率

}tagCaptureInitPara;

//	采集卡裁剪的参数
typedef struct tagCaptureCropPara
{
	int nPoxX = 0;		//	裁剪的坐标 X
	int nPoxY = 0;		//	裁剪的坐标 Y
	int nWidth = 0;		//	裁剪的宽度 W
	int nHeight = 0;	//	裁剪的高度 H

	double dbOriginalScale = 1.77777;	//	目前常用的裁剪的比例 16:9 == 1.77777  4 : 3 == 1.33333  5:4 == 1.25

}tagCaptureCropPara;

//	ai 算法打开参数
typedef struct tagAiOpenPara
{
	bool		bIsSplicing = false;	//	是否是续接病例， 默认是新病例
	
	enGestation emWeek;					//	孕周 ; enEarly = 0 早孕, enMidLater = 2,	中晚孕
	std::string strCaseFilePath;		//	病例保存路径,	如 "D://case//1234"
	std::string strCaseFileName;		//	病例保存名称,	如 "123456"
	enQcLevel	emQclevel;				//	检查级别	1,2,3级  100 == 国家级

	tagAiOpenPara()
	{
		bIsSplicing = false;
		emWeek = enEarly;
		strCaseFilePath = "";
		strCaseFileName = "";
		emQclevel = enLevelNational;
	}
	void Clear()
	{
		tagAiOpenPara();
	}

}tagAiOpenPara;

//	病例信息结构体
typedef struct tagCaseCreateInfo
{
	//	基本信息
	std::string	strDevId;				//	设备序列号 必填
	
	int			nCaseType = 1;			//	病例类型，1  实时分析病例 2 单人质控  3、多人质控 必填
	int			nCaseCheckId = 0;		//	检查id， 设置切面的id	必填
	int			nCaseCheckType = 0;		//	病例检查类型， 0 早 1中 2 晚, 必填

}tagCaseCreateInfo;

//	病例信息更新
typedef struct tagCaseUpdateInfo
{
	int			nCaseId = -1;			//	病例id 8位, 本地服务器创建返回， 必填

	//	病例基本信息
	std::string	strCasePath;		//	病例相对路径 病例保存路径 E:/case/devId/年/月/日/caseId/
	std::string	strCasePathCloud;	//	病例云端保存路径	E:/case/devId/年/月/日/caseId/

	std::string strMulitFetusGroupId;	//	多胎分组id
	std::string strFetusName;			//	胎儿名称
	int			nJoinFlag = -1;			//	续接标志 1续接 0 不续接
		
	//	患者信息	工作站对接传入
	std::string	strPatientId;			//	患者ID
	std::string strPatientName;			//	患者名称	有患者名称就带上， 没有就不带
	int			nPatientWeek = -1;		//	患者孕周

}tagCaseUpdateInfo;


//	病例结束
typedef struct tagCaseFinishInfo
{
	int			nCaseId;			//	病例id 8位, 本地服务器创建返回， 必填

	//	病例结束信息
	int			nCaseResultStatus = 1;		//	病例切面状态 1 正常 2 疑似 3 未检 4 异常
	int			nTotalScore = -1;			//	当前病例总分（质控病例考核分数）
	int			nCaseLength = -1;			//	病例长度 毫秒

}tagCaseFinishInfo;

//	病例检索
typedef struct tagCaseSearchInfo
{
	std::string strSearchKey  = "";		//	搜索关键字 模糊搜索, 只搜索标签(AI标签与自定义标签)

	int			nJoinFlag = -1;			//	续接标志
	std::string	strCaseType = "";		//	病例类型，1  实时分析病例 2 单人质控  3、多人质控 必填 ("0,1,2")
	std::string	strCaseCheckType = "";	//	病例检查类型， 0 早 1中 2 晚, 必填 ("0,1")

	int			nCaseLengthMin = -1;	//	病例最短时间
	int			nCaseLengthMax = -1;	//	病例最长时间

	int			nAuaWeekBegin = -1;		//	ai测量  起始孕周
	int			nAuaWeekEnd = -1;		//	ai测量  起始孕周

	int			nLmpWeekBegin = -1;		//	手动输入  起始孕周 	
	int			nLmpWeekEnd = -1;		//	手动输入  结束孕周

	std::string	strTimeBegin;			//	搜索开始时间 成对出现
	std::string	strTimeEnd;				//	搜索结束时间

	std::string strCheckLevel;			//	检查级别 1,2,3 100(国家级)  ("1,2")
	std::string strFetusNum;			//	单胎多胎 "1,2,3";

	std::string strDoctorName;			//	医生名称 如("张三，李四，王五"), 精确搜索
	std::string strPatientName;			//	患者名称 如("张三，李四，王五"), 精确搜索

}tagCaseSearchInfo;

//	视频远程角色类型
typedef enum emRemoteRoleType
{
	eRemoteRolePaics = 1,		//	PIACS 客户端
	eRemoteRoleProfessor = 2	//	远程会诊 专家端
}emRemoteRoleType;

//	远程控制命令
typedef enum emRemoteCmdType
{
	ePaicsCmd_OnlineNotice = 10001,			//	Pcics 客户端 在线 或者 下线通知 通知
	ePaicsCmd_Assist_Apply = 10002,			//	Pcics 客户端 远程会诊协助申请		
	ePaicsCmd_Assist_End = 10003,			//	Pcics 客户端 远程会诊协助结束	
	ePaicsCmd_ChatMsg = 10004,				//	Pcics 客户端 远程会诊时 聊天信息	


	eProfessorCmd_OnlineNotice = 20001,		//	专家端 客户端  在线 通知
	eProfessorCmd_Accept_Assist = 20002,	//	专家端 客户端 远程会诊时 接收协助	
	eProfessorCmd_Refuse_Assist = 20003,	//	专家端 客户端 远程会诊时 拒绝协助	
	eProfessorCmd_ChatMsg = 20004,			//	专家端 客户端 远程会诊时 聊天信息	专家端 发起
	eProfessorCmd_SuggestMsg = 20005,		//	专家端 客户端 远程会诊时 聊天信息	专家端 发起

	/////////////////			监视		///////////////
	eProfessorCmd_Monitor_Start = 20006,	//	专家端 客户端 监控 PAICS 客户端	
	eProfessorCmd_Monitor_End = 20007,		//	专家端 客户端 监控 PAICS 结束		
	eProfessorCmd_Monitor_Switching = 20008,//	专家端 客户端 监控 PAICS 画面切换	(超声机画面, 或者客户端屏幕画面)
	Cmd_Realtime_Video_Data = 20009,		//	实时视频数据		
	Cmd_Realtime_Audio_Data = 20010,		//	实时音频数据
	Cmd_Realtime_Ai_Data = 20011,			//	实时AI数据

}emRemoteCmdType;

//	流信息
typedef enum emStreamType
{
	eStreamVideo = 1,	//	视频流
	eStreamAutho = 2	//	音频流
}emStreamType;

//	专家监控类型
typedef enum emProfessorMonitorType
{
	eMonitor_Client_Pic = 1,	//	客户端全画面
	eMonitor_Ultrasonic_Pic = 2	//	超声机画面 (其实就是采集卡的画面)
}emProfessorMonitorType;

//	通用 数据 回调 接口
class AYJ_PAICS_LIB_API ICallBackInterface
{
public:

	virtual ~ICallBackInterface() {}
	virtual int OnCallbackFun(const tagCallBackPara& _objCbData) = 0;
};




