#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <Windows.h>

int main() {
	FILE* fp;
	int hour, min, sec;
	int t_hour, t_min, t_sec;								// �����ڸ� �ð�
	int u_hour, u_min, u_sec;								// �����ڸ� �ð�
	time_t current;
	struct tm* d;

	fp = fopen("number.BMP", "rb");							// 12byte(96��) * 10
	char data[10][12], ch;

	fseek(fp, 62, SEEK_SET);								// ������� �ǳʶٱ�
	for (int i = 0; i < 10; i++)
	{
		fread(data[9 - i], 12, 1, fp);						// �Ųٷ� ����
	}

	char curtime[10][8];									// ���� �ð��� ������ char �迭

	while (1)
	{
		current = time(NULL);
		d = localtime(&current);
		hour = d->tm_hour;
		min = d->tm_min;
		sec = d->tm_sec;

		t_hour = (hour / 10) == 0 ? 10 : (hour / 10);		// ���� �����ڸ� ���� ����(�ε��� ����)
		t_min = (min / 10) == 0 ? 10 : (min / 10);			// ���� �����ڸ� ���� ����
		t_sec = (sec / 10) == 0 ? 10 : (sec / 10);			// ���� �����ڸ� ���� ����
		
		u_hour = (hour % 10) == 0 ? 10 : (hour % 10);		// ���� �����ڸ� ���� ����(�ε��� ����)
		u_min = (min % 10) == 0 ? 10 : (min % 10);			// ���� �����ڸ� ���� ����
		u_sec = (sec % 10) == 0 ? 10 : (sec % 10);			// ���� �����ڸ� ���� ����

		//printf("%02d:%02d:%02d\n", hour, min, sec);

		for (int i = 0; i < 10; i++)						// ���� �ð��� �ش��ϴ� ���� curtime�� ����
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
				ch = curtime[i][j];							// �ٴ����� ǥ��
				for (int k = 0; k < 8; k++)
				{
					if (ch & (1 << (7 - k))) printf(" ");	// 1�̸� ���
					else printf("@");						// 0�̸� ������
				}
			}
			printf("\n");
		}
		Sleep(200);
		system("cls");
	}
}