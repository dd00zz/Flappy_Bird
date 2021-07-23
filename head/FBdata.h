#pragma once

//������ݴ洢
struct Bird_Struct
{
	RECT current_Bird;
	RECT old_Bird;
};
extern Bird_Struct Bird;
//����е��������ٶ�
#define Gravity 5
//����ٶ�
#define Original_Velocity 5
extern double Bird_Velocity;
//��ĵ����˶�״̬��ʱ��
extern double Bird_Time;
//��Ĵ�ӡ��ʱ��
#define Bird_Move_Timer 2020
#define Bird_Move_Timer_Gap 1

//ǽ�Ĵ洢�ṹ
#define Wall_Max_Length 2000
struct Wall_Struct
{
	RECT current_Wall_up;
	RECT current_Wall_down;

	RECT old_Wall_up;
	RECT old_Wall_down;
};
extern Wall_Struct Wall[Wall_Max_Length];
extern int Wall_Length;
//ǽ�Ĵ�ӡ��ʱ��
#define Wall_Move_Timer 2021
#define Wall_Move_Timer_Gap 50
//ǽ�������ٶ�(/s)
//#define Wall_Move_Velocity 150
extern int Wall_Move_Velocity;
//ǽ����
#define Wall_Wall_Gap 75
//����ǽ��߶�
#define Wall_Up_Down_Basic_Height 300
//ǽ���
#define Wall_Basic_Weight 125


//��Ϸ��������
#define Screen_Height	550
#define Screen_Weight	1200

extern int Length_Node;