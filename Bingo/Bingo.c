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
	char user[ROW][COL] = { 0, };						// 사용자의 빙고판
	char userOpen[ROW][COL] = { 0, };					// 사용자의 빙고판 체크 여부
	char com[ROW][COL] = { 0, };						// 컴퓨터의 빙고판
	char comOpen[ROW][COL] = { 0, };					// 컴퓨터의 빙고판 체크 여부

	srand((unsigned)time(NULL));
	
	writeNum(user, com);								// 랜덤으로 빙고판 입력
	printBoard(user, com, userOpen, comOpen);			// 첫 번째 빙고판 출력
	playGame(user, com, userOpen, comOpen);				// 게임 플레이
	printResult(user, com, userOpen, comOpen);			// 최종 결과 출력
}

void writeNum(char userB[ROW][COL], char comB[ROW][COL])
{
	int posR, posC;

	for (int i = 0; i < MAX_NUM; i++)					// 사용자의 빙고판
	{
		posR = rand() % ROW;
		posC = rand() % COL;

		if (!userB[posR][posC])							// 만약 해당 칸이 비어 있으면
			userB[posR][posC] = i + 1;					// i 작성
		else
			i--;										// 아니라면 i 감소하고 다시 반복
	}

	for (int i = 0; i < MAX_NUM; i++)					// 컴퓨터의 빙고판
	{
		posR = rand() % ROW;
		posC = rand() % COL;

		if (!comB[posR][posC])							// 만약 해당 칸이 비어 있으면
			comB[posR][posC] = i + 1;					// i 작성
		else
			i--;										// 아니라면 i 감소하고 다시 반복
	}
}

void printBoard(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		printf("\n");
		for (int j = 0; j < COL; j++) {
			if (isUOpened[i][j]) 
				printf("	(%d)", userB[i][j]);		// 열려 있다면 괄호 붙여서 출력
			else printf("	%d", userB[i][j]);			// 열려 있지 않으면 그대로 출력
		}
		printf("		");
		for (int k = 0; k < COL; k++) {
			if (isCOpened[i][k])
				printf("	(%d)", comB[i][k]);			// 열려 있다면 괄호 붙여서 출력
			else printf("	-");						// 열려 있지 않으면 '-' 출력
		}
		printf("\n");
	}
	printf("\n");
	printf("		빙고수 : %d						빙고수 : %d\n\n\n", checkBingo(isUOpened), checkBingo(isCOpened));
}

int checkBingo(char isOpened[ROW][COL])			// 빙고 여부 체크
{
	int cnt = 0;								// 총 빙고 수 저장
	int flag = 0;								// 각 라인별로 모두 열렸는지 체크

	for (int i = 0; i < ROW; i++)				// 가로 빙고
	{
		for (int j = 0; j < COL; j++)
			flag += isOpened[i][j];				// 해당 ROW의 open배열 모두 더함
		cnt += (flag == 5) ? 1 : 0;				// 총합이 5라면, 즉 빙고라면 총 개수 +1
		flag = 0;
	}

	for (int i = 0; i < COL; i++)				// 세로 빙고
	{
		for (int j = 0; j < ROW; j++)
			flag += isOpened[j][i];				// 해당 COL의 open배열 모두 더함
		cnt += (flag == 5) ? 1 : 0;				// 총합이 5라면, 즉 빙고라면 총 개수 +1
		flag = 0;
	}

	for (int i = 0; i < ROW; i++)				// 왼쪽 대각선 빙고
		flag += isOpened[i][i];					// 대각선 상의 open배열 모두 더함
	cnt += (flag == 5) ? 1 : 0;					// 총합이 5라면, 즉 빙고라면 총 개수 +1
	flag = 0;

	for (int i = 0; i < ROW; i++)				// 오른쪽 대각선 빙고
		flag += isOpened[i][(COL-1)-i];			// 대각선 상의 open배열 모두 더함
	cnt += (flag == 5) ? 1 : 0;					// 총합이 5라면, 즉 빙고라면 총 개수 +1
	flag = 0;

	return cnt;									// 빙고 총 개수 리턴
}

void playGame(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL])
{
	while (checkBingo(isUOpened) <= ROW || checkBingo(isCOpened) <= ROW)			// 빙고 5개 이하라면 반복
	{
		userTurn(userB, comB, isUOpened, isCOpened);								// 사용자 차례
		printBoard(userB, comB, isUOpened, isCOpened);								// 빙고판 출력

		if (checkBingo(isUOpened) >= ROW || checkBingo(isCOpened) >= ROW) break;	// 빙고 5개 이상이면 종료

		comTurn(userB, comB, isUOpened, isCOpened);									// 컴퓨터 차례
		printBoard(userB, comB, isUOpened, isCOpened);								// 빙고판 출력

		if (checkBingo(isUOpened) >= ROW || checkBingo(isCOpened) >= ROW) break;	// 빙고 5개 이상이면 종료
	}
}

void userTurn(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL])
{
	int userChoice;
	int flag = 0;

	while (true)												// 올바른 숫자 입력할 때까지
	{
		printf("당신의 차례입니다. 몇 번을 열까요? : ");
		scanf("%d", &userChoice);

		if (userChoice <= 0 || userChoice > 25)
		{
			printf("잘못된 값을 입력했습니다. 재입력하세요. \n\n");
			continue;
		}
		else
		{
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COL; j++)
				{
					if (comB[i][j] == userChoice)				// 사용자 입력값과 일치하면
						isCOpened[i][j] = 1;					// 컴퓨터 open 배열 열어줌
					if (userB[i][j] == userChoice)
						isUOpened[i][j] = 1;					// 사용자 open 배열 열어줌
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

	while (flag != 2) {													// 사용자와 컴퓨터의 빙고판 모두가 열려야 함
		flag = 0;
		
		comChoice = searchNum(comB, isCOpened);							// searchNum에서 랜덤 수를 뽑아와 저장

		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				if (comB[i][j] == comChoice && !isCOpened[i][j]) {		// 랜덤 수와 빙고판의 수가 일치하고 열려 있지 않을 때
					isCOpened[i][j] = 1;								// 컴퓨터 open 배열 열기
					flag++;
				}
				if (userB[i][j] == comChoice && !isUOpened[i][j]) {		// 랜덤 수와 빙고판의 수가 일치하고 열려 있지 않을 때
					isUOpened[i][j] = 1;								// 사용자 open 배열 열기
					flag++;
				}
			}
		}
	}
	printf("컴퓨터의 차례입니다. ");
	Sleep(2000);
	printf("%d를 선택했습니다. \n\n", comChoice);
}

char searchNum(char comB[ROW][COL], char isCOpened[ROW][COL]) 
{
	int flag = 0;
	char temp = 0;

	if (!isCOpened[2][2])						// 가운데 빙고판 먼저 열기
		return comB[2][2];
	
	// 대각선 상의 빙고가 가로 빙고보다 중요하므로 먼저 체크함

	for (int i = 0; i < ROW; i++)				// 왼쪽 대각선
	{
		if (!isCOpened[i][i]) 
			temp = comB[i][i];					// 열려 있지 않으면 우선 저장
		flag += isCOpened[i][i];				// 왼쪽 대각선이 몇 개 열렸는지 확인
	}
	if (flag == 4)								// 만약 4개가 열려 있다면
		return temp;							// 열려 있지 않은 값 리턴
	flag = 0;

	for (int i = 0; i < ROW; i++)				// 오른쪽 대각선
	{
		if (!isCOpened[i][(COL - 1) - i]) 
			temp = comB[i][(COL - 1) - i];		
		flag += isCOpened[i][(COL - 1) - i];	// 오른쪽 대각선이 몇 개 열렸는지 확인
	}
	if (flag == 4)
		return temp;
	flag = 0;

	for (int i = 0; i < ROW; i++)				// 가로
	{
		for (int j = 0; j < COL; j++)
		{
			if (!isCOpened[i][j]) 
				temp = comB[i][j];				// 열려 있지 않으면 우선 저장
			flag += isCOpened[i][j];			// 해당 ROW에 몇 개 열렸는지 확인
		}
		if (flag == 4)							// 만약 4개가 열려 있다면
			return temp;						// 열려 있지 않은 값 리턴
		flag = 0;
	}

	for (int i = 0; i < COL; i++)				// 세로
	{
		for (int j = 0; j < ROW; j++)
		{
			if (!isCOpened[j][i]) 
				temp = comB[j][i];
			flag += isCOpened[j][i];			// 해당 COL에 몇 개 열렸는지 확인
		}
		if (flag == 4)
			return temp;
		flag = 0;
	}

	return (rand() % 25 + 1);					// 모두 아니라면 랜덤 수 리턴
}

void printResult(char userB[ROW][COL], char comB[ROW][COL], char isUOpened[ROW][COL], char isCOpened[ROW][COL])
{
	printf("\n");

	for (int i = 0; i < ROW; i++)
	{
		printf("\n");
		for (int j = 0; j < COL; j++) {
			if (isUOpened[i][j])
				printf("	(%d)", userB[i][j]);		// 열려 있다면 괄호 붙여서 출력
			else printf("	%d", userB[i][j]);			// 열려 있지 않으면 그대로 출력
		}
		printf("		");
		for (int k = 0; k < COL; k++) {
			if (isCOpened[i][k])
				printf("	(%d)", comB[i][k]);			// 열려 있다면 괄호 붙여서 출력
			else printf("	%d", comB[i][k]);			// 열려 있지 않으면 그대로 출력
		}
		printf("\n");
	}
	printf("\n");

	if (checkBingo(isUOpened) >= 5 && checkBingo(isCOpened) >= 5)
		printf("비겼습니다.\n\n");
	else if (checkBingo(isUOpened) >= 5) 
		printf("사용자가 이겼습니다.\n\n");
	else if (checkBingo(isCOpened) >= 5)
		printf("컴퓨터가 이겼습니다.\n\n");
	else
		printf("오류!\n");

	printf("\n");
}
