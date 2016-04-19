#include <math.h>
#include <stdlib.h>

#include "../CustomHeader.h"

//---------------ɢ�����Ϣ�洢λ��--------------------------
extern ScatteringPoint		*ScatteringPointPtr;

/* ˳����OY��OZ��OX������תphi��theta��gamma */
//��������,��֪��A����ϵת����B����ϵ����ת��ϵ����A����ϵ�е���B����ϵ������
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

//��������,��֪��A����ϵת����B����ϵ����ת��ϵ����B����ϵ�е���A����ϵ������
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


/* ������ƫ��ͽ�ƫ�� */
void LineDeviationCal(
				int		ScatteringPointNum,
				Point	*PointSight,	//��������ϵ��ɢ�������
				Point	*PointGround,	//��������ϵ��ɢ�������
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

	//������Է��ȣ�ΪRCSȡ����
	float	*RelativeAmp;	//��Է���
	RelativeAmp = (float*)malloc(sizeof(float) * ScatteringPointNum);
	for(i = 0 ; i < ScatteringPointNum ; ++i)
	{
		RelativeAmp[i] = sqrt(PointSight[i].RCS);
	}


	//������λ
	float	*Phase;	//ÿ��ɢ������λ
	Phase = (float*)malloc(sizeof(float) * ScatteringPointNum);
	for(i = 0 ; i < ScatteringPointNum ; ++i)
	{
		float	ScatteringPointR1, ScatteringPointR2;	//ÿ��ɢ���ľ��룬�ֱ�Ϊ����ͽ���
		float	GroundScatteringPointX;	//ɢ����ڵ�������ϵ�µ�����
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


	//��ƫ��ķ�ĸ����
	float	LineDeviationMemberSightY = 0;	//��������ϵ��Y��������
	float	LineDeviationMemberSightZ = 0;	//��������ϵ��Z��������
	for(i = 0 ; i < ScatteringPointNum ; ++i)
	{
		for(j = 0 ; j < ScatteringPointNum ; ++j)
		{
			LineDeviationMemberSightY += RelativeAmp[i] * RelativeAmp[j] * PointSight[i].Y * cos(Phase[i] - Phase[j]);
			LineDeviationMemberSightZ += RelativeAmp[i] * RelativeAmp[j] * PointSight[i].Z * cos(Phase[i] - Phase[j]);
		}
	}


	//��ƫ��ķ��Ӳ���
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


/* ��Ŀ��ģ�Ͳ������� */
void PointTargetCal(MsgCore0ToCore2 *Msg0To2Ptr, MsgCore2ToCore1 *Msg2To1Ptr, MsgCore2ToCore34567 *Msg2To34567Ptr)
{
	int i;

	//�þ��������ʱ
	Msg2To1Ptr->DistanceDelay =
			((Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetDistanceRecv +
					Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetDistanceTran)
					/ LIGHT_SPEED * FPGA_CLK_FRE) + DISTANCE_DELAY_COMPENSATION;
	//���ٶȼ���Ƶ�ʿ�����
	Msg2To1Ptr->DopplerFrePinc = 2 *
								(Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetSpeedTran +
										Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetSpeedRecv)
								* WAVE_FRE / LIGHT_SPEED * 0xffffffff / FPGA_CLK_FRE;
	//�ù��ʼ������
	for(i = 0 ; i < RANGE_PROFILE_NUM ; i++)
	{
		Msg2To1Ptr->RangeProfile[i] = 0;
	}
	Msg2To1Ptr->RangeProfile[(int)(RANGE_PROFILE_NUM/2)] =
			sqrt(pow(10,((Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetPower - SIG_POEWR_MAX_DBM)/10))
					* AMPLITUDE_MAX * AMPLITUDE_MAX);

	//��������
	Msg2To1Ptr->NoisePower = sqrt(pow(10,((Msg0To2Ptr->NoisePower - SIG_POEWR_MAX_DBM)/10)) * AMPLITUDE_MAX * AMPLITUDE_MAX);

	//�Ƕȸ�ֵ
	Msg2To34567Ptr->TargetAngleTheta = Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetTheta;
	Msg2To34567Ptr->TargetAnglePhi = Msg0To2Ptr->TargetParam.PointTargetParamMsg.TargetPhi;
}

/* ��չĿ��ģ�ͣ�����0���� */
void RangeSpreadTargetParam0Cal(MsgCore0ToCore2 *Msg0To2Ptr, MsgCore2ToCore1 *Msg2To1Ptr,
								MsgCore2ToCore34567 *Msg2To34567Ptr, MsgCore2ToCore0 *Msg2To0Ptr,
								ScatteringPoint *ScatteringPointPtr)
{
	int i;
	//��������ϵ�µ���Ϣ
	Point PointSight[1024];
	for(i = 0 ; i < ScatteringPointPtr->PointNum ; ++i)
	{
		//��Ŀ���������ϵת������������ϵ
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

	//�ó�һά������
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
		PositionTemp += RANGE_PROFILE_NUM/2;	//ʹRANGE_PROFILE_NUM/2Ϊ0λ��
		Msg2To1Ptr->RangeProfile[PositionTemp] += PointSight[i].RCS;
	}

	//��������վ���
	int	R1 = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetDistanceTran;
	int	R2 = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetDistanceRecv;

	//�ù��ʼ������
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

	//��������
	Msg2To1Ptr->NoisePower = sqrt(pow(10,((Msg0To2Ptr->NoisePower - SIG_POEWR_MAX_DBM)/10)) * AMPLITUDE_MAX * AMPLITUDE_MAX);

	//�þ��������ʱ
	Msg2To1Ptr->DistanceDelay = (R1 + R2) / LIGHT_SPEED * FPGA_CLK_FRE + DISTANCE_DELAY_COMPENSATION;
	//���ٶȼ���Ƶ�ʿ�����
	Msg2To1Ptr->DopplerFrePinc = 2 *
								(Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetSpeedTran +
										Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetSpeedRecv)
								* WAVE_FRE / LIGHT_SPEED * 0xffffffff / FPGA_CLK_FRE;

	//�Ƕȸ�ֵ
	Msg2To34567Ptr->TargetAngleTheta = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetTheta;
	Msg2To34567Ptr->TargetAnglePhi = Msg0To2Ptr->TargetParam.RangeSpreadTargetParam0Msg.TargetPhi;

	//�ش�����
	memcpy(	Msg2To0Ptr->TargetParamBack.RangeSpreadTargetParam0SetBackFrame.RangeProfile,
			Msg2To1Ptr->RangeProfile,
			sizeof(Msg2To1Ptr->RangeProfile));
}

/* ��չĿ��ģ�ͣ�����1���� */
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

	/* ���㷢�ͺͽ��վ��� */
	TranR = sqrt(	(GroundCoordTargetX - GroundCoordRadarTranX)*(GroundCoordTargetX - GroundCoordRadarTranX) +
					(GroundCoordTargetY - GroundCoordRadarTranY)*(GroundCoordTargetY - GroundCoordRadarTranY) +
					(GroundCoordTargetZ - GroundCoordRadarTranZ)*(GroundCoordTargetZ - GroundCoordRadarTranZ));

	RecvR = sqrt(	(GroundCoordRadarRecvX - GroundCoordTargetX)*(GroundCoordRadarRecvX - GroundCoordTargetX) +
					(GroundCoordRadarRecvY - GroundCoordTargetY)*(GroundCoordRadarRecvY - GroundCoordTargetY) +
					(GroundCoordRadarRecvZ - GroundCoordTargetZ)*(GroundCoordRadarRecvZ - GroundCoordTargetZ));

	/* �þ��������ʱ */
	Msg2To1Ptr->DistanceDelay =
			((TranR + RecvR) / LIGHT_SPEED * FPGA_CLK_FRE) + DISTANCE_DELAY_COMPENSATION;
	/* ���ٶȼ���Ƶ�ʿ����� */
	Msg2To1Ptr->DopplerFrePinc = 2 *
								(Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.TargetSpeedTran +
										Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.TargetSpeedRecv)
								* WAVE_FRE / LIGHT_SPEED * 0xffffffff / FPGA_CLK_FRE;


	/* ����Ŀ������������ϵ�µķ�λ�͸����� */
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
	//����ó���������ϵ��Ŀ�������
	TargetRadarX -= Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordRadarRecvX;
	TargetRadarY -= Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordRadarRecvY;
	TargetRadarZ -= Msg0To2Ptr->TargetParam.RangeSpreadTargetParam1Msg.GroundCoordRadarRecvZ;
	RadarCoordTheta = atan(TargetRadarZ/TargetRadarX);
	RadarCoordPhi = atan(TargetRadarY / sqrt(TargetRadarX*TargetRadarX + TargetRadarZ*TargetRadarZ));


	/* ������������ϵ��ɢ���λ�� */
	//��������ϵ�µ���Ϣ
	Point*	PointSight = (Point*)malloc(sizeof(Point) * ScatteringPointPtr->PointNum);
	Point*	PointGround = (Point*)malloc(sizeof(Point) * ScatteringPointPtr->PointNum);
	for(i = 0 ; i < ScatteringPointPtr->PointNum ; ++i)
	{
		//ɢ��������Ŀ���������ϵת������������ϵ

		CoordinateCalculateTransToOrigin(
						GroundCoordToTargetCoordAngleX, GroundCoordToTargetCoordAngleY, GroundCoordToTargetCoordAngleZ,
						ScatteringPointPtr->PointData[i].X,
						ScatteringPointPtr->PointData[i].Y,
						ScatteringPointPtr->PointData[i].Z,
						&(PointGround[i].X), &(PointGround[i].Y), &(PointGround[i].Z)
						);
		//ɢ�������ӵ�������ϵת������������ϵ
		Point PointRadar;
		CoordinateCalculateOriginToTrans(
						GroundCoordToRadarCoordAngleX, GroundCoordToRadarCoordAngleY, GroundCoordToRadarCoordAngleZ,
						PointGround[i].X,
						PointGround[i].Y,
						PointGround[i].Z,
						&(PointRadar.X), &(PointRadar.Y), &(PointRadar.Z)
						);
		//ɢ����������������ϵת������������ϵ
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

	/* ������ƫ��ֵ�ͽ�ƫ�� */
	float	LineDeviationY;
	float	LineDeviationZ;
	float	AngleDeviationTheta;
	float	AngleDeviationPhi;
	LineDeviationCal(
					ScatteringPointPtr->PointNum,
					PointSight,		//��������ϵ��ɢ�������
					PointGround,	//��������ϵ��ɢ�������
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


	/* �Ƕȸ�ֵ  */
	Msg2To34567Ptr->TargetAngleTheta = RadarCoordTheta + AngleDeviationTheta;
	Msg2To34567Ptr->TargetAnglePhi = RadarCoordPhi + AngleDeviationPhi;


	/* �ó�һά������ */
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
	//�ù��ʼ������
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

	//��������
	Msg2To1Ptr->NoisePower = sqrt(pow(10,((Msg0To2Ptr->NoisePower - SIG_POEWR_MAX_DBM)/10)) * AMPLITUDE_MAX * AMPLITUDE_MAX);

	//�ش�����
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

/* ��չĿ��ģ�ͣ�����2���� */
void RangeSpreadTargetParam2Cal(MsgCore0ToCore2 *Msg0To2Ptr, MsgCore2ToCore1 *Msg2To1Ptr,
								MsgCore2ToCore34567 *Msg2To34567Ptr, MsgCore2ToCore0 *Msg2To0Ptr,
								ScatteringPoint *ScatteringPointPtr)
{

}



