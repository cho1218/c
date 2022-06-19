#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable: 4996)

#define MAX_NUM	25
#define ROW		5
#define COL		5

void writeNum(char userB[ROW][COL], char comB[ROW][COL]);
void printBoard(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL]);
int checkBingo(char isOpened[ROW][COL]);
void playGame(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL]);
void userTurn(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL]);
void comTurn(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL]);
char searchNum(char comB[ROW][COL], char isCOpened[ROW][COL]);
void printResult(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL]);

int main() {
	char user[ROW][COL] = { 0, };						// ������� ������
	char userOpen[ROW][COL] = { 0, };					// ������� ������ üũ ����
	char com[ROW][COL] = { 0, };						// ��ǻ���� ������
	char comOpen[ROW][COL] = { 0, };					// ��ǻ���� ������ üũ ����

	srand((unsigned)time(NULL));
	
	writeNum(user, com);								// �������� ������ �Է�
	printBoard(user, com, userOpen, comOpen);			// ù ��° ������ ���
	playGame(user, com, userOpen, comOpen);				// ���� �÷���
	printResult(user, com, userOpen, comOpen);			// ���� ��� ���
}

void writeNum(char userB[ROW][COL], char comB[ROW][COL])
{
	int posR, posC;

	for (int i = 0; i < MAX_NUM; i++)					// ������� ������
	{
		posR = rand() % ROW;
		posC = rand() % COL;

		if (!userB[posR][posC])							// ���� �ش� ĭ�� ��� ������
			userB[posR][posC] = i + 1;					// i �ۼ�
		else
			i--;										// �ƴ϶�� i �����ϰ� �ٽ� �ݺ�
	}

	for (int i = 0; i < MAX_NUM; i++)					// ��ǻ���� ������
	{
		posR = rand() % ROW;
		posC = rand() % COL;

		if (!comB[posR][posC])							// ���� �ش� ĭ�� ��� ������
			comB[posR][posC] = i + 1;					// i �ۼ�
		else
			i--;										// �ƴ϶�� i �����ϰ� �ٽ� �ݺ�
	}
}

void printBoard(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		printf("\n");
		for (int j = 0; j < COL; j++) {
			if (isUOpened[i][j]) 
				printf("	(%d)", userB[i][j]);		// ���� �ִٸ� ��ȣ �ٿ��� ���
			else printf("	%d", userB[i][j]);			// ���� ���� ������ �״�� ���
		}
		printf("		");
		for (int k = 0; k < COL; k++) {
			if (isCOpened[i][k])
				printf("	(%d)", comB[i][k]);			// ���� �ִٸ� ��ȣ �ٿ��� ���
			else printf("	-");						// ���� ���� ������ '-' ���
		}
		printf("\n");
	}
	printf("\n");
	printf("		����� : %d						����� : %d\n\n\n", checkBingo(isUOpened), checkBingo(isCOpened));
}

int checkBingo(char isOpened[ROW][COL])			// ���� ���� üũ
{
	int cnt = 0;								// �� ���� �� ����
	int flag = 0;								// �� ���κ��� ��� ���ȴ��� üũ

	for (int i = 0; i < ROW; i++)				// ���� ����
	{
		for (int j = 0; j < COL; j++)
			flag += isOpened[i][j];				// �ش� ROW�� open�迭 ��� ����
		cnt += (flag == 5) ? 1 : 0;				// ������ 5���, �� ������ �� ���� +1
		flag = 0;
	}

	for (int i = 0; i < COL; i++)				// ���� ����
	{
		for (int j = 0; j < ROW; j++)
			flag += isOpened[j][i];				// �ش� COL�� open�迭 ��� ����
		cnt += (flag == 5) ? 1 : 0;				// ������ 5���, �� ������ �� ���� +1
		flag = 0;
	}

	for (int i = 0; i < ROW; i++)				// ���� �밢�� ����
		flag += isOpened[i][i];					// �밢�� ���� open�迭 ��� ����
	cnt += (flag == 5) ? 1 : 0;					// ������ 5���, �� ������ �� ���� +1
	flag = 0;

	for (int i = 0; i < ROW; i++)				// ������ �밢�� ����
		flag += isOpened[i][(COL-1)-i];			// �밢�� ���� open�迭 ��� ����
	cnt += (flag == 5) ? 1 : 0;					// ������ 5���, �� ������ �� ���� +1
	flag = 0;

	return cnt;									// ���� �� ���� ����
}

void playGame(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL])
{
	while (checkBingo(isUOpened) <= ROW || checkBingo(isCOpened) <= ROW)			// ���� 5�� ���϶�� �ݺ�
	{
		userTurn(userB, comB, isUOpened, isCOpened);								// ����� ����
		printBoard(userB, comB, isUOpened, isCOpened);								// ������ ���

		if (checkBingo(isUOpened) >= ROW || checkBingo(isCOpened) >= ROW) break;	// ���� 5�� �̻��̸� ����

		comTurn(userB, comB, isUOpened, isCOpened);									// ��ǻ�� ����
		printBoard(userB, comB, isUOpened, isCOpened);								// ������ ���

		if (checkBingo(isUOpened) >= ROW || checkBingo(isCOpened) >= ROW) break;	// ���� 5�� �̻��̸� ����
	}
}

void userTurn(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL])
{
	int userChoice;
	int flag = 0;

	while (true)												// �ùٸ� ���� �Է��� ������
	{
		printf("����� �����Դϴ�. �� ���� �����? : ");
		scanf("%d", &userChoice);

		if (userChoice <= 0 || userChoice > 25)
		{
			printf("�߸��� ���� �Է��߽��ϴ�. ���Է��ϼ���. \n\n");
			continue;
		}
		else
		{
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COL; j++)
				{
					if (comB[i][j] == userChoice)				// ����� �Է°��� ��ġ�ϸ�
						isCOpened[i][j] = 1;					// ��ǻ�� open �迭 ������
					if (userB[i][j] == userChoice)
						isUOpened[i][j] = 1;					// ����� open �迭 ������
				}
			}
			break;
		}
	}
}

void comTurn(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL])
{
	int flag = 0;
	char comChoice;

	while (flag != 2) {													// ����ڿ� ��ǻ���� ������ ��ΰ� ������ ��
		flag = 0;
		
		comChoice = searchNum(comB, isCOpened);							// searchNum���� ���� ���� �̾ƿ� ����

		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				if (comB[i][j] == comChoice && !isCOpened[i][j]) {		// ���� ���� �������� ���� ��ġ�ϰ� ���� ���� ���� ��
					isCOpened[i][j] = 1;								// ��ǻ�� open �迭 ����
					flag++;
				}
				if (userB[i][j] == comChoice && !isUOpened[i][j]) {		// ���� ���� �������� ���� ��ġ�ϰ� ���� ���� ���� ��
					isUOpened[i][j] = 1;								// ����� open �迭 ����
					flag++;
				}
			}
		}
	}
	printf("��ǻ���� �����Դϴ�. ");
	Sleep(2000);
	printf("%d�� �����߽��ϴ�. \n\n", comChoice);
}

char searchNum(char comB[ROW][COL], char isCOpened[ROW][COL]) 
{
	int flag = 0;
	char temp = 0;

	if (!isCOpened[2][2])						// ��� ������ ���� ����
		return comB[2][2];
	
	// �밢�� ���� ���� ���� ������ �߿��ϹǷ� ���� üũ��

	for (int i = 0; i < ROW; i++)				// ���� �밢��
	{
		if (!isCOpened[i][i]) 
			temp = comB[i][i];					// ���� ���� ������ �켱 ����
		flag += isCOpened[i][i];				// ���� �밢���� �� �� ���ȴ��� Ȯ��
	}
	if (flag == 4)								// ���� 4���� ���� �ִٸ�
		return temp;							// ���� ���� ���� �� ����
	flag = 0;

	for (int i = 0; i < ROW; i++)				// ������ �밢��
	{
		if (!isCOpened[i][(COL - 1) - i]) 
			temp = comB[i][(COL - 1) - i];		
		flag += isCOpened[i][(COL - 1) - i];	// ������ �밢���� �� �� ���ȴ��� Ȯ��
	}
	if (flag == 4)
		return temp;
	flag = 0;

	for (int i = 0; i < ROW; i++)				// ����
	{
		for (int j = 0; j < COL; j++)
		{
			if (!isCOpened[i][j]) 
				temp = comB[i][j];				// ���� ���� ������ �켱 ����
			flag += isCOpened[i][j];			// �ش� ROW�� �� �� ���ȴ��� Ȯ��
		}
		if (flag == 4)							// ���� 4���� ���� �ִٸ�
			return temp;						// ���� ���� ���� �� ����
		flag = 0;
	}

	for (int i = 0; i < COL; i++)				// ����
	{
		for (int j = 0; j < ROW; j++)
		{
			if (!isCOpened[j][i]) 
				temp = comB[j][i];
			flag += isCOpened[j][i];			// �ش� COL�� �� �� ���ȴ��� Ȯ��
		}
		if (flag == 4)
			return temp;
		flag = 0;
	}

	return (rand() % 25 + 1);					// ��� �ƴ϶�� ���� �� ����
}

void printResult(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL])
{
	printf("\n");

	for (int i = 0; i < ROW; i++)
	{
		printf("\n");
		for (int j = 0; j < COL; j++) {
			if (isUOpened[i][j])
				printf("	(%d)", userB[i][j]);		// ���� �ִٸ� ��ȣ �ٿ��� ���
			else printf("	%d", userB[i][j]);			// ���� ���� ������ �״�� ���
		}
		printf("		");
		for (int k = 0; k < COL; k++) {
			if (isCOpened[i][k])
				printf("	(%d)", comB[i][k]);			// ���� �ִٸ� ��ȣ �ٿ��� ���
			else printf("	%d", comB[i][k]);			// ���� ���� ������ �״�� ���
		}
		printf("\n");
	}
	printf("\n");

	if (checkBingo(isUOpened) >= 5 && checkBingo(isCOpened) >= 5)
		printf("�����ϴ�.\n\n");
	else if (checkBingo(isUOpened) >= 5) 
		printf("����ڰ� �̰���ϴ�.\n\n");
	else if (checkBingo(isCOpened) >= 5)
		printf("��ǻ�Ͱ� �̰���ϴ�.\n\n");
	else
		printf("����!\n");

	printf("\n");
}