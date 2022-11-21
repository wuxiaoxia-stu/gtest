#pragma once

/*
******		FileName	:	AyjPaicsSdkCase.h
******		Describe	:	此文件是c++ 接口, 主要用于病例管理 包括  病例创建 与 病例获取
******		Date		:	2021-06-27 
******		Author		:	TangJinFei
******		Copyright	:	Guangzhou AiYunJi Inc.
******		Note1		:	1、依赖库..., 2、所有字符编码采用u8格式 3、仅支持64位 
******		Note2		:	接口命名规则: 后缀有Cb的, 都为异步 , 否则为同步
*/


#include "AyjPaicsSdkDefine.h"
#include "detector_struct.h"


namespace AYJ
{
	/////////////////		ABC 检查 数据 		//////////////////

	//	获取检查配置信息 _nCheckId  = 1  , 实时分析的检查配置， 2 ， 质控的检查配置
	AYJ_PAICS_LIB_API int CheckInfoGet(int _nCheckId , tagCallBackPara& _objCbPara);
	//	保存检查配置信息
	AYJ_PAICS_LIB_API int CheckInfoSave(const char* _szDataJson, tagCallBackPara& _objCbPara);
	//	通过检查id 获取已选择的切面列表
	AYJ_PAICS_LIB_API int CheckListGetById(int _nCheckId, tagCallBackPara& _objCbPara);

	/////////////////		病例创建		//////////////////

	//	创建病例
	AYJ_PAICS_LIB_API int CaseCreate(const tagCaseCreateInfo& _tagCreateInfo, tagCallBackPara& _objCbPara);

	//	病例信息更新
	AYJ_PAICS_LIB_API int CaseInfoUpdate(const tagCaseUpdateInfo& _tagCaseInfo, tagCallBackPara& _objCbPara);

	//	病例结束
	AYJ_PAICS_LIB_API int CaseFinish(const tagCaseFinishInfo& _tagCaseInfo, tagCallBackPara& _objCbPara);

	/////////////////		历史病例		//////////////////

	//	获取时间线
	AYJ_PAICS_LIB_API int CaseTimelineGet(const tagCaseSearchInfo& _tagSearchInfo, tagCallBackPara& _objCbPara);
	//	获取病例列表
	AYJ_PAICS_LIB_API int CaseListGet(const char* _szDataJsonArry, tagCallBackPara& _objCbPara);
	//	获取病例详情
	AYJ_PAICS_LIB_API int CaseDetailGet(int _nCaseId, tagCallBackPara& _objCbPara);
	//	获取当前设备当前病例 （续接页面展示）
	AYJ_PAICS_LIB_API int CaseListTodayGet(tagCallBackPara& _objCbPara);
	//	删除病例 ， 错误病例需要删除， 请谨慎调用 (只有新病例失败才调用， 续接不需要)
	AYJ_PAICS_LIB_API int CaseDelete(int _nCaseId, tagCallBackPara& _objCbPara);

	/////////////////		病例标签		//////////////////
	
	//	创建自定义标签
	AYJ_PAICS_LIB_API int CustomLabelCreate(const char* _szLabelName, tagCallBackPara& _objCbPara);
	//	删除自定义标签
	AYJ_PAICS_LIB_API int CustomLabelDelete(const char* _szLabelId, tagCallBackPara& _objCbPara);

	//	病例关联标签
	AYJ_PAICS_LIB_API int CaseRelateLabel(int _nCaseId, const char* _szLabelId, tagCallBackPara& _objCbPara);
	//	移除病例标签
	AYJ_PAICS_LIB_API int CaseRemoveLabel(int _nCaseId, const char* _szLabelId, tagCallBackPara& _objCbPara);



}
