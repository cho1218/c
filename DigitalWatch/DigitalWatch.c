#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <Windows.h>

int main() {
	FILE* fp;
	int hour, min, sec;
	int t_hour, t_min, t_sec;								// 십의자리 시간
	int u_hour, u_min, u_sec;								// 일의자리 시간
	time_t current;
	struct tm* d;

	fp = fopen("number.BMP", "rb");							// 12byte(96개) * 10
	char data[10][12], ch;

	fseek(fp, 62, SEEK_SET);								// 헤더정보 건너뛰기
	for (int i = 0; i < 10; i++)
	{
		fread(data[9 - i], 12, 1, fp);						// 거꾸로 저장
	}

	char curtime[10][8];									// 현재 시간을 저장할 char 배열

	while (1)
	{
		current = time(NULL);
		d = localtime(&current);
		hour = d->tm_hour;
		min = d->tm_min;
		sec = d->tm_sec;

		t_hour = (hour / 10) == 0 ? 10 : (hour / 10);		// 시의 십의자리 숫자 저장(인덱스 역할)
		t_min = (min / 10) == 0 ? 10 : (min / 10);			// 분의 십의자리 숫자 저장
		t_sec = (sec / 10) == 0 ? 10 : (sec / 10);			// 초의 십의자리 숫자 저장
		
		u_hour = (hour % 10) == 0 ? 10 : (hour % 10);		// 시의 일의자리 숫자 저장(인덱스 역할)
		u_min = (min % 10) == 0 ? 10 : (min % 10);			// 분의 일의자리 숫자 저장
		u_sec = (sec % 10) == 0 ? 10 : (sec % 10);			// 초의 일의자리 숫자 저장

		//printf("%02d:%02d:%02d\n", hour, min, sec);

		for (int i = 0; i < 10; i++)						// 현재 시간에 해당하는 숫자 curtime에 저장
		{
			curtime[i][0] = data[i][t_hour - 1];
			curtime[i][1] = data[i][u_hour - 1];
			curtime[i][2] = data[i][10];
			curtime[i][3] = data[i][t_min - 1];
			curtime[i][4] = data[i][u_min - 1];
			curtime[i][5] = data[i][10];
			curtime[i][6] = data[i][t_sec - 1];
			curtime[i][7] = data[i][u_sec - 1];
			printf("\n");
		}
		
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				ch = curtime[i][j];							// 줄단위로 표시
				for (int k = 0; k < 8; k++)
				{
					if (ch & (1 << (7 - k))) printf(" ");	// 1이면 흰색
					else printf("@");						// 0이면 검정색
				}
			}
			printf("\n");
		}
		Sleep(200);
		system("cls");
	}
}
