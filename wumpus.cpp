#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <stack>
#include <ctime>
#include <string>
using namespace std;

string map[6][6] = { //�ʱ� �׸���
	{"*","*","*","*","*","*"},
	{"*","","","","","*"},
	{"*","","","","","*"},
	{"*","","","","","*"},
	{"*","","","","","*"},
	{"*","*","*","*","*","*"}
};
int Gx, Gy; //�� ��ġ
int nx, ny; //���� ��ġ
int nd; // 1-�� 2-�� 3-�� 4-��
int getg = 0;
int dx[4] = { -1,1,0,0 }; //��:N ��:S ��:W ��:E
int dy[4] = { 0,0,-1,1 };
int infoW[6][6];
int infoP[6][6];

stack <pair<int, int>> s;

void PrintMap(int x, int y) {
	system("pause");
	system("cls");
	cout << "���� ��ġ :" << x << "," << y << "���� ���� : " << nd << "\n";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (i == x && j == y) cout << "N\t";
			else cout << map[i][j] << "\t";
		}
		cout << "\n\n";
	}
}

void SetWumpus() { //������ ����
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			if (map[i][j] != "" || (i == 4 && j == 1)) continue;
			int percent = rand() % 100;
			if (0 <= percent && percent <= 9) {
				map[i][j] = 'W';
				for (int k = 0; k < 4; k++) {
					if ((i + dx[k]) >= 1 && (i + dx[k]) <= 4 && (j + dy[k]) >= 1 && (j + dy[k]) <= 4) {
						if (map[i + dx[k]][j + dy[k]].find("S") == map[i + dx[k]][j + dy[k]].npos) {
							map[i + dx[k]][j + dy[k]] += "S";
							infoW[i + dx[k]][j + dy[k]] = 1;
						}
					}
				}
			}

		}
	}
}

void SetPitch() { //������ ����
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			if (map[i][j] != "" || (i == 4 && j == 1)) continue;
			int percent = rand() % 100;
			if (0 <= percent && percent <= 9) {
				map[i][j] = 'P';
				for (int k = 0; k < 4; k++) {
					if ((i + dx[k]) >= 1 && (i + dx[k]) <= 4 && (j + dy[k]) >= 1 && (j + dy[k]) <= 4) {
						if (map[i + dx[k]][j + dy[k]].find("B") == map[i + dx[k]][j + dy[k]].npos) {
							map[i + dx[k]][j + dy[k]] += "B";
							infoP[i + dx[k]][j + dy[k]] = 1;
						}
					}
				}
			}

		}
	}
}


void SetGold() { //�� ����
	int x, y;
	while (1) {
		x = rand() % 4 + 1;
		y = rand() % 4 + 1;
		if ((x == 4 && y == 1)) continue;
		else {
			map[x][y] = 'G';
			Gx = x;
			Gy = y;
			break;
		}
	}
}

void TurnLeft() {
	if (nd == 1) {
		nd = 4;
	}
	else if (nd == 2) {
		nd = 3;
	}
	else if (nd == 3) {
		nd = 1;
	}
	else if (nd == 4) {
		nd = 2;
	}
}

void TurnRight() {
	if (nd == 1) {
		nd = 3;
	}
	else if (nd == 2) {
		nd = 4;
	}
	else if (nd == 3) {
		nd = 2;
	}
	else if (nd == 4) {
		nd = 1;
	}
}

void GoForward() {
	if (infoW[nx][ny] == 1 || infoP[nx][ny] == 1) {
		TurnLeft();
	}
	if (nd == 1) {
		ny++;
		if (ny > 4) {
			ny--;
			TurnLeft();
		}
	}
	else if (nd == 2) {
		ny--;
		if (ny < 1) {
			ny++;
			TurnLeft();
		}
	}
	else if (nd == 3) {
		nx++;
		if (nx > 4) {
			nx--;
			TurnLeft();
		}
	}
	else if (nd == 4) {
		nx--;
		if (nx < 1) {
			nx++;
			TurnLeft();
		}
	}
	PrintMap(nx, ny);
}

int main() {
	srand((unsigned int)time(NULL));
	nx = 4;
	ny = 1;
	nd = 1;
	SetGold();
	SetWumpus();
	SetPitch();
	PrintMap(nx, ny);
	s.push({ 4,1 });
	while (!getg) {
		PrintMap(nx, ny);
		GoForward();
		if (map[nx][ny] == "P") {
			cout << "�����̿� �׾����ϴ�\n";
			nx = 4;
			ny = 1;
			nd = 1;
			while (!s.empty()) {
				s.pop();
			}
			s.push({ 4,1 });
			continue;
		}
		if (map[nx][ny] == "W") {
			cout << "�������� �׾����ϴ�\n";
			nx = 4;
			ny = 1;
			nd = 1;
			while (!s.empty()) {
				s.pop();
			}
			s.push({ 4,1 });
			continue;
		}
		s.push({ nx,ny });
		if (nx == Gx && ny == Gy) {
			getg = 1;
			map[Gx][Gy] = ' ';
			cout << "���� ȹ���߽��ϴ�!\n";
			break;
		}

	}
	while (!s.empty()) {
		PrintMap(s.top().first, s.top().second);
		s.pop();
	}
	cout << "Ž�� ����";
}