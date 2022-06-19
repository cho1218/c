#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void getUserInput(char word[11]);
void compareWord(char pastword[11], char newword[11]);
void updateArr(char pastword[11], char newword[11]);

int main(void) 
{
	char std[11] = { 0, };			// 기존 문자열
	char input[11] = { 0, };		// 새로 입력되는 문자열

	while (true) {
		getUserInput(input);		// 사용자 입력
		compareWord(std, input);	// 공통 글자 탐색 후 출력
		updateArr(std, input);		// 입력 받은 문자열을 기존의 문자열로 이동
	}
}

void getUserInput(char word[11])
{
	char temp[11] = { 0, };

	while (true) {
		printf("Word? ");
		scanf("%s", temp);

		if (strlen(temp) < 3) {				// 문자열 길이 2 이하
			printf("too short\n");			
			continue;						// 다시 입력 받기
		}
		else if (!strcmp(temp, "end")) {	// end 입력했다면 프로그램 종료
			exit(0);
		}
		else {
			strcpy(word, temp);				// 임시 배열의 문자열 복사
			break;
		}
	}
}

void compareWord(char pastword[11], char newword[11])
{
	if (pastword[0] == 0) {						// 기존 배열에 문자열이 없다면(첫 번째 플레이라면)
		updateArr(pastword, newword);			// 기존 배열로 입력된 문자열 이동
		getUserInput(newword);					// 사용자 입력 한 번 더 받기
	}

	int pastidx = 0;							// 기존 배열의 공통 글자 인덱스
	int newidx = 0;								// 새로운 배열의 공통 글자 인덱스
	bool findflag = false;

	for (int i = 0; i < 11; i++)
	{
		if (!pastword[i]) break;				// 문자열 끝나면 반복 종료
		for (int j = 0; j < 11; j++)
		{
			if (!newword[j]) break;
			if (pastword[i] == newword[j]) {	// 문자가 일치하면
				pastidx = i;
				newidx = j;
				findflag = true;
				break;							// 인덱스 값을 저장해주고 반복 종료
			}
		}
		if (findflag) break;
	}

	if (findflag) {								// 공통 글자를 발견했다면
		for (int i = 0; i < 11; i++)
		{
			if (pastword[i] == 0) break;		// 문자열 끝나면 반복 종료
			if (i == pastidx)					// 저장된 인덱스 값에서는 괄호 붙여 출력
				printf("(%c)", pastword[i]);
			else
				printf("%c", pastword[i]);
		}

		printf(" - ");

		for (int i = 0; i < 11; i++)
		{
			if (newword[i] == 0) break;
			if (i == newidx)
				printf("(%c)", newword[i]);
			else
				printf("%c", newword[i]);
		}

		printf("\n");
	}
	else {										// 공통 글자가 없었다면
		printf("no cross word\n");
	}
}

void updateArr(char pastword[11], char newword[11])
{
	strset(pastword, 0);		// 기존 배열의 문자열 널문자로 초기화
	strcpy(pastword, newword);	// 기존 배열로 문자열 이동
	strset(newword, 0);			// 입력 받을 배열 초기화
}
