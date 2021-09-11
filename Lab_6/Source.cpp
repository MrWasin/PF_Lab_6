#include<stdio.h>
#include<windows.h>
#include<conio.h>

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 4);
	printf("<-0->");
}

void erase_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf("     ");
}

void draw_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 0);
	printf("^");
}

void erase_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}


int main()
{
	setcursor(0);
	char ch = ' ';
	int x = 38, y = 20;
	char direction{};
	int bullets[5] = { 0,0,0,0,0 };
	int shotsX[5], shotsY[5];
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x > 0) { direction = 'L'; }
			if (ch == 'd' && x < 75) { direction = 'R'; }
			if (ch == 's') { direction = 'S'; }
			if (ch == ' ') {
				for (int i = 0; i < 5; i++) {
					if (bullets[i] == 0) {
						bullets[i] = 1;
						shotsX[i] = x + 2;
						shotsY[i] = y;
						break;
					}
				}
			}
			fflush(stdin);
		}

		if (direction == 'L' && x > 0) { erase_ship(x, y); draw_ship(--x, y); }
		if (direction == 'R' && x < 75) { erase_ship(x, y); draw_ship(++x, y); }
		if (direction == 'S') { erase_ship(x, y); draw_ship(x, y); }
		for (int i = 0; i < 5; i++) {
			if (bullets[i] == 1) {
				if (shotsY[i] < 20) {
					erase_bullet(shotsX[i], shotsY[i]);
				}
				if (shotsY[i] > 0) {
					draw_bullet(shotsX[i], --shotsY[i]);
				}
				else {
					bullets[i] = 0;
				}
			}
		}

		Sleep(100);
	} while (ch != 'x');

	return 0;
}