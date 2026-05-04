#pragma once
#include<cstdlib>
#include<ctime>
class Cube{
public:
	int face[6][3][3];
	Cube() {
		for (int f = 0;f < 6;f++) {
			for (int i = 0;i < 3;i++) {
				for (int j = 0;j < 3;j++) {
					face[f][i][j] = f;
				}
			}
		}
	}
	void rotateFaceCW(int f) {
		int tmp[3][3];

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				tmp[j][2 - i] = face[f][i][j];

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				face[f][i][j] = tmp[i][j];
	}
	void moveU() {
		// 上面旋转
		rotateFaceCW(0);

		// 四个面交换
		int tmp[3];

		// 保存前面
		for (int i = 0; i < 3; i++)
			tmp[i] = face[2][0][i];

		for (int i = 0; i < 3; i++)
			face[2][0][i] = face[1][0][i];

		for (int i = 0; i < 3; i++)
			face[1][0][i] = face[4][0][i];

		for (int i = 0; i < 3; i++)
			face[4][0][i] = face[3][0][i];

		for (int i = 0; i < 3; i++)
			face[3][0][i] = tmp[i];
	}
	void moveR() {
		// 右面顺时针
		rotateFaceCW(1);

		int tmp[3];

		// 保存上面的右列
		for (int i = 0; i < 3; i++)
			tmp[i] = face[0][i][2];

		for (int i = 0; i < 3; i++)
			face[0][i][2] = face[2][i][2];

		for (int i = 0; i < 3; i++)
			face[2][i][2] = face[5][i][2];

		for (int i = 0; i < 3; i++)
			face[5][i][2] = face[4][2 - i][0];

		for (int i = 0; i < 3; i++)
			face[4][2 - i][0] = tmp[i];
	}
	void moveF() {
		// 前面顺时针
		rotateFaceCW(2);

		int tmp[3];

		// 保存上面的底行
		for (int i = 0; i < 3; i++)
			tmp[i] = face[0][2][i];

		for (int i = 0; i < 3; i++)
			face[0][2][i] = face[3][2 - i][2];

		for (int i = 0; i < 3; i++)
			face[3][i][2] = face[5][0][i];

		for (int i = 0; i < 3; i++)
			face[5][0][i] = face[1][2 - i][0];

		for (int i = 0; i < 3; i++)
			face[1][i][0] = tmp[i];
	}
	void moveL() {

		rotateFaceCW(3);

		int tmp[3];

		for (int i = 0; i < 3; i++)
			tmp[i] = face[0][i][0];

		for (int i = 0; i < 3; i++)
			face[0][i][0] = face[4][2 - i][2];

		for (int i = 0; i < 3; i++)
			face[4][2 - i][2] = face[5][i][0];

		for (int i = 0; i < 3; i++)
			face[5][i][0] = face[2][i][0];

		for (int i = 0; i < 3; i++)
			face[2][i][0] = tmp[i];
	}
	void moveD() {

		rotateFaceCW(5);

		int tmp[3];

		for (int i = 0; i < 3; i++)
			tmp[i] = face[2][2][i];

		for (int i = 0; i < 3; i++)
			face[2][2][i] = face[3][2][i];

		for (int i = 0; i < 3; i++)
			face[3][2][i] = face[4][2][i];

		for (int i = 0; i < 3; i++)
			face[4][2][i] = face[1][2][i];

		for (int i = 0; i < 3; i++)
			face[1][2][i] = tmp[i];
	}
	void moveB() {

		rotateFaceCW(4);

		int tmp[3];

		for (int i = 0; i < 3; i++)
			tmp[i] = face[0][0][i];

		for (int i = 0; i < 3; i++)
			face[0][0][i] = face[1][i][2];

		for (int i = 0; i < 3; i++)
			face[1][i][2] = face[5][2][2-i];

		for (int i = 0; i < 3; i++)
			face[5][2][i] = face[3][i][0];

		for (int i = 0; i < 3; i++)
			face[3][i][0] = tmp[2-i];
	}
	void scramble(int steps = 20) {
		static bool inited = false;
		if (!inited) {
			srand(time(nullptr));
			inited = true;
		}
		for (int i = 0;i < steps;i++) {
			int r = rand() % 6;
			switch (r) {
			case 0:moveU();break;
			case 1:moveR();break;
			case 2:moveF();break;
			case 3:moveL();break;
			case 4:moveD();break;
			case 5:moveB();break;
			}
		}
	}
};

