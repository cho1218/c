#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LADDER_H	14	// 가로줄
#define LADDER_V	9	// 세로줄
#define MAX_H		6	// 최대 가로 개수
#define MIN_H_SUM	15	// 최소 15개 이상
#define PLAYER		5	// 플레이어 수

int main() {
	int result[PLAYER][PLAYER] = { 0, };
	int repeat = 0;
	srand((unsigned)time(NULL));

	while (repeat != 100) {
		int ladder[LADDER_V][LADDER_H] = { 0, };
		int ladderIdx[MAX_H] = { 0, };
		int ladderCnt = 0;
		int flag = 0;
		int interval = 1;
		int ladderSum = 0;

		// 다섯 개의 사다리 그리기 위해 총 4번 반복
		while (interval < (PLAYER * 2 - 1)) {
			ladderCnt = rand() % 3 + 3;		// 사다리 개수는 무조건 3 이상 5 이하
			ladderSum += ladderCnt;

			if (interval == 7 && ladderSum + 3 < MIN_H_SUM) {	// 총 사다리 개수 15개 이상
				ladderCnt = MIN_H_SUM - ladderSum;
			}

			for (int i = 0; i < ladderCnt; i++)
			{
				int temp = rand() % (LADDER_H - 1);		// 가로선이 들어갈 인덱스 생성

				// 1 이하 차이 확인
				for (int j = 0; j < i; j++) {
					if (ladderCnt >= 6 && i >= ladderCnt - 2) continue;		// 가로선이 6개, 즉 그 이상일 경우 마지막에 배정되는 사다리는 연속 허용
					else if (ladderCnt == 5 && i >= ladderCnt - 1) continue;	// 가로선이 5개일 경우 마지막에 배정되는 사다리는 연속 허용

					if (temp == ladderIdx[j] || temp + 1 == ladderIdx[j] || temp - 1 == ladderIdx[j]) {
						flag++;
						break;
					}
				}
				if (interval > 1 && ladder[interval - 2][temp] == 1) flag++;	// 옆 사다리와 중복 확인

				// 중복이 있다면 인덱스 -1하고 다시 뽑기
				if (flag != 0) i--;
				else ladderIdx[i] = temp;

				flag = 0;
			}

			//int arrlength = sizeof(ladderIdx) / sizeof(int);
			//for (int i = 0; i < arrlength; i++)
			//	printf("%d ", ladderIdx[i]);
			//printf("\n");

			// 사다리 배정
			for (int i = 0; i < ladderCnt; i++)
				ladder[interval][ladderIdx[i]] = 1;

			interval += 2;
		}

		// 결과값 출력
		printf("\n");
		printf("1 2 3 4 5\n");
		for (int i = 0; i < LADDER_H; i++) {
			for (int j = 0; j < LADDER_V; j++) {
				if (j % 2 == 1) {
					if (ladder[j][i] == 0) printf(" ");
					else printf("-");
				}
				else {
					printf("|");
				}
			}
			printf("\n");
		}
		printf("A B C D E\n");

		int pos = 0;
		int move[2] = { 0, 0 };

		for (int i = 0; i < PLAYER; i++) {
			pos = i;	// 사다리의 인덱스를 현재 위치의 인덱스로 바꿔서 우선 저장
			move[0] = i * 2;
			move[1] = 0;
			while (move[1] != LADDER_H - 1) {
				if (move[0] == 0) {		// 현재 위치가 맨 왼쪽 사다리인 경우
					if (ladder[1][move[1]] == 1) {
						move[0] += 2;
						move[1] += 1;
					}
					else move[1] += 1;
				}
				else if (move[0] == (PLAYER * 2) - 2) {	// 현재 위치가 맨 오른쪽 사다리인 경우
					if (ladder[move[0] - 1][move[1]] == 1) {
						move[0] -= 2;
						move[1] += 1;
					}
					else move[1] += 1;
				}
				else {	// 중간 사다리인 경우
					if (ladder[move[0] + 1][move[1]] == 1) {	// 오른쪽에 사다리가 있는 경우
						move[0] += 2;
						move[1] += 1;
					}
					else if (ladder[move[0] - 1][move[1]] == 1) {	// 왼쪽에 사다리가 있는 경우
						move[0] -= 2;
						move[1] += 1;
					}
					else move[1] += 1;		// 아무것도 없는 경우
				}
			}

			switch (move[0])	// 마지막으로 멈춘 위치
			{
			case 0:
				result[pos][0] += 1;
				break;
			case 2:
				result[pos][1] += 1;
				break;
			case 4:
				result[pos][2] += 1;
				break;
			case 6:
				result[pos][3] += 1;
				break;
			case 8:
				result[pos][4] += 1;
				break;
			default:
				printf("error!\n");
				break;
			}
		}

		// 누계 출력
		for (int i = 0; i < PLAYER; i++) {
			printf("%d : ", i + 1);
			for (int j = 0; j < PLAYER; j++)
				printf("%c(%d) ", j + 65, result[i][j]);
			printf("\n");
		}
		printf("\n\n");
		repeat++;
	}
}

