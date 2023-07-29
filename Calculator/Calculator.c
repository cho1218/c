#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

void add(char a[41], char b[41]);
void sub(char a[41], char b[41]);
void mul(char a[41], char b[41]);

int main() {
	char inputX[42] = { 0, };
	char inputY[42] = { 0, };
	char X[41] = { 0, };
	char Y[41] = { 0, };

	printf("input X. ");
	fgets(inputX , sizeof(char) * 42, stdin);

	if (inputX[strlen(inputX) - 1] == '\n') {
		inputX[strlen(inputX) - 1] = 0;
	}

	for (int i = 0; i < strlen(inputX); i++)
	{
		X[i] = inputX[strlen(inputX) - (i + 1)];
	}

	printf("input Y. ");
	fgets(inputY, sizeof(char) * 42, stdin);

	if (inputY[strlen(inputY) - 1] == '\n') {
		inputY[strlen(inputY) - 1] = 0;
	}

	for (int i = 0; i < strlen(inputY); i++)
	{
		Y[i] = inputY[strlen(inputY) - (i + 1)];
	}

	printf("\n");

	//printf("%s\n%s\n", X, Y);

	add(X, Y);
	sub(X, Y);
	mul(X, Y);
}

void add(char a[41], char b[41])
{
	char result[42] = { 0, };
	int length = strlen(a) >= strlen(b) ? strlen(a) : strlen(b);
	int temp, carry = 0, i;

	for (i = 0; i < length; i++)
	{
		temp = carry + (a[i] - 48) + (b[i] - 48);

		while (temp < 0) temp += 48;

		if (temp >= 10)
			carry = 1;
		else
			carry = 0;

		result[i] = (temp % 10) + 48;
	}
	if (carry) result[i] = 49;

	printf("X + Y = ");
	for (i = length; i >= 0; i--)
	{
		if (!result[i]) continue;
		printf("%c", result[i]);
	}
	printf("\n");
}

void sub(char a[41], char b[41])
{
	char result[41] = { 0, };
	int length, temp, carry = 0, i;
	bool sign = false;

	sign = (strlen(a) < strlen(b) ||
		(strlen(a) == strlen(b) && a[strlen(a) - 1] < b[strlen(a) - 1])) ?
		true : false;

	length = strlen(a) >= strlen(b) ? strlen(a) : strlen(b);

	for (i = 0; i < length; i++)
	{
		if (!a[i]) a[i] = 48;
		else if (!b[i]) b[i] = 48;
		
		temp = sign ? (b[i] - 48) - (a[i] - 48) : (a[i] - 48) - (b[i] - 48);
		temp += carry;

		if (temp < 0) {
			carry = -1;
			temp += 10;
		}
		else {
			carry = 0;
		}

		result[i] = (temp % 10) + 48;
	}

	printf("X - Y = ");
	if (sign) printf("-");
	for (int i = 40; i >= 0; i--)
	{
		if (!result[i]) continue;
		printf("%c", result[i]);
	}
	printf("\n");
}

void mul(char a[41], char b[41])
{
	char result[81] = { 0, };
	int temp, length, carry = 0;
	int i = 0, j = 0;

	for (i = 0; i < 40; i++)
	{
		if (!a[i] || !b[i]) break;
		for (j = 0; j < 40; j++)
		{
			if (!a[j] || !b[j]) break;

			if (!result[i + j]) result[i + j] = 48;

			temp =  carry + ((a[i] - 48) * (b[j] - 48));

			if (temp >= 10) {
				carry = temp / 10;
				result[i + j] += temp % 10;
			}
			else {
				carry = 0;
				result[i + j] += temp;
			}
		}
		if (carry) result[i + j] += carry + 48;
	}

	for (i = 0; i < 80; i++)
	{
		if (!result[i]) break;

		if ((result[i] - 48) >= 10000) {
			temp = (result[i] - 48) / 10000;
			result[i + 1] += temp;
			temp = (result[i] - 48) % 10000;
			result[i] = temp + 48;
		}
		else if ((result[i] - 48) >= 1000) {
			temp = (result[i] - 48) / 1000;
			result[i + 1] += temp;
			temp = (result[i] - 48) % 1000;
			result[i] = temp + 48;
		}
		else if ((result[i] - 48) >= 100) {
			temp = (result[i] - 48) / 100;
			result[i + 1] += temp;
			temp = (result[i] - 48) % 100;
			result[i] = temp + 48;
		}
		else if ((result[i]- 48) >= 10) {
			temp = (result[i] - 48) / 10;
			result[i + 1] += temp;
			temp = (result[i] - 48) % 10;
			result[i] = temp + 48;
		}
	}

	printf("X * Y = ");

	for (i = 80; i >= 0; i--)
	{
		if (!result[i] || result[i] == 48) continue;
		else break;
	}

	for (int k = i; k >= 0; k--)
	{
		printf("%c", result[k]);
	}
	printf("\n");
}
