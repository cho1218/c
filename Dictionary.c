#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct UNIT							// 단어 단위 구조체		
{
	char word[20];
	char meaning[70];
} Unit;

Unit mydic[51844] = { {0,}, {0,} };

void search();								// 단어 검색

int main() {
	FILE* pfile;
	char* filename = "dict_test.txt";
	char line[100] = { 0, };				// 파일 읽기에 사용할 임시 배열
	char* token;							// 토큰 임시 저장
	int cnt = 0;							// 인덱스 저장용 변수

	pfile = fopen(filename, "r");			// 읽기 모드로 파일 열기

	if (pfile == NULL) {					// 파일을 여는데 실패했을 경우
		printf("fail to open\n");
		return 0;
	}

	while (!feof(pfile)) {					// 파일의 끝까지
		fgets(line, 90, pfile);				// 한 줄씩 읽어오기
		if (feof(pfile)) break;

		token = strtok(line, ":");
		strcpy(mydic[cnt].word, token);		// 앞의 토큰 word에 저장

		token = strtok(NULL, "");
		strcpy(mydic[cnt].meaning, token);	// 뒤의 토큰 meaning에 저장

		cnt++;
	}

	fclose(pfile);							// 파일 닫기
	
	while (true) search();					// 사전 기능 수행

}

void search()
{
	char input[20];							// 사용자 입력 저장
	int i;

	printf("단어 ? ");
	fgets(input, 20, stdin);
	if (input[strlen(input) - 1] == '\n')	// 맨 마지막 줄바꿈문자 공백으로 변경
		input[strlen(input) - 1] = ' ';

	for (i = 0; i < 51844; i++)				// 탐색 후 일치하는 단어가 있다면 출력
	{
		if (strcmp(input, mydic[i].word) == 0) {
			printf("%s%s\n", mydic[i].word, mydic[i].meaning);
			break;
		}
	}
	if (i == 51844) printf("찾으시는 단어가 목록에 없습니다.\n\n");
}