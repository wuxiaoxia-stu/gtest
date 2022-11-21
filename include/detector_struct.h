#ifndef _DETECTOR_DEFINE_H_
#define _DETECTOR_DEFINE_H_

#pragma once
#define DETECTOR_API __declspec(dllexport)

#include <vector>
#include <string>
#include <map>

#pragma warning(push)
#pragma warning(disable:4251)

//��⻭������λ��
enum   enPositionStatus
{
	enNone = -1,					  /* ��ֵ */
	enLeft = 1,						  /* �� */
	enRight = 2,					  /* �� */
	enMiddle = 3,					  /* ���� */
};

//���沥��״̬
enum   enFrameStatus
{
	enUndetected = -1,				  /* δ��� */
	enWaiting = 0,					  /* �ȴ���ʼ��� */
	enPlaying = 1,					  /* ����״̬ */
	enStop = 2,						  /* ��ͣ״̬ */
};

//��������
enum   enGestation
{
	enEmpty = -1,					   /* ��ֵ */
	enEarly = 0,					   /* ������ */
	enMidLater = 2,					   /* �������� */
};

//�������Ƶ�ԭ��
enum   enCauseOfSuspect
{
	enNoSuspect = -1,				   /* ��ֵ */
	enCause1 = 1,					   /* ���������쳣�ṹ */
	enCause2 = 2,					   /* ȱ�������ṹ */
	enCause3 = 3,					   /* ͼ���������� */
};		

//�������ط�ʽ - 20211025
enum enWeightEstimationMethod
{
	enHadlock = 1,					   /* Hadlock��ʽ(AC/HC/FL) */
	enIntergrowth21 = 2,			   /* INTERGROWTH-21ST */
};

//QC�ȼ� - 20211104
enum enQcLevel
{
	enLevel1 = 1,					   /* �� */
	enLevel2 = 2,					   /* �� */
	enLevel3 = 3,					   /* �� */
	enLevelNational = 100,			   /* ���Ҽ� */
};

//����-��Բ����
struct   measure_ellipse
{
	int center_x = 0;				   /* ���ĵ�x */
	int center_y = 0;				   /* ���ĵ�y */
	double r_l = 0;					   /* ������ */
	double r_s = 0;					   /* �̰��� */
	double angle = 0;				   /* ��ת�� */
};

//����-ֱ������
struct   measure_line
{
	int point0_x = 0;				   /* A��x���� */
	int point0_y = 0;				   /* A��y���� */
	int point1_x = 0;				   /* B��x���� */
	int point1_y = 0;				   /* B��y���� */
	bool visible = false;			   /* ֱ���Ƿ���Ҫ��ʾ */
};

//��������
struct   bin_rect
{
	int x = 0;						   /* ���x���� */
	int y = 0;						   /* ���y���� */
	int width = 0;					   /* �� */
	int height = 0;					   /* �� */
	bin_rect() {}
	bin_rect(int i_x, int i_y, int i_width, int i_height)
	{
		x = i_x;
		y = i_y;
		width = i_width;
		height = i_height;
	}
};

//��������
struct   feature_label
{
	std::string en;					   /* Ӣ���� */
	std::string ch;					   /* ������ */
};

//������������
union   measure_shape
{
	measure_ellipse ellipse;		   /* ��Բ���� */
	measure_line line;				   /* ֱ������ */
	measure_shape() { new (&ellipse) measure_ellipse; }
};

//��������
struct   measure_feature
{
	int id = -1;					   /* 0 ����ID */
	double prob = 0;				   /* 0 ����������Ŷ� */
	int type = 0;					   /* 1 �������1 - line, 2 - ellipse */
	double value = 0;				   /* 1 ����ֵ */
	int best_seq = -1;				   /* 1 ����֡��� */
	int best_pts = -1;				   /* 1 ����֡ʱ��� */
	double best_value = 0;			   /* 1 ���Ų���ֵ */
	std::string label;				   /* 1 ���� BDP HL ������*/
	bin_rect bin;					   /* 0 ���ο����Ϊ��ʱ�����ֵ */
	measure_shape shape;			   /* 1 ��״���� */
};

//�������
struct   measure_result
{
	int image_id = -1;							    /* ��״���� */
	double scale = -1;							    /* ��״���� */
	std::vector<measure_feature> measure_vector;    /* ��״���� */
};

//QC�÷�
struct   qc_score
{
	int num_in_sp = -1;				/* 1 �������ڵ���� */
	double value = 0;				/* 1 �÷� */
	double limit = 0;				/* 0 �÷������� */
};

//����QC
struct sp_qc
{
	int hash_id = -1;				/* ��ID */
	int index = -1;					/* λ��id */
	int priority = 0;				/* ���ȼ� */
	double pl_score = 0;			/* ����QC�ܷ� */
	std::map<int, qc_score> qc;		/* qc������ */
};

//QC����λ��
struct stuExamGroupEx
{
	bool needExam = true;			/* ��Ҫ���� */
	int hash_id = -1;				/* ����id */
	int index = 0;					/* λ������ ,����ӵ�λ�ã� ������Ƿ��� ���� 1�� �Ƿ������1��ʼ�� ���������id ����һ����*/
};

//QC����
struct stuExamQuestionEx
{
	std::vector<stuExamGroupEx> vecGroup;	/* �������� */
};

//QC��Ϣ
struct   qc_info
{
	std::string label_en;			/* Ӣ�ı�ǩ */
	std::string label_ch;			/* ���ı�ǩ */
	double limit = 0;				/* �÷������� */
	int belong_to_sp = -1;			/* �������� - 20210824 */
	int num_in_sp = -1;				/* �������ڵ���� */
	std::vector<int> sp_qc_list;	/* �����QC�б� */
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
	int x = 0;				   /* 1 ����x  20210814 modify unsigned int to int */
	int y = 0;				   /* 1 ����y 20210814 modify unsigned int to int */
	int w = 0;				   /* 1 ����w 20210814 modify unsigned int to int */
	int h = 0;				   /* 1 ����h 20210814 modify unsigned int to int */
	float prob = 0;			   /* 1 ���Ŷ� */
	int obj_id = -1;		   /* 0 ID 20210814 modify unsigned int to int */
	int track_id = 0;		   /* 0 δʹ�� 20210814 modify unsigned int to int */
	int frames_counter = 0;    /* 0 δʹ�� 20210814 modify unsigned int to int  */
	float x_3d = 0;			   /* 0 δʹ�� */
	float y_3d = 0;			   /* 0 δʹ�� */
	float z_3d = 0;			   /* 0 δʹ�� */
};

//�������
struct   bbox_s :bbox_t
{
	//����״̬
	enum ResultStatus 
	{
		None = 0,					   /* �� */
		Normal = 1,					   /* ���� */
		Suspect = 2,				   /* �����쳣 */
		Abnormal = 3,				   /* �쳣 */
		Substandard = 4,			   /* ���ƷǱ�׼(����) */
	}state = None;					   /* 1 ����/����״̬*/
	int hash_id = -1;				   /* 1 ��ID */
	//bool is_plane = false;			   /* 1 �����ʶ */
	bool is_measured = false;		   /* 1 �Ѳ�����ʶ */
	bool is_visible = false;		   /* 1 �Ѽ��ʶ */
	bool is_standard = true;		   /* 0 ��׼������ʶ */
	bool is_color = false;			   /* 0 �ʳ���ʶ */
	bool is_message_only = false;	   /* 1 ������Ϣ��ʶ��Ϊtrueʱ������ȡis_visible�ֶ� */
	int best_seq = -1;				   /* 1 ����֡��� */
	int best_pts = -1;				   /* 1 ����֡ʱ��� */
	ResultStatus best_state = None;	   /* 1 ����֡״̬ */
	std::vector<measure_feature> measure_vector;	/* 1 �������� */
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

//���������� PP/SP
struct   bbox_bag :bbox_s
{
	bool is_plane = false;							/* �����ʶ */											
	std::vector<bbox_s> member;						/* �����ڳ�Ա���� */
	//std::map<int, qc_score> qc;					/* QC������ */
	std::vector<sp_qc> pl_qc;						/* ���п��ܵ�QC���� */
	enPositionStatus pos = enNone;					/* ��ǰ��������λ�� */
	enFrameStatus play_status = enUndetected;		/* ����/��ͣ */
	//double pl_score = 0;							/* ����QC�ܷ� */
	std::vector<enCauseOfSuspect> suspect_cause;	/* �������Ƶ�ԭ�� */
	//int pl_group = -1;							/* ��-1ʱ�������ͬ�Ķ���������������������Ҫ�ϲ� */
	float weight_prob = 0;							/* ��Ȩ���Ŷ� */
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

//֡�����
struct   detection_result
{
	long long seq = -1;									/* ֡��� */
	long long pts = -1;									/* ֡ʱ��� */
	int screen_num = 1;									/* ��������Ļ�� */
	//double gestational = -1;							/* ����õ��ľ������� */
	enPositionStatus roi_pos = enNone;					/* ��ǰ�������λ�ã���/����/�� */
	enFrameStatus frame_status_left = enUndetected;		/* ����״̬/����״̬ */
	enFrameStatus frame_status_right = enUndetected;	/* ����״̬ */
	bin_rect roi_rect;									/* ROI�ü����� */
	bin_rect meas_roi_rect;								/* ����ROI�ü����� */
	std::vector<bbox_bag> vector_boxbag;				/* ���� */
};



//ƴ������
struct   splicing_unit
{
	int hash_id = -1;								/* ��ID */
	double prob = 0;								/* ����֡���Ŷ� */
	long long seq = -1;								/* ����֡��� */
	long long pts = -1;								/* ����֡ʱ��� */
	bbox_s::ResultStatus state = bbox_s::None;		/* ����֡״̬ */
	bool is_visible = false;						/* �Ѽ��ʶ */
};

//��������
struct   feature_details
{
	int mapping_hash_id = -1;		/* ӳ������ */
	int useless = -1;				/* ����Ч */
	int blurry = -1;				/* ģ�� */
	int cut = -1;					/* �ü� */
	int color = -1;					/* �ʳ� */
	int normal = -1;				/* �������� */
	int abnormal = -1;				/* �쳣���� */
	int pp_pl = -1;					/* PP���� */
	int sp_pl = -1;					/* SP���� */
	int early_gestation = -1;		/* ������ */
	int mid_later_gestation = -1;	/* �������� */
	int exportable = -1;			/* ��������� */
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
	std::string strResultUUid = "";		//	Qc�ʿ� ͼƬ uuid
	std::string strResultNameEx = "";	//	Qc�ʿ� ͼƬ ����
	int			nSectionId = -1;		//	Qc�ʿ� �������ID
};

#pragma warning(pop)
#endif