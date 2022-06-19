#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LADDER_H	14	// ������
#define LADDER_V	9	// ������
#define MAX_H		6	// �ִ� ���� ����
#define MIN_H_SUM	15	// �ּ� 15�� �̻�
#define PLAYER		5	// �÷��̾� ��

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

		// �ټ� ���� ��ٸ� �׸��� ���� �� 4�� �ݺ�
		while (interval < (PLAYER * 2 - 1)) {
			ladderCnt = rand() % 3 + 3;		// ��ٸ� ������ ������ 3 �̻� 5 ����
			ladderSum += ladderCnt;

			if (interval == 7 && ladderSum + 3 < MIN_H_SUM) {	// �� ��ٸ� ���� 15�� �̻�
				ladderCnt = MIN_H_SUM - ladderSum;
			}

			for (int i = 0; i < ladderCnt; i++)
			{
				int temp = rand() % (LADDER_H - 1);		// ���μ��� �� �ε��� ����

				// 1 ���� ���� Ȯ��
				for (int j = 0; j < i; j++) {
					if (ladderCnt >= 6 && i >= ladderCnt - 2) continue;		// ���μ��� 6��, �� �� �̻��� ��� �������� �����Ǵ� ��ٸ��� ���� ���
					else if (ladderCnt == 5 && i >= ladderCnt - 1) continue;	// ���μ��� 5���� ��� �������� �����Ǵ� ��ٸ��� ���� ���

					if (temp == ladderIdx[j] || temp + 1 == ladderIdx[j] || temp - 1 == ladderIdx[j]) {
						flag++;
						break;
					}
				}
				if (interval > 1 && ladder[interval - 2][temp] == 1) flag++;	// �� ��ٸ��� �ߺ� Ȯ��

				// �ߺ��� �ִٸ� �ε��� -1�ϰ� �ٽ� �̱�
				if (flag != 0) i--;
				else ladderIdx[i] = temp;

				flag = 0;
			}

			//int arrlength = sizeof(ladderIdx) / sizeof(int);
			//for (int i = 0; i < arrlength; i++)
			//	printf("%d ", ladderIdx[i]);
			//printf("\n");

			// ��ٸ� ����
			for (int i = 0; i < ladderCnt; i++)
				ladder[interval][ladderIdx[i]] = 1;

			interval += 2;
		}

		// ����� ���
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
			pos = i;	// ��ٸ��� �ε����� ���� ��ġ�� �ε����� �ٲ㼭 �켱 ����
			move[0] = i * 2;
			move[1] = 0;
			while (move[1] != LADDER_H - 1) {
				if (move[0] == 0) {		// ���� ��ġ�� �� ���� ��ٸ��� ���
					if (ladder[1][move[1]] == 1) {
						move[0] += 2;
						move[1] += 1;
					}
					else move[1] += 1;
				}
				else if (move[0] == (PLAYER * 2) - 2) {	// ���� ��ġ�� �� ������ ��ٸ��� ���
					if (ladder[move[0] - 1][move[1]] == 1) {
						move[0] -= 2;
						move[1] += 1;
					}
					else move[1] += 1;
				}
				else {	// �߰� ��ٸ��� ���
					if (ladder[move[0] + 1][move[1]] == 1) {	// �����ʿ� ��ٸ��� �ִ� ���
						move[0] += 2;
						move[1] += 1;
					}
					else if (ladder[move[0] - 1][move[1]] == 1) {	// ���ʿ� ��ٸ��� �ִ� ���
						move[0] -= 2;
						move[1] += 1;
					}
					else move[1] += 1;		// �ƹ��͵� ���� ���
				}
			}

			switch (move[0])	// ���������� ���� ��ġ
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

		// ���� ���
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

