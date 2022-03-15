#include "pch.h"
#include "Library.h"

void menuFunction(int &input)	//chon chuc nang
{
	system("cls");
	printf("1. Dang nhap.\n");
	printf("2. Quan li doc gia.\n");
	printf("3. Quan li sach.\n");
	printf("4. Lap phieu muon sach.\n");
	printf("5. Lap phieu tra sach.\n");
	printf("6. Cac thong ke co ban.\n");
	printf("7. Thoat.\n");
	printf("Chon chuc nang: ");
	scanf("%d", &input);
	char temp[2];	//biến lưu trữ '\n' sau khi nhấn enter
	gets_s(temp);
}














