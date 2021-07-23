#pragma once

//鸟的数据存储
struct Bird_Struct
{
	RECT current_Bird;
	RECT old_Bird;
};
extern Bird_Struct Bird;
//鸟飞行的重力加速度
#define Gravity 5
//鸟的速度
#define Original_Velocity 5
extern double Bird_Velocity;
//鸟的单个运动状态计时器
extern double Bird_Time;
//鸟的打印计时器
#define Bird_Move_Timer 2020
#define Bird_Move_Timer_Gap 1

//墙的存储结构
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
//墙的打印计时器
#define Wall_Move_Timer 2021
#define Wall_Move_Timer_Gap 50
//墙的运行速度(/s)
//#define Wall_Move_Velocity 150
extern int Wall_Move_Velocity;
//墙间宽度
#define Wall_Wall_Gap 75
//上下墙间高度
#define Wall_Up_Down_Basic_Height 300
//墙宽度
#define Wall_Basic_Weight 125


//游戏窗口属性
#define Screen_Height	550
#define Screen_Weight	1200

extern int Length_Node;