#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	FILE* fpC;
	FILE* fpM;

	fpC = fopen("BPINK.bmp", "rb");				// 432 * 484, ���� ����(���� �б� ���)
	fpM = fopen("BPINKM.bmp", "wb");			// ��� ��ȯ ����(���� ���� ���)
	char readcolor[3], data[54];

	fread(data, 54, 1, fpC);					// ������ ��� ���� �״�� ����
	fwrite(data, 54, 1, fpM);

	while (!feof(fpC))
	{
		fread(&readcolor, 3, 1, fpC);			// 3����Ʈ(RGB)�� �о����
		for (int i = 0; i < 3; i++)
			fwrite(&readcolor[1], 1, 1, fpM);	// G���� ���߾� ������ 3����Ʈ�� ����
	}											// (R���̳� B���� �̿��ص� ��)

	fclose(fpC);
	fclose(fpM);
}