#include "Unit.h"
#include "global.h"

//移動時の障害物情報
int map_mvLayer[16][16]{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,100,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,100,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};



Unit::Unit(int _x, int _y, char* img) {
	x = _x;
	y = _y;
	toX = x * 32;
	toY = y * 32;
	gHandle = LoadGraph(img);
}

//ユニットを表示
void Unit::View() {
	DrawExtendGraph(x * 32, y * 32, (x + 1) * 32, (y + 1) * 32, gHandle, true);
}

//クリックした場所に移動
void Unit::MoveByClick()
{
	bool isMouseInput = MovePoint(&toX, &toY);
	static std::stack<Direction> moveRoute;
	
	if (mvArea[toX / 32][toY / 32] < 0) return;
	if (isMouseInput == true) {
		moveRoute = RouteSetting();
	}
	Move(&moveRoute);

}

//移動ルートをセッティング
std::stack<Direction> Unit::RouteSetting()
{
	
	std::stack<Direction> moveRoute;

	

	int tempX = toX / 32;
	int tempY = toY / 32;
	while (mvArea[tempX][tempY] != move) {
		if (tempX - 1 >= 0 && mvArea[tempX - 1][tempY] == mvArea[tempX][tempY] + 1) {
			tempX--;
			moveRoute.push(RIGHT);
		}
		else if (tempX + 1 < 16 && mvArea[tempX + 1][tempY] == mvArea[tempX][tempY] + 1) {
			tempX++;
			moveRoute.push(LEFT);
		}
		else if (tempY - 1 >= 0 && mvArea[tempX][tempY - 1] == mvArea[tempX][tempY] + 1) {
			tempY--;
			moveRoute.push(DOWN);
		}
		else if (tempY + 1 < 16 && mvArea[tempX][tempY + 1] == mvArea[tempX][tempY] + 1) {
			tempY++;
			moveRoute.push(UP);
		}
	}
	return moveRoute;
	
}

//ルートに従って移動
void Unit::Move(std::stack<Direction> *moveRoute) {
	
	if (moveRoute->empty() == false) {
		if (moveRoute->top() == LEFT) {
			x--;
		}
		else if (moveRoute->top() == RIGHT) {
			x++;
		}
		else if (moveRoute->top() == UP) {
			y--;
		}
		else if (moveRoute->top() == DOWN) {
			y++;
		}
		moveRoute->pop();
	}

}

//クリックした場所を移動先に指定
bool Unit::MovePoint(int *targetX, int *targetY) {
	if (GetMouseInputRelease() != 0) {
		GetMousePoint(targetX, targetY);
		return true;
	}
	return false;

}

void Unit::setXY(int _x, int _y) {
	x = _x;
	y = _y;
}

//移動範囲を調べる再帰関数
void MoveAreaDeep(int mvArea[16][16], int move, int x, int y)
{
	move -= map_mvLayer[x][y];
	if (x < 0 || y < 0 || x > 15 || y > 15 || mvArea[x][y] >= move ) return;

	mvArea[x][y] = move;
	if (move > 0) {
		MoveAreaDeep(mvArea, move - 1, x - 1, y);
		MoveAreaDeep(mvArea, move - 1, x + 1, y);
		MoveAreaDeep(mvArea, move - 1, x, y + 1);
		MoveAreaDeep(mvArea, move - 1, x, y - 1);
	}
	
	
}

//移動範囲表示
void Unit::MoveArea() {
	static int swch= -1;
	
	if (swch == -1 && x == toX / 32 && y == toY / 32 ) {
		for (int j = 0; j < 16; j++) {
			for (int i = 0; i < 16; i++) {
				mvArea[i][j] = -1;
			}
		}
		MoveAreaDeep(mvArea, move, x, y);
	
		swch = 1;
	}
	if (x != toX / 32 || y != toY / 32) {
		swch = -1;
	}
	if (swch == 1) {
		for (int j = 0; j < 16; j++) {
			for (int i = 0; i < 16; i++) {
				if (mvArea[i][j] >= 0) {
					DrawBox(i * 32, j * 32, (i + 1) * 32, (j + 1) * 32, GetColor(255, 0, 0), false);
				}
			}
		}
	}
}