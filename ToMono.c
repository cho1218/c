#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	FILE* fpC;
	FILE* fpM;

	fpC = fopen("BPINK.bmp", "rb");				// 432 * 484, 원본 파일(이진 읽기 모드)
	fpM = fopen("BPINKM.bmp", "wb");			// 흑백 변환 파일(이진 쓰기 모드)
	char readcolor[3], data[54];

	fread(data, 54, 1, fpC);					// 사진의 헤더 정보 그대로 복사
	fwrite(data, 54, 1, fpM);

	while (!feof(fpC))
	{
		fread(&readcolor, 3, 1, fpC);			// 3바이트(RGB)씩 읽어오기
		for (int i = 0; i < 3; i++)
			fwrite(&readcolor[1], 1, 1, fpM);	// G값에 맞추어 동일한 3바이트값 쓰기
	}											// (R값이나 B값을 이용해도 됨)

	fclose(fpC);
	fclose(fpM);
}