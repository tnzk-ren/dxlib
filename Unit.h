#pragma once
#include "DxLib.h"
#include "global.h"
#include <stack>


class Unit {

public:
	Unit(int _x, int _y, char* img);
	void View();
	void Move(std::stack<Direction> *moveRoute);
	bool MovePoint(int *targetX, int *targetY);
	void setXY(int _x, int _y);
	std::stack<Direction> RouteSetting();
	void MoveByClick();
	void MoveArea();

private:
	int x;
	int y;
	int gHandle;
	int toX;
	int toY;

	int mvArea[16][16];
	int move = 4;
};