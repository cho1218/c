#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#pragma warning(disable:4996)

void playGame(int* score);
char* makeWord();
void printWrong(char com[71], char user[71]);

int main(void) {
	srand((unsigned)time(NULL));
	int cnt = 0;					// �� 10�� �ݺ�
	int score = 0;					// ���� ����

	printf("������ �����մϴ�.\n");

	while (cnt++ < 10) {
		printf("(%d/10) ", cnt);
		playGame(&score);
	}

	printf("����� ������ %d�� �Դϴ�.\n", score);
}

void playGame(int* score) 
{
	char std[71] = { 0, };				// ���� ���ڿ�
	char input[71] = { 0, };			// ����� �Է� ���ڿ�
	int speed = 0;						// Ÿ�� �ӵ�
	int length = rand() % 21 + 50;		// ���� ����(50-70�� ����)

	printf("������ �Է��ϼ���\n");

	while (strlen(std) < length && strlen(std) + 6 < 70) {
		strcat(std, makeWord());		// ���� ���ڿ� ����
	}

	std[strlen(std) - 1] = 0;			// ������ space ����

	printf("= %s\n", std);
	printf("= ");

	int t = clock();					// ���� �ð�
	fgets(input, 70, stdin);
	t = (clock() - t) / 1000;			// ���� �ð� - ���� �ð�

	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = 0;	// �ٹٲ� ����

	speed = strlen(std) / t * 60;

	if (strcmp(std, input) == 0) {
		printf("�¾ҽ��ϴ�. (%d�� ȹ�� %dŸ/��)\n", (20 - t) * 1000, speed);
		*score += (20 - t) * 1000;		// score�� ���� �߰�
	}
	else
	{
		printWrong(std, input);			// Ʋ�� ���� ã���ֱ�
		printf("Ʋ�Ƚ��ϴ�. (%dŸ/��)\n", speed);
	}
}

char* makeWord()
{
	char result[7] = { 0, };			// �ִ� 7����(�ִ� 5���� + space + '\0')
	int cnt = rand() % 2 + 4;			// �ܾ� �� ����
	int i;

	for (i = 0; i < cnt; i++)
		result[i] = rand() % 26 + 65;	// A-Z���� �������� �� ����
	result[i] = 32;						// �������� space ����

	return result;
}

void printWrong(char com[71], char user[71])
{
	char* comP = com;				// ���� ���ڿ��� ������
	char* userP = user;				// ����� ���ڿ��� ������ 

	printf("  ");

	while (*userP) {
		if (*comP == *userP)		// �� ���ڿ��� �ش� �ּ��� ���� ���ٸ�
			printf(" ");
		else
			printf("^");
		comP++;
		userP++;
	}
	printf("\n");
}