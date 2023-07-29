#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable: 4996)

int main() {
	srand((unsigned int)time(NULL));
	
	char str1[100][51] = { 0, };						// (1) 일반 배열
	char* str2[100];									// (2) 동적 할당
	int size, i, j;

	for (i = 0; i < 100; i++) {
		size = rand() % 21 + 30;						// 몇 개의 알파벳을 생성할 것인지 결정 (30 ~ 50개)
		str2[i] = malloc(sizeof(char) * (size + 1));	// size만큼 동적 할당
		for (j = 0; j < size; j++) {					// 랜덤으로 알파벳 생성 후 배열에 저장
			str1[i][j] = rand() % 26 + 'A';
			str2[i][j] = rand() % 26 + 'A';
		}
		str2[i][j] = 0;
	}

	printf("배열 저장 방식\n");
	printf("정렬 전 :\n");

	for (i = 0; i < 100; i++)
		printf("%d : %s\n", i + 1, str1[i]);			// 정렬 전 배열 출력

	for (i = 0; i < 99; i++)							// 정렬 코드
		for (j = i + 1; j < 100; j++)
			if (strcmp(str1[i], str1[j]) > 0) {			// 값 교환
				char temp[51] = { 0, };
				strcpy(temp, str1[i]);
				strcpy(str1[i], str1[j]);
				strcpy(str1[j], temp);
			}

	printf("정렬 후 :\n");
	for (i = 0; i < 100; i++)
		printf("%d : %s\n", i + 1, str1[i]);

	printf("\n포인터 저장 방식\n");
	printf("정렬 전 :\n");

	for (i = 0; i < 100; i++)
		printf("%d : %s\n", i + 1, str2[i]);			// 정렬 전 배열 출력

	for (i = 0; i < 99; i++)							// 정렬 코드
		for (j = i + 1; j < 100; j++)
			if (strcmp(str2[i], str2[j]) > 0) {			// 주솟값 교환
				char* ptr;
				ptr = str2[i];
				str2[i] = str2[j];
				str2[j] = ptr;
			}

	printf("정렬 후 :\n");
	for (i = 0; i < 100; i++)
		printf("%d : %s\n", i + 1, str2[i]);			// 정렬 후 배열 출력
}
