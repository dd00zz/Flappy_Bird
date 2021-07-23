#include "stdafx.h"
#include "FBfunc.h"
#include "FBdata.h"

bool Bird_Wall_Crack() {
	int position = -1;
	for (int i = 0; i < Wall_Length; i++)
		if (Wall[i].current_Wall_up.left <= (Bird.current_Bird.left + Bird.current_Bird.right) / 2
			&& Wall[i].current_Wall_up.right >= (Bird.current_Bird.left + Bird.current_Bird.right) / 2) {
			position = i;
			break;
		}
	if (Bird.current_Bird.top < 0 || Bird.current_Bird.bottom> Screen_Height)
		return true;
	if (position != -1)
		if (Bird.current_Bird.top <= Wall[position].current_Wall_up.bottom
			|| Bird.current_Bird.bottom >= Wall[position].current_Wall_down.top)
			return true;
	return false;
}

void Move_Bird() {
	Bird_Velocity = Bird_Velocity + Gravity * (Bird_Time / 500);

	Bird.old_Bird.bottom = Bird.current_Bird.bottom;
	Bird.old_Bird.top = Bird.current_Bird.top;

	Bird.current_Bird.bottom = Bird.current_Bird.bottom + Bird_Velocity;
	Bird.current_Bird.top = Bird.current_Bird.top + Bird_Velocity;
}
void Bird_Print(HDC hdc) {
	HBRUSH hbrush;
	//»æÖÆÄñ
	hbrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, hbrush);
	Rectangle(hdc, Bird.old_Bird.left, Bird.old_Bird.top, Bird.old_Bird.right, Bird.old_Bird.bottom);
	HPEN hpen = CreatePen(BS_SOLID, 1, RGB(255, 255, 255));
	SelectObject(hdc, hpen);
	Rectangle(hdc, Bird.old_Bird.left, Bird.old_Bird.top, Bird.old_Bird.right, Bird.old_Bird.bottom);
	DeleteObject(hpen);

	hbrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, hbrush);
	Rectangle(hdc, Bird.current_Bird.left, Bird.current_Bird.top, Bird.current_Bird.right, Bird.current_Bird.bottom);
	DeleteObject(hbrush);
}

void Creat_Wall() {
	RECT Gap;
	int Gap_Height = 0;
	int Gap_weight = 0;
	Gap_Height = rand() % 101 + Wall_Up_Down_Basic_Height;
	Gap_weight = rand() % 51 + (Wall_Basic_Weight - 20);

	Gap.top = rand() % (Gap_Height * 1 / 3 + 1) + ((Screen_Height) / 2 - Gap_Height / 2);
	Gap.bottom = rand() % (Gap_Height / 2 + 1) + (Screen_Height) / 2;

	Wall[Wall_Length].current_Wall_up.top = 0;
	Wall[Wall_Length].current_Wall_up.bottom = Gap.top;
	Wall[Wall_Length].current_Wall_down.top = Gap.bottom;
	Wall[Wall_Length].current_Wall_down.bottom = Screen_Height;

	Wall[Wall_Length].current_Wall_up.left = Screen_Weight;
	Wall[Wall_Length].current_Wall_up.right = Screen_Weight + Gap_weight;
	Wall[Wall_Length].current_Wall_down.left = Screen_Weight;
	Wall[Wall_Length].current_Wall_down.right = Screen_Weight + Gap_weight;

	Wall_Length++;
}
void Move_Wall() {
	for (int i = 0; i < Wall_Length; i++) {
		Wall[i].old_Wall_down.bottom = Wall[i].current_Wall_down.bottom;
		Wall[i].old_Wall_down.top = Wall[i].current_Wall_down.top;
		Wall[i].old_Wall_down.left = Wall[i].current_Wall_down.left;
		Wall[i].old_Wall_down.right = Wall[i].current_Wall_down.right;

		Wall[i].old_Wall_up.bottom = Wall[i].current_Wall_up.bottom;
		Wall[i].old_Wall_up.top = Wall[i].current_Wall_up.top;
		Wall[i].old_Wall_up.left = Wall[i].current_Wall_up.left;
		Wall[i].old_Wall_up.right = Wall[i].current_Wall_up.right;

		Wall[i].current_Wall_up.left -= Wall_Move_Velocity / Wall_Move_Timer_Gap;
		Wall[i].current_Wall_up.right -= Wall_Move_Velocity / Wall_Move_Timer_Gap;

		Wall[i].current_Wall_down.left -= Wall_Move_Velocity / Wall_Move_Timer_Gap;
		Wall[i].current_Wall_down.right -= Wall_Move_Velocity / Wall_Move_Timer_Gap;
	}

	int distance = rand() % Wall_Wall_Gap * 2 + Wall_Wall_Gap * 4;
	if (Screen_Weight - Wall[Wall_Length - 1].current_Wall_down.left >= distance)
		if (Wall_Length <= Wall_Max_Length)
			Creat_Wall();
}
void Wall_Print(HDC hdc) {
	for (int i = 0; i < Wall_Length; i++) {
		HBRUSH hbrush;
		hbrush = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, hbrush);
		Rectangle(hdc, Wall[i].current_Wall_up.right, Wall[i].old_Wall_up.top, Wall[i].current_Wall_up.right + Wall_Move_Velocity / Wall_Move_Timer_Gap, Wall[i].old_Wall_up.bottom);
		Rectangle(hdc, Wall[i].current_Wall_down.right, Wall[i].old_Wall_down.top, Wall[i].current_Wall_down.right + Wall_Move_Velocity / Wall_Move_Timer_Gap, Wall[i].old_Wall_down.bottom);
		DeleteObject(hbrush);
		HPEN hpen = CreatePen(BS_SOLID, 1, RGB(255, 255, 255));
		SelectObject(hdc, hpen);
		Rectangle(hdc, Wall[i].current_Wall_up.right, Wall[i].old_Wall_up.top, Wall[i].current_Wall_up.right + Wall_Move_Velocity / Wall_Move_Timer_Gap, Wall[i].old_Wall_up.bottom);
		Rectangle(hdc, Wall[i].current_Wall_down.right, Wall[i].old_Wall_down.top, Wall[i].current_Wall_down.right + Wall_Move_Velocity / Wall_Move_Timer_Gap, Wall[i].old_Wall_down.bottom);
		DeleteObject(hpen);

		hbrush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, hbrush);
		Rectangle(hdc, Wall[i].current_Wall_up.left, Wall[i].current_Wall_up.top, Wall[i].current_Wall_up.right, Wall[i].current_Wall_up.bottom);
		Rectangle(hdc, Wall[i].current_Wall_down.left, Wall[i].current_Wall_down.top, Wall[i].current_Wall_down.right, Wall[i].current_Wall_down.bottom);

		DeleteObject(hbrush);
	}
}