#include "stdafx.h"
#include "FBdata.h"

//鸟控制相关组件
Bird_Struct Bird;
double Bird_Velocity = 5;
double Bird_Time = 0;

//墙控制相关组7件
Wall_Struct Wall[Wall_Max_Length];
int Wall_Length = 0;
//墙的运行速度
int Wall_Move_Velocity = 150;

int Length_Node = 10;