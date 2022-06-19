#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct UNIT							// �ܾ� ���� ����ü		
{
	char word[20];
	char meaning[70];
} Unit;

Unit mydic[51844] = { {0,}, {0,} };

void search();								// �ܾ� �˻�

int main() {
	FILE* pfile;
	char* filename = "dict_test.txt";
	char line[100] = { 0, };				// ���� �б⿡ ����� �ӽ� �迭
	char* token;							// ��ū �ӽ� ����
	int cnt = 0;							// �ε��� ����� ����

	pfile = fopen(filename, "r");			// �б� ���� ���� ����

	if (pfile == NULL) {					// ������ ���µ� �������� ���
		printf("fail to open\n");
		return 0;
	}

	while (!feof(pfile)) {					// ������ ������
		fgets(line, 90, pfile);				// �� �پ� �о����
		if (feof(pfile)) break;

		token = strtok(line, ":");
		strcpy(mydic[cnt].word, token);		// ���� ��ū word�� ����

		token = strtok(NULL, "");
		strcpy(mydic[cnt].meaning, token);	// ���� ��ū meaning�� ����

		cnt++;
	}

	fclose(pfile);							// ���� �ݱ�
	
	while (true) search();					// ���� ��� ����

}

void search()
{
	char input[20];							// ����� �Է� ����
	int i;

	printf("�ܾ� ? ");
	fgets(input, 20, stdin);
	if (input[strlen(input) - 1] == '\n')	// �� ������ �ٹٲ޹��� �������� ����
		input[strlen(input) - 1] = ' ';

	for (i = 0; i < 51844; i++)				// Ž�� �� ��ġ�ϴ� �ܾ �ִٸ� ���
	{
		if (strcmp(input, mydic[i].word) == 0) {
			printf("%s%s\n", mydic[i].word, mydic[i].meaning);
			break;
		}
	}
	if (i == 51844) printf("ã���ô� �ܾ ��Ͽ� �����ϴ�.\n\n");
}