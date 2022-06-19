#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable: 4996)

int main() {
	srand((unsigned int)time(NULL));
	
	char str1[100][51] = { 0, };						// (1) �Ϲ� �迭
	char* str2[100];									// (2) ���� �Ҵ�
	int size, i, j;

	for (i = 0; i < 100; i++) {
		size = rand() % 21 + 30;						// �� ���� ���ĺ��� ������ ������ ���� (30 ~ 50��)
		str2[i] = malloc(sizeof(char) * (size + 1));	// size��ŭ ���� �Ҵ�
		for (j = 0; j < size; j++) {					// �������� ���ĺ� ���� �� �迭�� ����
			str1[i][j] = rand() % 26 + 'A';
			str2[i][j] = rand() % 26 + 'A';
		}
		str2[i][j] = 0;
	}

	printf("�迭 ���� ���\n");
	printf("���� �� :\n");

	for (i = 0; i < 100; i++)
		printf("%d : %s\n", i + 1, str1[i]);			// ���� �� �迭 ���

	for (i = 0; i < 99; i++)							// ���� �ڵ�
		for (j = i + 1; j < 100; j++)
			if (strcmp(str1[i], str1[j]) > 0) {			// �� ��ȯ
				char temp[51] = { 0, };
				strcpy(temp, str1[i]);
				strcpy(str1[i], str1[j]);
				strcpy(str1[j], temp);
			}

	printf("���� �� :\n");
	for (i = 0; i < 100; i++)
		printf("%d : %s\n", i + 1, str1[i]);

	printf("\n������ ���� ���\n");
	printf("���� �� :\n");

	for (i = 0; i < 100; i++)
		printf("%d : %s\n", i + 1, str2[i]);			// ���� �� �迭 ���

	for (i = 0; i < 99; i++)							// ���� �ڵ�
		for (j = i + 1; j < 100; j++)
			if (strcmp(str2[i], str2[j]) > 0) {			// �ּڰ� ��ȯ
				char* ptr;
				ptr = str2[i];
				str2[i] = str2[j];
				str2[j] = ptr;
			}

	printf("���� �� :\n");
	for (i = 0; i < 100; i++)
		printf("%d : %s\n", i + 1, str2[i]);			// ���� �� �迭 ���
}