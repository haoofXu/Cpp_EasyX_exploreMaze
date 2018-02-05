
#include <stdlib.h>
#include <iostream>  
#include <fstream>  
#include <graphics.h>
#include <conio.h>

using namespace std;

int* readMaze(char maze[100][100]) {
	ifstream in("e:\\maze.txt");
	if (!in) {
		cout << "不能打开输入的文件" << endl;
		return 0;
	}
	int raw = 0;
	int column = 0;
	int flag = 0;
	int length = 0;
	char a;
	a = in.get();
	bool find = false;
	while (a != EOF) {
		if (a == '\n' || a == '\r') {
			if (!find) {
				length = raw;
				find = true;

			}
			raw = 0;
			column++;
			//cout << '1';
		}
		else if (a == '$') {
			maze[raw][column] = a;
			raw++;
			//cout << '2';
		}
		else if (a == '+') {
			maze[raw][column] = a;
			raw++;
			//cout << '3';
		}
		else {
			maze[raw][column] = a;
			raw++;
			//cout << '4';
		}
		//cout << a;
		a = in.get();
	}
	int* size = new int[2];
	size[0] = length;
	size[1] = column;

	return size;
}



int GetDirection()
{
	int ret = 6;

	do
	{
		int ch = _getch();
		cout << ch;
		if (isascii(ch))
			continue;

		ch = _getch();
		cout << ch;
		switch (ch)
		{
		case 81:
			ret = -1;
			break;
		case 72:
			ret = 0; // top
			break;
		case 75:
			ret = 2; // left 
			break;
		case 77:
			ret = 3; // right
			break;
		case 80:
			ret = 1; // down
			break;

		case 82: 
			ret = 4; //Ins
			break;

		case 73:
			/*cout << "B";*/
			ret = 5; //PU
			break;

		default:
			break;
		}
	} while (ret == 6);

	return ret;
}
int main()
{
	IMAGE img, playerp,end;

	loadimage(&img, L"enemy.jpg", 20, 20, true);//先把图片放在工程项目下，使用L+"绝对路径"  
	loadimage(&playerp, L"player.jpg", 20, 20, true);//先把图片放在工程项目下，使用L+"绝对路径"  
	loadimage(&end, L"end.jpg", 20, 20, true);//先把图片放在工程项目下，使用L+"绝对路径"  

	//while (true)
	//{
	//	GetDirection();
	//}

	char maze[100][100] = { '0' };
	int mazeInt[100][100] = { 0 };
	int* col = readMaze(maze);


	initgraph(col[0]*20, col[1]*20);
	setbkcolor(BLACK);
	cleardevice();


	int player[2] = { 0 };
	int enemy[2] = { 0 };
	int exit[2] = { 0 };

	setcolor(BLACK);
	setfillcolor(0x5454);
	for (int i = 0; i < col[1]; i++) {
		for (int j = 0; j < 100; j++) {
			if (maze[j][i] == '#') {
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
			}
			else if (maze[j][i] == '~') {
				setfillcolor(WHITE);

				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
				setfillcolor(0x5454);
			}
			else if (maze[j][i] == '+') {
				player[0] = j;
				player[1] = i;
				int x = j * 20;
				int y = i * 20;
				mazeInt[j][i] = 1;
				putimage(x, y, &playerp);//显示图片  

				/*setfillcolor(GREEN);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
				setfillcolor(0x5454);*/
			}
			else if (maze[j][i] == 'E') {
				enemy[0] = j;
				enemy[1] = i;
				int x = j * 20;
				int y = i * 20 ;
				putimage(x, y, &img);
				/*setfillcolor(YELLOW);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
				setfillcolor(0x5454);*/
			}
			else if (maze[j][i] == '$') {
				exit[0] = j;
				exit[1] = i;

				int x = j * 20;
				int y = i * 20;
				putimage(x, y, &end);
				/*setfillcolor(RED);
				fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
				setfillcolor(0x5454);*/
			}
		}
	}


	while (true)
	{
		bool cantGo = false;
		int dir = GetDirection();
		if (dir == -1) { break; }
		if (dir == 0) {
			if (player[1] >= 1) {
				if (maze[player[0]][player[1] - 1] != '#') {
					maze[player[0]][player[1] - 1] = '+';
					maze[player[0]][player[1]] = '~';
					player[1] --;
					mazeInt[player[0]][player[1]] = 1;
				}
			}
		}
		else if (dir == 1) {
				if (player[1] < col[1]) {
					if (maze[player[0]][player[1] + 1] != '#' ) {
						maze[player[0]][player[1] + 1] = '+';
						maze[player[0]][player[1]] = '~';
						player[1] ++;
						mazeInt[player[0]][player[1]] = 1;
					}
				}
			}
		else if (dir == 2) {
			if (player[0] >= 1) {
				if (maze[player[0] - 1][player[1]] != '#') {
					maze[player[0] - 1][player[1]] = '+';
					maze[player[0]][player[1]] = '~';
					player[0] --;
					mazeInt[player[0]][player[1]] = 1;
				}
			}
		}
		else if (dir == 3) {
			if (player[0] < col[0]) {
				if (maze[player[0]+1][player[1]] != '#') {
					maze[player[0]+1][player[1]] = '+';
					maze[player[0]][player[1]] = '~';
					player[0] ++;
					mazeInt[player[0]][player[1]] = 1;
				}
			}
		}
		else if (dir == 4) {
			while (true)
			{
				int dir = (int)rand() % 4;
				int dir2 = (int)rand() % 4;
				int x = player[0];
				int y = player[1];
				if (dir == 0) {
					if (player[1] >= 1) {
						if (maze[player[0]][player[1] - 1] != '#'
							&& mazeInt[player[0]][player[1] - 1] == 0) {
							maze[player[0]][player[1] - 1] = '+';
							maze[player[0]][player[1]] = '~';
							player[1] --;
						}
						else {
							if (player[0] == x && player[1] == y && maze[player[0]][player[1] - 1] != '#') {
								cantGo = true;
							}
							if (cantGo) {
								if (maze[player[0]][player[1] - 1] != '#') {
									maze[player[0]][player[1] - 1] = '+';
									maze[player[0]][player[1]] = '~';
									player[1] --;
								}
							}
						}
					}
					else {
						continue;
					}
				}
				else if (dir == 1) {
					if (player[1] < col[1]) {
						if (maze[player[0]][player[1] + 1] != '#'
							&& mazeInt[player[0]][player[1] + 1] == 0 ) {
							maze[player[0]][player[1] + 1] = '+';
							maze[player[0]][player[1]] = '~';
							player[1] ++;
						}
						else {
							if (player[0] == x && player[1] == y && maze[player[0]][player[1] + 1] != '#') {
								cantGo = true;
							}
							if (cantGo && maze[player[0]][player[1] + 1] != '#') {
								maze[player[0]][player[1] + 1] = '+';
								maze[player[0]][player[1]] = '~';
								player[1] ++;
							}
						}
					}
					else {
						continue;
					}
				}
				else if (dir == 2) {
					if (player[0] >= 1) {
						if (maze[player[0] - 1][player[1]] != '#'
							&& mazeInt[player[0] - 1][player[1]] == 0) {
							maze[player[0] - 1][player[1]] = '+';
							maze[player[0]][player[1]] = '~';
							player[0] --;
						}
						else {
							if (player[0] == x && player[1] == y && maze[player[0] - 1][player[1]] != '#') {
								cantGo = true;
							}
							if (cantGo && maze[player[0] - 1][player[1]] != '#') {
								maze[player[0] - 1][player[1]] = '+';
								maze[player[0]][player[1]] = '~';
								player[0] --;
							}
						}
					}
					else {
						continue;
					}
				}
				else if (dir == 3) {
					if (player[0] < col[0]) {
						if (maze[player[0] + 1][player[1]] != '#'
							&& mazeInt[player[0] + 1][player[1]] == 0) {
							maze[player[0] + 1][player[1]] = '+';
							maze[player[0]][player[1]] = '~';
							player[0] ++;
						}
						else {
							if (player[0] == x && player[1] == y && maze[player[0] +1][player[1]] != '#') {
								cantGo = true;
							}
							if (cantGo && maze[player[0] + 1][player[1]] != '#') {
								maze[player[0] + 1][player[1]] = '+';
								maze[player[0]][player[1]] = '~';
								player[0] ++;
							}
						}
					}
					else {
						continue;
					}
				}

				mazeInt[player[0]][player[1]] = 1;
				if (dir2 == 0) {
					if (enemy[1] >= 1) {
						if (maze[enemy[0]][enemy[1] - 1] != '#') {
							maze[enemy[0]][enemy[1] - 1] = 'E';
							maze[enemy[0]][enemy[1]] = '~';
							enemy[1] --;
						}
						else {
							continue;
						}
					}
					else {
						continue;
					}
				}
				else if (dir2 == 1) {
					if (enemy[1] < col[1]) {
						if (maze[enemy[0]][enemy[1] + 1] != '#') {
							maze[enemy[0]][enemy[1] + 1] = 'E';
							maze[enemy[0]][enemy[1]] = '~';
							enemy[1] ++;
						}
						else {
							continue;
						}
					}
					else {
						continue;
					}
				}
				else if (dir2 == 2) {
					if (enemy[0] >= 1) {
						if (maze[enemy[0] - 1][enemy[1]] != '#') {
							maze[enemy[0] - 1][enemy[1]] = 'E';
							maze[enemy[0]][enemy[1]] = '~';
							enemy[0] --;
						}
						else {
							continue;
						}
					}
					else {
						continue;
					}
				}
				else if (dir2 == 3) {
					if (enemy[0] < col[0]) {
						if (maze[enemy[0] + 1][enemy[1]] != '#') {
							maze[enemy[0] + 1][enemy[1]] = 'E';
							maze[enemy[0]][enemy[1]] = '~';
							enemy[0] ++;
						}
						else {
							continue;
						}
					}
					else {
						continue;
					}
				}
				cleardevice();
				setcolor(BLACK);
				setfillcolor(0x5454);
				for (int i = 0; i < col[1]; i++) {
					for (int j = 0; j < 100; j++) {
						if (maze[j][i] == '#') {
							fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
						}
						else if (maze[j][i] == '~') {
							setfillcolor(WHITE);

							fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
							setfillcolor(0x5454);
						}
						else if (maze[j][i] == '+') {
							player[0] = j;
							player[1] = i;
							int x = j * 20;
							int y = i * 20;
							putimage(x, y, &playerp);//显示图片  
/*
							setfillcolor(GREEN);
							fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
							setfillcolor(0x5454);*/
						}
						else if (maze[j][i] == 'E') {
							enemy[0] = j;
							enemy[1] = i;
							int x = j * 20;
							int y = i * 20;
							putimage(x, y, &img);
							/*setfillcolor(YELLOW);
							fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
							setfillcolor(0x5454);*/
						}
						else if (maze[j][i] == '$') {
							exit[0] = j;
							exit[1] = i;
							int x = j * 20;
							int y = i * 20;
							putimage(x, y, &end);
/*
							setfillcolor(RED);
							fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
							setfillcolor(0x5454);*/
						}
					}
				}
				Sleep(500);
			}
		}
		else if(dir==5)
		{
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					if (maze[j][i] == '+') {
						if (mazeInt[j - 1][i] == 1) {
							maze[player[0] - 1][player[1]] = '+';
							maze[player[0]][player[1]] = '~';
							player[0] --;
						}
						else if (mazeInt[j + 1][i] == 1) {
							maze[player[0] + 1][player[1]] = '+';
							maze[player[0]][player[1]] = '~';
							player[0] ++;
						}
						else if (mazeInt[j][i - 1] == 1) {
							maze[player[0]][player[1] - 1] = '+';
							maze[player[0]][player[1]] = '~';
							player[1] --;
						}
						else if (mazeInt[j][i + 1] == 1) {
							maze[player[0]][player[1] + 1] = '+';
							maze[player[0]][player[1]] = '~';
							player[1] ++;
						}
						mazeInt[j][i] = 0;
					}
				}
			}
		}
		cleardevice();
		setcolor(BLACK);
		setfillcolor(0x5454);
		for (int i = 0; i < col[1]; i++) {
			for (int j = 0; j < 100; j++) {
				if (maze[j][i] == '#') {
					fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
				}
				else if (maze[j][i] == '~') {
					setfillcolor(WHITE);

					fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
					setfillcolor(0x5454);
				}
				else if (maze[j][i] == '+') {
					player[0] = j;
					player[1] = i;

					int x = j * 20;
					int y = i * 20;
					putimage(x, y, &playerp);//显示图片  
					/*setfillcolor(GREEN);
					fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
					setfillcolor(0x5454);*/
				}
				else if (maze[j][i] == 'E') {
					enemy[0] = j;
					enemy[1] = i;
					int x = j * 20;
					int y = i * 20;
					putimage(x, y, &img);//显示图片  
					/*setfillcolor(YELLOW);
					fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
					setfillcolor(0x5454);*/
				}
				else if (maze[j][i] == '$') {
					exit[0] = j;
					exit[1] = i;

					int x = j * 20;
					int y = i * 20;
					putimage(x, y, &end);
	/*				setfillcolor(RED);
					fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
					setfillcolor(0x5454);*/
				}
			}
		}
		if (player[0] == exit[0] && player[1] == exit[1]) {

			for (int i = 0; i < col[1]; i++) {
				for (int j = 0; j < 100; j++) {
					if (mazeInt[j][i] == 1) {
						setfillcolor(YELLOW);
						fillrectangle(j * 20, i * 20, (j + 1) * 20, (i + 1) * 20);
						setfillcolor(0x5454);
					}
				}
			}
		}
	}


	_getch();
	closegraph();
}