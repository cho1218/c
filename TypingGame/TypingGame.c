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
	int cnt = 0;					// 총 10번 반복
	int score = 0;					// 점수 총합

	printf("게임을 시작합니다.\n");

	while (cnt++ < 10) {
		printf("(%d/10) ", cnt);
		playGame(&score);
	}

	printf("당신의 점수는 %d점 입니다.\n", score);
}

void playGame(int* score) 
{
	char std[71] = { 0, };				// 기준 문자열
	char input[71] = { 0, };			// 사용자 입력 문자열
	int speed = 0;						// 타자 속도
	int length = rand() % 21 + 50;		// 기준 길이(50-70자 사이)

	printf("다음을 입력하세요\n");

	while (strlen(std) < length && strlen(std) + 6 < 70) {
		strcat(std, makeWord());		// 랜덤 문자열 생성
	}

	std[strlen(std) - 1] = 0;			// 마지막 space 제거

	printf("= %s\n", std);
	printf("= ");

	int t = clock();					// 시작 시간
	fgets(input, 70, stdin);
	t = (clock() - t) / 1000;			// 종료 시간 - 시작 시간

	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = 0;	// 줄바꿈 제거

	speed = strlen(std) / t * 60;

	if (strcmp(std, input) == 0) {
		printf("맞았습니다. (%d점 획득 %d타/분)\n", (20 - t) * 1000, speed);
		*score += (20 - t) * 1000;		// score에 점수 추가
	}
	else
	{
		printWrong(std, input);			// 틀린 글자 찾아주기
		printf("틀렸습니다. (%d타/분)\n", speed);
	}
}

char* makeWord()
{
	char result[7] = { 0, };			// 최대 7글자(최대 5글자 + space + '\0')
	int cnt = rand() % 2 + 4;			// 단어 수 설정
	int i;

	for (i = 0; i < cnt; i++)
		result[i] = rand() % 26 + 65;	// A-Z에서 랜덤으로 값 설정
	result[i] = 32;						// 마지막에 space 삽입

	return result;
}

void printWrong(char com[71], char user[71])
{
	char* comP = com;				// 랜덤 문자열의 포인터
	char* userP = user;				// 사용자 문자열의 포인터 

	printf("  ");

	while (*userP) {
		if (*comP == *userP)		// 두 문자열의 해당 주소의 값이 같다면
			printf(" ");
		else
			printf("^");
		comP++;
		userP++;
	}
	printf("\n");
}
