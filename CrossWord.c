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
	char std[11] = { 0, };			// ���� ���ڿ�
	char input[11] = { 0, };		// ���� �ԷµǴ� ���ڿ�

	while (true) {
		getUserInput(input);		// ����� �Է�
		compareWord(std, input);	// ���� ���� Ž�� �� ���
		updateArr(std, input);		// �Է� ���� ���ڿ��� ������ ���ڿ��� �̵�
	}
}

void getUserInput(char word[11])
{
	char temp[11] = { 0, };

	while (true) {
		printf("Word? ");
		scanf("%s", temp);

		if (strlen(temp) < 3) {				// ���ڿ� ���� 2 ����
			printf("too short\n");			
			continue;						// �ٽ� �Է� �ޱ�
		}
		else if (!strcmp(temp, "end")) {	// end �Է��ߴٸ� ���α׷� ����
			exit(0);
		}
		else {
			strcpy(word, temp);				// �ӽ� �迭�� ���ڿ� ����
			break;
		}
	}
}

void compareWord(char pastword[11], char newword[11])
{
	if (pastword[0] == 0) {						// ���� �迭�� ���ڿ��� ���ٸ�(ù ��° �÷��̶��)
		updateArr(pastword, newword);			// ���� �迭�� �Էµ� ���ڿ� �̵�
		getUserInput(newword);					// ����� �Է� �� �� �� �ޱ�
	}

	int pastidx = 0;							// ���� �迭�� ���� ���� �ε���
	int newidx = 0;								// ���ο� �迭�� ���� ���� �ε���
	bool findflag = false;

	for (int i = 0; i < 11; i++)
	{
		if (!pastword[i]) break;				// ���ڿ� ������ �ݺ� ����
		for (int j = 0; j < 11; j++)
		{
			if (!newword[j]) break;
			if (pastword[i] == newword[j]) {	// ���ڰ� ��ġ�ϸ�
				pastidx = i;
				newidx = j;
				findflag = true;
				break;							// �ε��� ���� �������ְ� �ݺ� ����
			}
		}
		if (findflag) break;
	}

	if (findflag) {								// ���� ���ڸ� �߰��ߴٸ�
		for (int i = 0; i < 11; i++)
		{
			if (pastword[i] == 0) break;		// ���ڿ� ������ �ݺ� ����
			if (i == pastidx)					// ����� �ε��� �������� ��ȣ �ٿ� ���
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
	else {										// ���� ���ڰ� �����ٸ�
		printf("no cross word\n");
	}
}

void updateArr(char pastword[11], char newword[11])
{
	strset(pastword, 0);		// ���� �迭�� ���ڿ� �ι��ڷ� �ʱ�ȭ
	strcpy(pastword, newword);	// ���� �迭�� ���ڿ� �̵�
	strset(newword, 0);			// �Է� ���� �迭 �ʱ�ȭ
}
