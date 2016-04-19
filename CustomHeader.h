/*
 * CustomCore0.h
 *
 *  Created on: 2015-11-27
 *      Author: LRH
 */

#ifndef CUSTOMCORE0_H_
#define CUSTOMCORE0_H_

#include <xdc/runtime/System.h>
#include <xdc/runtime/Sysmin.h>
#include <ti/ipc/MessageQ.h>
//#include <ti/ipc/Notify.h>
//#include <xdc/runtime/System.h>	//System_printf()

#define	MODE_WORK					1
#define SLEEP_MODE					2

//FPGA clock fre
#define FPGA_CLK_FRE				100000000.0//100MHz
//���ڼ����һЩ����
#define	LIGHT_SPEED					300000000.0
#define WAVE_FRE					35000000000.0	//35GHz
#define LAMBDA						(LIGHT_SPEED/WAVE_FRE)
#define PI              			3.1415926535898
#define SIG_POEWR_MAX_DBM			-10
#define NOISE_POEWR_MAX_DBM			-20
#define AMPLITUDE_MAX				0xffff
#define	DISTANCE_DELAY_COMPENSATION	0
//MessageQ������
#define MSGQ_NAME_CORE0_CORE1       "Core0ToCore1MsgQ"
#define MSGQ_NAME_CORE0_CORE2       "Core0ToCore2MsgQ"
#define MSGQ_NAME_CORE0_CORE3       "Core0ToCore3MsgQ"
#define MSGQ_NAME_CORE0_CORE4       "Core0ToCore4MsgQ"
#define MSGQ_NAME_CORE0_CORE5       "Core0ToCore5MsgQ"
#define MSGQ_NAME_CORE0_CORE6       "Core0ToCore6MsgQ"
#define MSGQ_NAME_CORE0_CORE7       "Core0ToCore7MsgQ"
#define MSGQ_NAME_CORE34567_CORE1   "Core34567ToCore1MsgQ"
#define MSGQ_NAME_CORE2_CORE34567   "Core2ToCore34567MsgQ"
#define MSGQ_NAME_CORE3_CORE1       "Core3ToCore1MsgQ"
#define MSGQ_NAME_CORE4_CORE1       "Core4ToCore1MsgQ"
#define MSGQ_NAME_CORE5_CORE1       "Core5ToCore1MsgQ"
#define MSGQ_NAME_CORE6_CORE1       "Core6ToCore1MsgQ"
#define MSGQ_NAME_CORE7_CORE1       "Core7ToCore1MsgQ"
#define MSGQ_NAME_CORE2_CORE0       "Core2ToCore0MsgQ"
#define MSGQ_NAME_CORE2_CORE1       "Core2ToCore1MsgQ"
#define MSGQ_NAME_CORE2_CORE3		"Core2ToCore3MsgQ"
#define MSGQ_NAME_CORE2_CORE4		"Core2ToCore4MsgQ"
#define MSGQ_NAME_CORE2_CORE5		"Core2ToCore5MsgQ"
#define MSGQ_NAME_CORE2_CORE6		"Core2ToCore6MsgQ"
#define MSGQ_NAME_CORE2_CORE7		"Core2ToCore7MsgQ"
//heap ID
#define HEAP_ID_CORE0_CORE1			0
#define HEAP_ID_CORE0_CORE2			1
#define HEAP_ID_CORE2_CORE0			2
#define HEAP_ID_CORE2_CORE1			3
#define HEAP_ID_CORE2_CORE34567		4
#define HEAP_ID_CORE34567_CORE1		5
//heap buf������
#define	HEAP_BUF_NAME_CORE0_CORE1     "Core0ToCore1"
#define	HEAP_BUF_NAME_CORE0_CORE2     "Core0ToCore2"
#define	HEAP_BUF_NAME_CORE0_CORE3     "Core0ToCore3"
#define	HEAP_BUF_NAME_CORE0_CORE4     "Core0ToCore4"
#define	HEAP_BUF_NAME_CORE0_CORE5     "Core0ToCore5"
#define	HEAP_BUF_NAME_CORE0_CORE6     "Core0ToCore6"
#define	HEAP_BUF_NAME_CORE0_CORE7     "Core0ToCore7"
#define	HEAP_BUF_NAME_CORE34567_CORE1 "Core34567ToCore1"
#define	HEAP_BUF_NAME_CORE2_CORE34567 "Core2ToCore34567"
#define	HEAP_BUF_NAME_CORE2_CORE0     "Core2ToCore0"
#define	HEAP_BUF_NAME_CORE2_CORE1     "Core2ToCore1"
#define	HEAP_BUF_NAME_CORE3_CORE1     "Core3ToCore1"
#define	HEAP_BUF_NAME_CORE4_CORE1     "Core4ToCore1"
#define	HEAP_BUF_NAME_CORE5_CORE1     "Core5ToCore1"
#define	HEAP_BUF_NAME_CORE6_CORE1     "Core6ToCore1"
#define	HEAP_BUF_NAME_CORE7_CORE1     "Core7ToCore1"
#define	HEAP_BUF_NAME_CORE2_CORE3     "Core2ToCore3"
#define	HEAP_BUF_NAME_CORE2_CORE4     "Core2ToCore4"
#define	HEAP_BUF_NAME_CORE2_CORE5     "Core2ToCore5"
#define	HEAP_BUF_NAME_CORE2_CORE6     "Core2ToCore6"
#define	HEAP_BUF_NAME_CORE2_CORE7     "Core2ToCore7"
//processor ID
#define PROC_ID_CORE0 0
#define PROC_ID_CORE1 1
#define PROC_ID_CORE2 2
#define PROC_ID_CORE3 3
#define PROC_ID_CORE4 4
#define PROC_ID_CORE5 5
#define PROC_ID_CORE6 6
#define PROC_ID_CORE7 7
//notify ID
#define	LINE_ID_CORE0_CORE1 	0
#define	LINE_ID_CORE0_CORE2 	0
#define EVENT_ID_CORE0_CORE1 	5
#define EVENT_ID_CORE0_CORE2 	5
//UDP�˿ں�
#define UDP_PORT 45454
//
#define IPCGRH_SRC_ID 1
//
#define RAYLEIGH_PARAM 0.5
//ɢ������
#define SCATTERTING_POINT_NUM 10
//SRIO�Ķ˿ں�
#define SRIO_PORT_NUM 0
//
#define SRIO_BRR_0 0
#define SRIO_BRR_1 1
#define SRIO_BRR_2 2
#define SRIO_BRR_3 3
//һά���������
#define RANGE_PROFILE_NUM	32
//��Ԫ����
#define	ARRAY_NUM			96

/* Notify payload */
#define QMSS_RDY_NOTIFY 		0
#define MANUAL_MSG_RDY_NOTIFY 	1
#define	SELF_CHECKING_NOTIFY	2
#define WORK_ENABLE_NOTIFY		3
#define SLEEP_ENABLE_NOTIFY		4
#define	WORK_PARAM_SET_NOTIFY	5

/* Frame ID */
#define COMMUNICATION_CHECK		1
#define SELF_CHECKING			2
#define	WORK_ENABLE				3
#define	SLEEP_ENABLE			4
#define	SCATTERING_POINT_INPUT	5
#define	WORK_PARAM_SET			6

/* Target param bit31:16 */
#define	MANUAL_MODE				0x0000
#define	AUTO_MODE_PASS_BACK		0x0001
#define	AUTO_MODE_NO_PASS_BACK	0x0002

/* Target param bit15:0 */
#define	POINT_TARGET			0x0000
#define	RANGE_SPREAD_TARGET_0	0x0001
#define	RANGE_SPREAD_TARGET_1	0x0002
#define	RANGE_SPREAD_TARGET_2	0x0003

/* Jamming param */
#define	NO_JAMMING				0x00000000
#define	ISRJ_0					0x00010000
#define	ISRJ_1					0x00010001
#define	ISRJ_2					0x00010002

/* SRIO ����֡ */
typedef struct
{
	unsigned int	DopplerFrePinc;
	unsigned short  DistanceDelay;
	unsigned short  NoisePower;
	unsigned short 	RangeProfile[RANGE_PROFILE_NUM];
}SrioFrame0;
typedef struct
{
	unsigned short  OrientationVectorReal[ARRAY_NUM];
}SrioFrame1;
typedef struct
{
	unsigned short  OrientationVectorImag[ARRAY_NUM];
}SrioFrame2;

/* Ŀ�����  */
//��Ŀ��
typedef struct
{
	float TargetSpeedTran;
	float TargetSpeedRecv;
	float TargetPower;
	float TargetDistanceTran;
	float TargetDistanceRecv;
	float TargetTheta;
	float TargetPhi;
}PointTargetParam;
//��չĿ�꣬����0
typedef struct
{
	float TargetSpeedTran;
	float TargetSpeedRecv;
	float TargetDistanceTran;
	float TargetDistanceRecv;
	float TargetTheta;
	float TargetPhi;
	float TargetPt;
	float TargetG;
	float TargetAe;
	float TargetAttitudeTheta;
	float TargetAttitudePhi;
}RangeSpreadTargetParam0;
//��չĿ�꣬����1
typedef struct
{
	float TargetSpeedTran;
	float TargetSpeedRecv;
	float TargetPt;
	float TargetG;
	float TargetAe;
	float GroundCoordRadarTranX;
	float GroundCoordRadarTranY;
	float GroundCoordRadarTranZ;
	float GroundCoordTargetX;
	float GroundCoordTargetY;
	float GroundCoordTargetZ;
	float GroundCoordRadarRecvX;
	float GroundCoordRadarRecvY;
	float GroundCoordRadarRecvZ;
	float GroundCoordToRadarCoordAngleX;
	float GroundCoordToRadarCoordAngleY;
	float GroundCoordToRadarCoordAngleZ;
	float GroundCoordToTargetCoordAngleX;
	float GroundCoordToTargetCoordAngleY;
	float GroundCoordToTargetCoordAngleZ;
}RangeSpreadTargetParam1;
//��չĿ�꣬����2
typedef struct
{
	float TargetSpeedTran;
	float TargetSpeedRecv;
	float TargetPt;
	float TargetG;
	float TargetAe;
	float GroundCoordRadarTranX;
	float GroundCoordRadarTranY;
	float GroundCoordRadarTranZ;
	float GroundCoordTargetX;
	float GroundCoordTargetY;
	float GroundCoordTargetZ;
	float GroundCoordRadarRecvX;
	float GroundCoordRadarRecvY;
	float GroundCoordRadarRecvZ;
	float RadarCoordOxVectorX;
	float RadarCoordOxVectorY;
	float RadarCoordOxVectorZ;
	float RadarCoordOyVectorX;
	float RadarCoordOyVectorY;
	float RadarCoordOyVectorZ;
	float TargetCoordOxVectorX;
	float TargetCoordOxVectorY;
	float TargetCoordOxVectorZ;
	float TargetCoordOyVectorX;
	float TargetCoordOyVectorY;
	float TargetCoordOyVectorZ;
}RangeSpreadTargetParam2;


/* Message struct */
typedef struct
{
	MessageQ_MsgHeader 	header;
	int	 				TargetFrameId;
	union
	{
		PointTargetParam 			PointTargetParamMsg;
		RangeSpreadTargetParam0		RangeSpreadTargetParam0Msg;
		RangeSpreadTargetParam1 	RangeSpreadTargetParam1Msg;
		RangeSpreadTargetParam2 	RangeSpreadTargetParam2Msg;
	}TargetParam;
	float				NoisePower;
} MsgCore0ToCore2;

typedef struct
{
	MessageQ_MsgHeader 	header;
	int	 				FrameId;
} MsgCore0ToCore1;

typedef struct
{
	MessageQ_MsgHeader 	header;
	float               TargetAngleTheta;
	float               TargetAnglePhi;
} MsgCore0ToCore23456;

typedef struct
{
	MessageQ_MsgHeader 	header;
	unsigned short 		ProcId;
	unsigned short      OrientationVectorReal[20];	//Each core calculate and send 20 orientation vector
	unsigned short      OrientationVectorImag[20];
} MsgCore34567ToCore1;

/* �����Ҫ���͸���1�Ĳ��� */
typedef struct
{
	MessageQ_MsgHeader 	header;
	unsigned int 		DopplerFrePinc;
	unsigned short 		DistanceDelay;
	unsigned short  	NoisePower;
	unsigned short      RangeProfile[RANGE_PROFILE_NUM];
} MsgCore2ToCore1;

/* ����õĽǶ� */
typedef struct
{
	MessageQ_MsgHeader 	header;
	float				TargetAngleTheta;
	float				TargetAnglePhi;
} MsgCore2ToCore34567;


/* Ŀ������ش� */
typedef struct
{
	float	RangeProfile[RANGE_PROFILE_NUM];
}RangeSpreadTargetParam0SetBack;

typedef struct
{
	float	TargetDistanceTran;
	float	TargetDistanceRecv;
	float	RangeProfile[RANGE_PROFILE_NUM];
	float	LineDeviationTheta;
	float	LineDeviationPhi;
	float	AngleDeviationTheta;
	float	AngleDeviationPhi;
}RangeSpreadTargetParam12SetBack;

//����õ�Ŀ��ش�����
typedef struct
{
	MessageQ_MsgHeader 	header;
	union
	{
		RangeSpreadTargetParam0SetBack	RangeSpreadTargetParam0SetBackFrame;
		RangeSpreadTargetParam12SetBack	RangeSpreadTargetParam12SetBackFrame;
	}TargetParamBack;
}MsgCore2ToCore0;


/* ���Ų��� */
/* ��Ъ����ת��ʽ���� */
typedef struct
{
	float	Distance;
	float	Speed;
	float	Theta;
	float	Phi;
	float	Power;
	float	SampleWidth;
	float	RepeatWidth;
	float	RepeatStartTime;
	float	RepeatNum;
}JammingIsrjParam0;

typedef struct
{
	float	Speed;
	float	Power;
	float	GroundCoordJammingX;
	float	GroundCoordJammingY;
	float	GroundCoordJammingZ;
	float	SampleWidth;
	float	RepeatWidth;
	float	RepeatStartTime;
	float	RepeatNum;
}JammingIsrjParam1;

typedef struct
{
	int		JammingFrameId;
	union
	{
		JammingIsrjParam0	JammingIsrjParam0Hyplink;
		JammingIsrjParam1	JammingIsrjParam1Hyplink;
	}JammingParam;
}HyplinkDataDsp1ToDsp2;

/* ���������趨֡  */
typedef struct
{
	int		FrameId;
	int		TargetFrameId;
	union
	{
		PointTargetParam 		TargetParam0Data;
		RangeSpreadTargetParam0	RangeSpreadTargetParam0Data;
		RangeSpreadTargetParam1	RangeSpreadTargetParam1Data;
		RangeSpreadTargetParam2	RangeSpreadTargetParam2Data;
	}TargetFrame;
	int		JammingFrameId;
	union
	{
		JammingIsrjParam0		JammingIsrjParam0Data;
		JammingIsrjParam1		JammingIsrjParam1Data;
	}JammingFrame;
	float	NoisePower;
}WorkParamUdpFrame;


/* ���ڹ����������ûش����� */
typedef struct
{
	int		FrameId;
    int		TargetFrameId;
    union	WorkParamSetBack
    {
        char	PointTargetBack;
        RangeSpreadTargetParam0SetBack	RangeSpreadTargetParam0SetBackFrame;
        RangeSpreadTargetParam12SetBack	RangeSpreadTargetParam12SetBackFrame;
    }TargetParamBack;
    int		JammingFrameId;
    union
    {
        char	NoJammingBack;
        char	IsrjParam0Back;
    }JammingParamBack;
    float	NoisePower;
}WorkParamSetBack;


/* ɢ���ṹ�� */
typedef struct
{
	float	RCS;
	float	X;
	float	Y;
	float	Z;
}Point;

typedef struct
{
	int		PointNum;
	Point	PointData[1024];	//���ɢ�����
}ScatteringPoint;

/* ɢ�����Ϣ����֡ */
typedef struct
{
	int				FrameId;
	ScatteringPoint	ScatteringPointData;
}ScatteringPointUdpFrame;





#endif /* CUSTOMCORE0_H_ */
