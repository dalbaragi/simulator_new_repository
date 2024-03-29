#include <math.h>
#include <stdlib.h>

#include "../CustomHeader.h"

//---------------散射点信息存储位置--------------------------
extern ScatteringPoint		*ScatteringPointPtr;

/* 顺序按照OY、OZ、OX依次旋转phi、theta、gamma */
//计算坐标,已知从A坐标系转换到B坐标系的旋转关系，求A坐标系中点在B坐标系下坐标
void CoordinateCalculateOriginToTrans(float OriginToTransAngleGamma, float OriginToTransAnglePhi, float OriginToTransAngleTheta,
                                   float OriginalX, float OriginalY, float OriginalZ,
                                   float *TransX, float *TransY, float *TransZ)
{
    float TransMatrix[3][3];

    float OriginToTransAnglePhiRad = OriginToTransAnglePhi / 3.1415926 * 180;
    float OriginToTransAngleThetaRad = OriginToTransAngleTheta / 3.1415926 * 180;
    float OriginToTransAngleGammaRad = OriginToTransAngleGamma / 3.1415926 * 180;

    float CosPhi = cos(OriginToTransAnglePhiRad);
    float SinPhi = sin(OriginToTransAnglePhiRad);
    float CosTheta = cos(OriginToTransAngleThetaRad);
    float SinTheta = sin(OriginToTransAngleThetaRad);
    float CosGamma = cos(OriginToTransAngleGammaRad);
    float SinGamma = sin(OriginToTransAngleGammaRad);

    TransMatrix[0][0] = CosPhi*CosTheta;
    TransMatrix[0][1] = -CosPhi*SinTheta*CosGamma + SinPhi*SinGamma;
    TransMatrix[0][2] = CosPhi*SinTheta*SinGamma + SinPhi*CosGamma;
    TransMatrix[1][0] = SinTheta;
    TransMatrix[1][1] = CosTheta*CosGamma;
    TransMatrix[1][2] = -CosTheta*SinGamma;
    TransMatrix[2][0] = -SinPhi*CosTheta;
    TransMatrix[2][1] = SinPhi*SinTheta*CosGamma + CosPhi*SinGamma;
    TransMatrix[2][2] = -SinPhi*SinTheta*SinGamma + CosPhi*CosGamma;

    *TransX = OriginalX*TransMatrix[0][0] + OriginalY*TransMatrix[0][1] + OriginalZ*TransMatrix[0][2];
    *TransY = OriginalX*TransMatrix[1][0] + OriginalY*TransMatrix[1][1] + OriginalZ*TransMatrix[1][2];
    *TransZ = OriginalX*TransMatrix[2][0] + OriginalY*TransMatrix[2][1] + OriginalZ*TransMatrix[2][2];
}

//计算坐标,已知从A坐标系转换到B坐标系的旋转关系，求B坐标系中点在A坐标系下坐标
void CoordinateCalculateTransToOrigin(float TransToOriginAngleGamma, float TransToOriginAnglePhi, float TransToOriginAngleTheta,
                                   float OriginalX, float OriginalY, float OriginalZ,
                                   float *TransX, float *TransY, float *TransZ)
{
    float TransMatrix[3][3];

    float TransToOriginAnglePhiRad = TransToOriginAnglePhi / 3.1415926 * 180;
    float TransToOriginAngleThetaRad = TransToOriginAngleTheta / 3.1415926 * 180;
    float TransToOriginAngleGammaRad = TransToOriginAngleGamma / 3.1415926 * 180;

    float CosPhi = cos(TransToOriginAnglePhiRad);
    float SinPhi = sin(TransToOriginAnglePhiRad);
    float CosTheta = cos(TransToOriginAngleThetaRad);
    float SinTheta = sin(TransToOriginAngleThetaRad);
    float CosGamma = cos(TransToOriginAngleGammaRad);
    float SinGamma = sin(TransToOriginAngleGammaRad);

    TransMatrix[0][0] = CosPhi*CosTheta;
    TransMatrix[0][1] = SinTheta;
    TransMatrix[0][2] = -SinPhi*CosTheta;
    TransMatrix[1][0] = -CosPhi*SinTheta*CosGamma + SinPhi*SinGamma;
    TransMatrix[1][1] = CosTheta*CosGamma;
    TransMatrix[1][2] = SinPhi*SinTheta*CosGamma + CosPhi*SinGamma;
    TransMatrix[2][0] = CosPhi*SinTheta*SinGamma + SinPhi*CosGamma;
    TransMatrix[2][1] = -CosTheta*SinGamma;
    TransMatrix[2][2] = -SinPhi*SinTheta*SinGamma + CosPhi*CosGamma;

    *TransX = OriginalX*TransMatrix[0][0] + OriginalY*TransMatrix[0][1] + OriginalZ*TransMatrix[0][2];
    *TransY = OriginalX*TransMatrix[1][0] + OriginalY*TransMatrix[1][1] + OriginalZ*TransMatrix[1][2];
    *TransZ = OriginalX*TransMatrix[2][0] + OriginalY*TransMatrix[2][1] + OriginalZ*TransMatrix[2][2];
}


/* 计算线偏差和角偏差 */
void LineDeviationCal(
				int		ScatteringPointNum,
				Point	*PointSight,	//视线坐标系下散射点坐标
				Point	*PointGround,	//地理坐标系下散射点坐标
				float   RadarTranX,
				float   RadarTranY,
				float   RadarTranZ,
				float   TargetX,
				float   TargetY,
				float   TargetZ,
				float   RadarRecvX,
				float   RadarRecvY,
				float   RadarRecvZ,
				float	*LineDeviationY,
				float	*LineDeviationZ
)
{
	int 	i, j;

	//计算相对幅度，为RCS取根号
	float	*RelativeAmp;	//相对幅度
	RelativeAmp = (float*)malloc(sizeof(float) * ScatteringPointNum);
	for(i = 0 ; i < ScatteringPointNum ; ++i)
	{
		RelativeAmp[i] = sqrt(PointSight[i].RCS);
	}


	//计算相位
	float	*Phase;	//每个散射点的相位
	Phase = (float*)malloc(sizeof(float) * ScatteringPointNum);
	for(i = 0 ; i < ScatteringPointNum ; ++i)
	{
		float	ScatteringPointR1, ScatteringPointR2;	//每个散射点的距离，分别为发射和接收
		float	GroundScatteringPointX;	//散射点在地理坐标系下的坐标
		float	GroundScatteringPointY;
		float	GroundScatteringPointZ;

		GroundScatteringPointX = TargetX + PointGround[i].X;
		GroundScatteringPointY = TargetY + PointGround[i].Y;
		GroundScatteringPointZ = TargetZ + PointGround[i].Z;

		ScatteringPointR1 = sqrt(	(GroundScatteringPointX - RadarTranX) * (GroundScatteringPointX - RadarTranX) +
									(GroundScatteringPointY - RadarTranY) * (GroundScatteringPointY - RadarTranY) +
									(GroundScatteringPointZ - RadarTranZ) * (GroundScatteringPointZ - RadarTranZ));

		ScatteringPointR2 = sqrt(	(GroundScatteringPointX - RadarRecvX) * (GroundScatteringPointX - RadarRecvX) +
									(GroundScatteringPointY - RadarRecvY) * (GroundScatteringPointY - RadarRecvY) +
									(GroundScatteringPointZ - RadarRecvZ) * (GroundScatteringPointZ - RadarRecvZ));

		Phase[i] = 2 * PI / LAMBDA * (ScatteringPointR1 + ScatteringPointR2);
	}


	//线偏差的分母部分
	float	LineDeviationMemberSightY = 0;	//视线坐标系下Y方向坐标
	float	LineDeviationMemberSightZ = 0;	//视线坐标系下Z方向坐标
	for(i = 0 ; i < ScatteringPointNum ; ++i)
	{
		for(j = 0 ; j < ScatteringPointNum ; ++j)
		{
			LineDeviationMemberSightY += RelativeAmp[i] * RelativeAmp[j] * PointSight[i].Y * cos(Phase[i] - Phase[j]);
			LineDeviationMemberSightZ += RelativeAmp[i] * RelativeAmp[j] * PointSight[i].Z * cos(Phase[i] - Phase[j]);
		}
	}


	//线偏差的分子部分
	float	LineDeviationDenominator;
	for(i = 0 ; i < ScatteringPointNum ; ++i)
	{
		LineDeviationDenominator = RelativeAmp[i] * RelativeAmp[j] * cos(Phase[i] - Phase[j]);
	}
	*LineDeviationY = LineDeviationMemberSightY / LineDeviationDenominator;
	*LineDeviationZ = LineDeviationMemberSightZ / LineDeviationDenominator;

	free(RelativeAmp);
	free(Phase);
}


/* 点目标模型参数计算 */
void PointTargetCal(MsgCore0ToCore2 *Msg0To2Ptr, MsgCore2ToCore1 *Msg2To1Ptr, MsgCore2ToCore34567 *Msg2To34567Ptr)
{
	int i;

	//用距离计算延时
	Msg2To1Ptr->DistanceDelay =
			((Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetDistanceRecv +
					Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetDistanceTran)
					/ LIGHT_SPEED * FPGA_CLK_FRE) + DISTANCE_DELAY_COMPENSATION;
	//用速度计算频率控制字
	Msg2To1Ptr->DopplerFrePinc = 2 *
								(Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetSpeedTran +
										Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetSpeedRecv)
								* WAVE_FRE / LIGHT_SPEED * 0xffffffff / FPGA_CLK_FRE;
	//用功率计算幅度
	for(i = 0 ; i < RANGE_PROFILE_NUM ; i++)
	{
		Msg2To1Ptr->RangeProfile[i] = 0;
	}
	Msg2To1Ptr->RangeProfile[(int)(RANGE_PROFILE_NUM/2)] =
			sqrt(pow(10,((Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetPower - SIG_POEWR_MAX_DBM)/10))
					* AMPLITUDE_MAX * AMPLITUDE_MAX);

	//噪声功率
	Msg2To1Ptr->NoisePower = sqrt(pow(10,((Msg0To2Ptr->NoisePower - SIG_POEWR_MAX_DBM)/10)) * AMPLITUDE_MAX * AMPLITUDE_MAX);

	//角度赋值
	Msg2To34567Ptr->TargetAngleTheta = Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetTheta;
	Msg2To34567Ptr->TargetAnglePhi = Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetPhi;
}

/* 扩展目标模型，参数0计算 */
void RangeSpreadTargetParam0Cal(MsgCore0ToCore2 *Msg0To2Ptr, MsgCore2ToCore1 *Msg2To1Ptr,
								MsgCore2ToCore34567 *Msg2To34567Ptr, MsgCore2ToCore0 *Msg2To0Ptr,
								ScatteringPoint *ScatteringPointPtr)
{
	int i;
	//视线坐标系下点信息
	Point PointSight[1024];
	for(i = 0 ; i < ScatteringPointPtr->PointNum ; ++i)
	{
		//由目标固联坐标系转换到视线坐标系
		CoordinateCalculateOriginToTrans(
						0,
						Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetAttitudePhi,
						Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetAttitudeTheta,
						ScatteringPointPtr->PointData[i].X,
						ScatteringPointPtr->PointData[i].Y,
						ScatteringPointPtr->PointData[i].Z,
						&(PointSight[i].X),
						&(PointSight[i].Y),
						&(PointSight[i].Z));
	}

	//得出一维距离像
	for(i = 0 ; i < RANGE_PROFILE_NUM ; i++)
	{
		Msg2To1Ptr->RangeProfile[i] = 0;
	}
	for(i = 0 ; i < ScatteringPointPtr->PointNum ; ++i)
	{
		float	temp = sqrt((PointSight[i].X)*(PointSight[i].X) +
						(PointSight[i].Y)*(PointSight[i].Y) +
						(PointSight[i].Z)*(PointSight[i].Z));
		int		PositionTemp;
		if(PointSight[i].X > 0)
			PositionTemp = temp / (LIGHT_SPEED/FPGA_CLK_FRE/2);
		else
			PositionTemp = - temp / (LIGHT_SPEED/FPGA_CLK_FRE/2);
		PositionTemp += RANGE_PROFILE_NUM/2;	//使RANGE_PROFILE_NUM/2为0位置
		Msg2To1Ptr->RangeProfile[PositionTemp] += PointSight[i].RCS;
	}

	//发射与接收距离
	int	R1 = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetDistanceTran;
	int	R2 = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetDistanceRecv;

	//用功率计算幅度
	for(i = 0 ; i < RANGE_PROFILE_NUM ; ++i)
	{
		double Power = 	(double)Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetG +
						(double)Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetPt +
						(double)Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetAe +
						(double)Msg2To1Ptr->RangeProfile[i] -
						10 * log10(4 * PI * (double)R1 * R1) /
						10 * log10(4 * PI * (double)R2 * R2);
		Msg2To1Ptr->RangeProfile[i] =
				sqrt(pow(10,((Power - SIG_POEWR_MAX_DBM)/10)) * AMPLITUDE_MAX * AMPLITUDE_MAX);
	}

	//噪声功率
	Msg2To1Ptr->NoisePower = sqrt(pow(10,((Msg0To2Ptr->NoisePower - SIG_POEWR_MAX_DBM)/10)) * AMPLITUDE_MAX * AMPLITUDE_MAX);

	//用距离计算延时
	Msg2To1Ptr->DistanceDelay = (R1 + R2) / LIGHT_SPEED * FPGA_CLK_FRE + DISTANCE_DELAY_COMPENSATION;
	//用速度计算频率控制字
	Msg2To1Ptr->DopplerFrePinc = 2 *
								(Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetSpeedTran +
										Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetSpeedRecv)
								* WAVE_FRE / LIGHT_SPEED * 0xffffffff / FPGA_CLK_FRE;

	//角度赋值
	Msg2To34567Ptr->TargetAngleTheta = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetTheta;
	Msg2To34567Ptr->TargetAnglePhi = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetPhi;

	//回传数据
	memcpy(	Msg2To0Ptr->TargetParamBack.RangeSpreadTargetParam0SetBackFrame.RangeProfile,
			Msg2To1Ptr->RangeProfile,
			sizeof(Msg2To1Ptr->RangeProfile));
}

/* 扩展目标模型，参数1计算 */
void RangeSpreadTargetParam1Cal(MsgCore0ToCore2 *Msg0To2Ptr, MsgCore2ToCore1 *Msg2To1Ptr,
								MsgCore2ToCore34567 *Msg2To34567Ptr, MsgCore2ToCore0 *Msg2To0Ptr,
								ScatteringPoint *ScatteringPointPtr)
{
	int i;

	float	TranR, RecvR;

	float	GroundCoordToRadarCoordAngleX  = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordToRadarCoordAngleX;
	float	GroundCoordToRadarCoordAngleY  = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordToRadarCoordAngleY;
	float	GroundCoordToRadarCoordAngleZ  = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordToRadarCoordAngleZ;
	float	GroundCoordToTargetCoordAngleX = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordToTargetCoordAngleX;
	float	GroundCoordToTargetCoordAngleY = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordToTargetCoordAngleY;
	float	GroundCoordToTargetCoordAngleZ = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordToTargetCoordAngleZ;

	float	GroundCoordRadarTranX = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordRadarTranX;
	float 	GroundCoordRadarTranY = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordRadarTranY;
	float 	GroundCoordRadarTranZ = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordRadarTranZ;
	float 	GroundCoordTargetX    = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordTargetX;
	float 	GroundCoordTargetY    = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordTargetY;
	float 	GroundCoordTargetZ    = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordTargetZ;
	float 	GroundCoordRadarRecvX = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordRadarRecvX;
	float 	GroundCoordRadarRecvY = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordRadarRecvY;
	float 	GroundCoordRadarRecvZ = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordRadarRecvZ;

	/* 计算发送和接收距离 */
	TranR = sqrt(	(GroundCoordTargetX - GroundCoordRadarTranX)*(GroundCoordTargetX - GroundCoordRadarTranX) +
					(GroundCoordTargetY - GroundCoordRadarTranY)*(GroundCoordTargetY - GroundCoordRadarTranY) +
					(GroundCoordTargetZ - GroundCoordRadarTranZ)*(GroundCoordTargetZ - GroundCoordRadarTranZ));

	RecvR = sqrt(	(GroundCoordRadarRecvX - GroundCoordTargetX)*(GroundCoordRadarRecvX - GroundCoordTargetX) +
					(GroundCoordRadarRecvY - GroundCoordTargetY)*(GroundCoordRadarRecvY - GroundCoordTargetY) +
					(GroundCoordRadarRecvZ - GroundCoordTargetZ)*(GroundCoordRadarRecvZ - GroundCoordTargetZ));

	/* 用距离计算延时 */
	Msg2To1Ptr->DistanceDelay =
			((TranR + RecvR) / LIGHT_SPEED * FPGA_CLK_FRE) + DISTANCE_DELAY_COMPENSATION;
	/* 用速度计算频率控制字 */
	Msg2To1Ptr->DopplerFrePinc = 2 *
								(Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.TargetSpeedTran +
										Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.TargetSpeedRecv)
								* WAVE_FRE / LIGHT_SPEED * 0xffffffff / FPGA_CLK_FRE;


	/* 计算目标在阵面坐标系下的方位和俯仰角 */
	float	RadarCoordTheta;
	float	RadarCoordPhi;
	float	TargetRadarX, TargetRadarY, TargetRadarZ;
	CoordinateCalculateOriginToTrans(
					GroundCoordToTargetCoordAngleX, GroundCoordToRadarCoordAngleY, GroundCoordToTargetCoordAngleZ,
					Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordTargetX,
					Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordTargetY,
					Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordTargetZ,
					&TargetRadarX,
					&TargetRadarY,
					&TargetRadarZ
					);
	//计算得出阵面坐标系下目标的坐标
	TargetRadarX -= Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordRadarRecvX;
	TargetRadarY -= Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordRadarRecvY;
	TargetRadarZ -= Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordRadarRecvZ;
	RadarCoordTheta = atan(TargetRadarZ/TargetRadarX);
	RadarCoordPhi = atan(TargetRadarY / sqrt(TargetRadarX*TargetRadarX + TargetRadarZ*TargetRadarZ));


	/* 计算视线坐标系下散射点位置 */
	//视线坐标系下点信息
	Point*	PointSight = (Point*)malloc(sizeof(Point) * ScatteringPointPtr->PointNum);
	Point*	PointGround = (Point*)malloc(sizeof(Point) * ScatteringPointPtr->PointNum);
	for(i = 0 ; i < ScatteringPointPtr->PointNum ; ++i)
	{
		//散射点坐标从目标固联坐标系转换到地理坐标系

		CoordinateCalculateTransToOrigin(
						GroundCoordToTargetCoordAngleX, GroundCoordToTargetCoordAngleY, GroundCoordToTargetCoordAngleZ,
						ScatteringPointPtr->PointData[i].X,
						ScatteringPointPtr->PointData[i].Y,
						ScatteringPointPtr->PointData[i].Z,
						&(PointGround[i].X), &(PointGround[i].Y), &(PointGround[i].Z)
						);
		//散射点坐标从地理坐标系转换到阵面坐标系
		Point PointRadar;
		CoordinateCalculateOriginToTrans(
						GroundCoordToRadarCoordAngleX, GroundCoordToRadarCoordAngleY, GroundCoordToRadarCoordAngleZ,
						PointGround[i].X,
						PointGround[i].Y,
						PointGround[i].Z,
						&(PointRadar.X), &(PointRadar.Y), &(PointRadar.Z)
						);
		//散射点坐标从阵面坐标系转换到视线坐标系
		CoordinateCalculateOriginToTrans(
						0,
						RadarCoordPhi,
						RadarCoordTheta,
						PointRadar.X,
						PointRadar.Y,
						PointRadar.Z,
						&(PointSight[i].X),
						&(PointSight[i].Y),
						&(PointSight[i].Z));
	}

	/* 计算线偏离值和角偏差 */
	float	LineDeviationY;
	float	LineDeviationZ;
	float	AngleDeviationTheta;
	float	AngleDeviationPhi;
	LineDeviationCal(
					ScatteringPointPtr->PointNum,
					PointSight,		//视线坐标系下散射点坐标
					PointGround,	//地理坐标系下散射点坐标
					GroundCoordRadarTranX,
					GroundCoordRadarTranY,
					GroundCoordRadarTranZ,
					GroundCoordTargetX,
					GroundCoordTargetY,
					GroundCoordTargetZ,
					GroundCoordRadarRecvX,
					GroundCoordRadarRecvY,
					GroundCoordRadarRecvZ,
					&LineDeviationY,
					&LineDeviationZ
	);
	AngleDeviationTheta = LineDeviationY / RecvR;
	AngleDeviationPhi = LineDeviationZ / RecvR;


	/* 角度赋值  */
	Msg2To34567Ptr->TargetAngleTheta = RadarCoordTheta + AngleDeviationTheta;
	Msg2To34567Ptr->TargetAnglePhi = RadarCoordPhi + AngleDeviationPhi;


	/* 得出一维距离像 */
	for(i = 0 ; i < RANGE_PROFILE_NUM ; i++)
	{
		Msg2To1Ptr->RangeProfile[i] = 0;
	}
	for(i = 0 ; i < ScatteringPointPtr->PointNum ; ++i)
	{
		float	TranRangeTemp = sqrt(	pow(GroundCoordTargetX + PointGround[i].X - GroundCoordRadarTranX, 2) +
										pow(GroundCoordTargetY + PointGround[i].Y - GroundCoordRadarTranY, 2) +
										pow(GroundCoordTargetZ + PointGround[i].Z - GroundCoordRadarTranZ, 2));
		float	RecvRangeTemp = sqrt(	pow(GroundCoordTargetX + PointGround[i].X - GroundCoordRadarRecvX, 2) +
										pow(GroundCoordTargetY + PointGround[i].Y - GroundCoordRadarRecvY, 2) +
										pow(GroundCoordTargetZ + PointGround[i].Z - GroundCoordRadarRecvZ, 2));
		Msg2To1Ptr->RangeProfile[(int)((TranRangeTemp + RecvRangeTemp - TranR - RecvR) / (LIGHT_SPEED/FPGA_CLK_FRE/2) + RANGE_PROFILE_NUM/2)]
		                         	 += PointSight[i].RCS;
	}
	//用功率计算幅度
	for(i = 0 ; i < RANGE_PROFILE_NUM ; ++i)
	{
		double Power = 	(double)Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.TargetG +
						(double)Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.TargetPt +
						(double)Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.TargetAe +
						(double)Msg2To1Ptr->RangeProfile[i] -
							10 * log10(4 * PI * (double)RecvR * RecvR) /
							10 * log10(4 * PI * (double)TranR * TranR);
		Msg2To1Ptr->RangeProfile[i] =
				sqrt(pow(10,((Power - SIG_POEWR_MAX_DBM)/10)) * AMPLITUDE_MAX * AMPLITUDE_MAX);
	}

	//噪声功率
	Msg2To1Ptr->NoisePower = sqrt(pow(10,((Msg0To2Ptr->NoisePower - SIG_POEWR_MAX_DBM)/10)) * AMPLITUDE_MAX * AMPLITUDE_MAX);

	//回传数据
	Msg2To0Ptr->TargetParamBack.RangeSpreadTargetParam12SetBackFrame.AngleDeviationPhi = AngleDeviationPhi;
	Msg2To0Ptr->TargetParamBack.RangeSpreadTargetParam12SetBackFrame.AngleDeviationTheta = AngleDeviationTheta;
	Msg2To0Ptr->TargetParamBack.RangeSpreadTargetParam12SetBackFrame.LineDeviationPhi = LineDeviationZ;
	Msg2To0Ptr->TargetParamBack.RangeSpreadTargetParam12SetBackFrame.LineDeviationTheta = LineDeviationY;
	Msg2To0Ptr->TargetParamBack.RangeSpreadTargetParam12SetBackFrame.TargetDistanceRecv = RecvR;
	Msg2To0Ptr->TargetParamBack.RangeSpreadTargetParam12SetBackFrame.TargetDistanceTran = TranR;
	memcpy(	Msg2To0Ptr->TargetParamBack.RangeSpreadTargetParam12SetBackFrame.RangeProfile,
			Msg2To1Ptr->RangeProfile,
			sizeof(Msg2To1Ptr->RangeProfile));

	free(PointSight);
	free(PointGround);
}

/* 扩展目标模型，参数2计算 */
void RangeSpreadTargetParam2Cal(MsgCore0ToCore2 *Msg0To2Ptr, MsgCore2ToCore1 *Msg2To1Ptr,
								MsgCore2ToCore34567 *Msg2To34567Ptr, MsgCore2ToCore0 *Msg2To0Ptr,
								ScatteringPoint *ScatteringPointPtr)
{

}



