#ifndef _DETECTOR_DEFINE_H_
#define _DETECTOR_DEFINE_H_

#pragma once
#define DETECTOR_API __declspec(dllexport)

#include <vector>
#include <string>
#include <map>

#pragma warning(push)
#pragma warning(disable:4251)

//检测画面所在位置
enum   enPositionStatus
{
	enNone = -1,					  /* 空值 */
	enLeft = 1,						  /* 左 */
	enRight = 2,					  /* 右 */
	enMiddle = 3,					  /* 居中 */
};

//画面播放状态
enum   enFrameStatus
{
	enUndetected = -1,				  /* 未检测 */
	enWaiting = 0,					  /* 等待开始检测 */
	enPlaying = 1,					  /* 播放状态 */
	enStop = 2,						  /* 暂停状态 */
};

//孕周类型
enum   enGestation
{
	enEmpty = -1,					   /* 空值 */
	enEarly = 0,					   /* 早孕周 */
	enMidLater = 2,					   /* 中晚孕周 */
};

//切面疑似的原因
enum   enCauseOfSuspect
{
	enNoSuspect = -1,				   /* 空值 */
	enCause1 = 1,					   /* 含有疑似异常结构 */
	enCause2 = 2,					   /* 缺少正常结构 */
	enCause3 = 3,					   /* 图像质量问题 */
};		

//估测体重方式 - 20211025
enum enWeightEstimationMethod
{
	enHadlock = 1,					   /* Hadlock公式(AC/HC/FL) */
	enIntergrowth21 = 2,			   /* INTERGROWTH-21ST */
};

//QC等级 - 20211104
enum enQcLevel
{
	enLevel1 = 1,					   /* Ⅰ级 */
	enLevel2 = 2,					   /* Ⅱ级 */
	enLevel3 = 3,					   /* Ⅲ级 */
	enLevelNational = 100,			   /* 国家级 */
};

//测量-椭圆坐标
struct   measure_ellipse
{
	int center_x = 0;				   /* 中心点x */
	int center_y = 0;				   /* 中心点y */
	double r_l = 0;					   /* 长半轴 */
	double r_s = 0;					   /* 短半轴 */
	double angle = 0;				   /* 旋转角 */
};

//测量-直线坐标
struct   measure_line
{
	int point0_x = 0;				   /* A点x坐标 */
	int point0_y = 0;				   /* A点y坐标 */
	int point1_x = 0;				   /* B点x坐标 */
	int point1_y = 0;				   /* B点y坐标 */
	bool visible = false;			   /* 直线是否需要显示 */
};

//方框坐标
struct   bin_rect
{
	int x = 0;						   /* 起点x坐标 */
	int y = 0;						   /* 起点y坐标 */
	int width = 0;					   /* 宽 */
	int height = 0;					   /* 高 */
	bin_rect() {}
	bin_rect(int i_x, int i_y, int i_width, int i_height)
	{
		x = i_x;
		y = i_y;
		width = i_width;
		height = i_height;
	}
};

//特征名称
struct   feature_label
{
	std::string en;					   /* 英文名 */
	std::string ch;					   /* 中文名 */
};

//测量特征坐标
union   measure_shape
{
	measure_ellipse ellipse;		   /* 椭圆坐标 */
	measure_line line;				   /* 直线坐标 */
	measure_shape() { new (&ellipse) measure_ellipse; }
};

//测量特征
struct   measure_feature
{
	int id = -1;					   /* 0 测量ID */
	double prob = 0;				   /* 0 测量结果置信度 */
	int type = 0;					   /* 1 特征类别：1 - line, 2 - ellipse */
	double value = 0;				   /* 1 测量值 */
	int best_seq = -1;				   /* 1 最优帧序号 */
	int best_pts = -1;				   /* 1 最优帧时间戳 */
	double best_value = 0;			   /* 1 最优测量值 */
	std::string label;				   /* 1 名称 BDP HL 无中文*/
	bin_rect bin;					   /* 0 矩形框，起点为负时代表空值 */
	measure_shape shape;			   /* 1 形状坐标 */
};

//测量结果
struct   measure_result
{
	int image_id = -1;							    /* 形状坐标 */
	double scale = -1;							    /* 形状坐标 */
	std::vector<measure_feature> measure_vector;    /* 形状坐标 */
};

//QC得分
struct   qc_score
{
	int num_in_sp = -1;				/* 1 在切面内的序号 */
	double value = 0;				/* 1 得分 */
	double limit = 0;				/* 0 得分上下限 */
};

//切面QC
struct sp_qc
{
	int hash_id = -1;				/* 宏ID */
	int index = -1;					/* 位置id */
	int priority = 0;				/* 优先级 */
	double pl_score = 0;			/* 切面QC总分 */
	std::map<int, qc_score> qc;		/* qc评分项 */
};

//QC分组位置
struct stuExamGroupEx
{
	bool needExam = true;			/* 需要考核 */
	int hash_id = -1;				/* 切面id */
	int index = 0;					/* 位置索引 ,切面坑的位置， 如果不是分组 就是 1， 是分组就是1开始， 分组的切面id 都是一样的*/
};

//QC分组
struct stuExamQuestionEx
{
	std::vector<stuExamGroupEx> vecGroup;	/* 组内切面 */
};

//QC信息
struct   qc_info
{
	std::string label_en;			/* 英文标签 */
	std::string label_ch;			/* 中文标签 */
	double limit = 0;				/* 得分上下限 */
	int belong_to_sp = -1;			/* 所属切面 - 20210824 */
	int num_in_sp = -1;				/* 在切面内的序号 */
	std::vector<int> sp_qc_list;	/* 切面的QC列表 */
	qc_info() {}
	qc_info(std::string s_label_en, std::string s_label_ch, double d_limit,
		int i_belong_to_sp, int i_num_in_sp, std::vector<int> v_sp_qc_list = {})
	{
		label_en = s_label_en;
		label_ch = s_label_ch;
		limit = d_limit;
		belong_to_sp = i_belong_to_sp;
		num_in_sp = i_num_in_sp;
		sp_qc_list = v_sp_qc_list;
	}
};

struct   bbox_t
{
	int x = 0;				   /* 1 坐标x  20210814 modify unsigned int to int */
	int y = 0;				   /* 1 坐标y 20210814 modify unsigned int to int */
	int w = 0;				   /* 1 坐标w 20210814 modify unsigned int to int */
	int h = 0;				   /* 1 坐标h 20210814 modify unsigned int to int */
	float prob = 0;			   /* 1 置信度 */
	int obj_id = -1;		   /* 0 ID 20210814 modify unsigned int to int */
	int track_id = 0;		   /* 0 未使用 20210814 modify unsigned int to int */
	int frames_counter = 0;    /* 0 未使用 20210814 modify unsigned int to int  */
	float x_3d = 0;			   /* 0 未使用 */
	float y_3d = 0;			   /* 0 未使用 */
	float z_3d = 0;			   /* 0 未使用 */
};

//检测特征
struct   bbox_s :bbox_t
{
	//特征状态
	enum ResultStatus 
	{
		None = 0,					   /* 空 */
		Normal = 1,					   /* 正常 */
		Suspect = 2,				   /* 疑似异常 */
		Abnormal = 3,				   /* 异常 */
		Substandard = 4,			   /* 疑似非标准(切面) */
	}state = None;					   /* 1 切面/特征状态*/
	int hash_id = -1;				   /* 1 宏ID */
	//bool is_plane = false;			   /* 1 切面标识 */
	bool is_measured = false;		   /* 1 已测量标识 */
	bool is_visible = false;		   /* 1 已检标识 */
	bool is_standard = true;		   /* 0 标准特征标识 */
	bool is_color = false;			   /* 0 彩超标识 */
	bool is_message_only = false;	   /* 1 发送信息标识，为true时，仅提取is_visible字段 */
	int best_seq = -1;				   /* 1 最优帧序号 */
	int best_pts = -1;				   /* 1 最优帧时间戳 */
	ResultStatus best_state = None;	   /* 1 最优帧状态 */
	std::vector<measure_feature> measure_vector;	/* 1 测量特征 */
	bbox_s() {}
	bbox_s(bbox_t temp)
	{
		x = temp.x;
		y = temp.y;
		w = temp.w;
		h = temp.h;
		prob = temp.prob;
		obj_id = temp.obj_id;
		track_id = temp.track_id;
		frames_counter = temp.frames_counter;
		x_3d = temp.x_3d;
		y_3d = temp.y_3d;
		z_3d = temp.z_3d;
	}
};

//容器类特征 PP/SP
struct   bbox_bag :bbox_s
{
	bool is_plane = false;							/* 切面标识 */											
	std::vector<bbox_s> member;						/* 容器内成员特征 */
	//std::map<int, qc_score> qc;					/* QC评分项 */
	std::vector<sp_qc> pl_qc;						/* 所有可能的QC评分 */
	enPositionStatus pos = enNone;					/* 当前切面所在位置 */
	enFrameStatus play_status = enUndetected;		/* 播放/暂停 */
	//double pl_score = 0;							/* 切面QC总分 */
	std::vector<enCauseOfSuspect> suspect_cause;	/* 切面疑似的原因 */
	//int pl_group = -1;							/* 非-1时，组号相同的多个切面代表其切面名称需要合并 */
	float weight_prob = 0;							/* 加权置信度 */
	bbox_bag() {}
	bbox_bag(bbox_s temp)
	{
		x = temp.x;
		y = temp.y;
		w = temp.w;
		h = temp.h;
		prob = temp.prob;
		weight_prob = temp.prob;
		obj_id = temp.obj_id;
		track_id = temp.track_id;
		frames_counter = temp.frames_counter;
		x_3d = temp.x_3d;
		y_3d = temp.y_3d;
		z_3d = temp.z_3d;
		state = temp.state;
		hash_id = temp.hash_id;
		//is_plane = temp.is_plane;
		is_measured = temp.is_measured;
		is_visible = temp.is_visible;
		is_standard = temp.is_standard;
		is_message_only = temp.is_message_only;
		best_seq = temp.best_seq;
		best_pts = temp.best_pts;
		best_state = temp.best_state;
		measure_vector = temp.measure_vector;
	}
};

//帧检测结果
struct   detection_result
{
	long long seq = -1;									/* 帧序号 */
	long long pts = -1;									/* 帧时间戳 */
	int screen_num = 1;									/* 画面内屏幕数 */
	//double gestational = -1;							/* 计算得到的具体孕周 */
	enPositionStatus roi_pos = enNone;					/* 当前检测区域位置：左/居中/右 */
	enFrameStatus frame_status_left = enUndetected;		/* 左屏状态/中屏状态 */
	enFrameStatus frame_status_right = enUndetected;	/* 右屏状态 */
	bin_rect roi_rect;									/* ROI裁剪区域 */
	bin_rect meas_roi_rect;								/* 测量ROI裁剪区域 */
	std::vector<bbox_bag> vector_boxbag;				/* 切面 */
};



//拼接数据
struct   splicing_unit
{
	int hash_id = -1;								/* 宏ID */
	double prob = 0;								/* 最优帧置信度 */
	long long seq = -1;								/* 最优帧序号 */
	long long pts = -1;								/* 最优帧时间戳 */
	bbox_s::ResultStatus state = bbox_s::None;		/* 最优帧状态 */
	bool is_visible = false;						/* 已检标识 */
};

//特征属性
struct   feature_details
{
	int mapping_hash_id = -1;		/* 映射特征 */
	int useless = -1;				/* 不生效 */
	int blurry = -1;				/* 模糊 */
	int cut = -1;					/* 裁剪 */
	int color = -1;					/* 彩超 */
	int normal = -1;				/* 正常特征 */
	int abnormal = -1;				/* 异常特征 */
	int pp_pl = -1;					/* PP切面 */
	int sp_pl = -1;					/* SP切面 */
	int early_gestation = -1;		/* 早孕期 */
	int mid_later_gestation = -1;	/* 中晚孕期 */
	int exportable = -1;			/* 可输出特征 */
	feature_details() {}
	feature_details(int argv_0, int argv_1, int argv_2, int argv_3,
		int argv_4, int argv_5, int argv_6, int argv_7,
		int argv_8, int argv_9, int argv_10, int argv_11)
	{
		mapping_hash_id = argv_0;
		useless = argv_1;
		blurry = argv_2;
		cut = argv_3;
		color = argv_4;
		normal = argv_5;
		abnormal = argv_6;
		pp_pl = argv_7;
		sp_pl = argv_8;
		early_gestation = argv_9;
		mid_later_gestation = argv_10;
		exportable = argv_11;
	}
};

struct  detection_resultEx
{
	detection_result objResultInfo;
	std::string strResultUUid = "";		//	Qc质控 图片 uuid
	std::string strResultNameEx = "";	//	Qc质控 图片 名称
	int			nSectionId = -1;		//	Qc质控 检查切面ID
};

#pragma warning(pop)
#endif