#include "pch.h"
#include "Library.h"

void menuLogin(int &input)	//thuc hien dang nhap de su dung cac chuc nang cu he thong
{
	system("cls");
	printf("1. Dang nhap.\n");
	printf("2. Dang xuat.\n");
	printf("3. Thay doi mat khau.\n");
	printf("4. Cap nhat thong tin ca nhan.\n");
	printf("5. Tao nguoi dung.\n");
	printf("6. Phan quyen nguoi dung.\n");
	printf("Chon chuc nang: ");
	scanf("%d", &input);
	char temp[2];	//biến lưu trữ '\n' sau khi nhấn enter
	gets_s(temp);
}
int readFileMembers(LISTMEMBERS& list)	//đọc danh sách người dùng từ file vào list
{
	FILE* file;
	file = fopen("members.bin", "rb");
	if (file == NULL)
	{
		MEMBER member;
		strcpy(member.userName, "admin");
		strcpy(member.passWord, "admin");
		addMember(list, member);
		return 1;
	}
	fseek(file, 0, SEEK_END);	//chuyển vị trí con trỏ đến cuối của tập tin
	unsigned long fileSize = ftell(file);	//trả về số bytes từ đầu tập tin
	rewind(file);	//chuyển con trỏ lại đầu tập tin
	unsigned long countMembers = fileSize / sizeof(MEMBER);	//đếm số người dùng

	MEMBER* temp = new MEMBER[countMembers];	//biến tạm lưu 

	for (unsigned long i = 0; i < countMembers; i++)
	{
		fread(&temp[i], sizeof(MEMBER), countMembers, file);	//đọc từng member
		addMember(list, temp[i]);	//thêm độc giả vào list
	}
	fclose(file);
	return 1;
}
void login(LISTMEMBERS& list, bool &isLoggedIn, MEMBER &member)
{
	system("cls");
	printf("1.1. Dang nhap\n");
	printf("Ten dang nhap: ");
	fgets(member.userName, sizeof(member.userName), stdin);
	member.userName[strlen(member.userName) - 1] = '\0';	//xoá '\n' ở cuối chuỗi
	printf("Mat khau: ");
	fgets(member.passWord, sizeof(member.passWord), stdin);
	member.passWord[strlen(member.passWord) - 1] = '\0';
	NODEMEMBER *p = list.first;
	while (p != NULL)
	{
		if ((strcmp(p->data.userName, member.userName) == 0) && (strcmp(p->data.passWord, member.passWord) == 0))
		{
			isLoggedIn = true;
			member = p->data;
			break;
		}
		p=p->next;
	}
	if (isLoggedIn == true)
	{
		printf("Dang nhap thanh cong.\n");
	}
	else
	{
		printf("Ten dang nhap hoac mat khau sai.\n");
	}
	system("pause");
}
void logout(bool& isLoggedIn)
{
	isLoggedIn = false;
}
//NHẬP THÔNG TIN CÁ NHÂN	
int checkUsername(char username[], LISTMEMBERS list)	//kiểm tra đã có username này chưa
{
	NODEMEMBER* p;
	p = list.first;
	while (p!=NULL)
	{
		if (strcmp(username, p->data.userName) == 0)	//so sánh username với từng phần tử trong list
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}
void inputMember(MEMBER& member, LISTMEMBERS list)
{
	system("cls");
	printf("1.5. Them nguoi dung.\n");

	printf("Ten dang nhap: ");
	fgets(member.userName, sizeof(member.userName), stdin);
	member.userName[strlen(member.userName) - 1] = '\0';	//xoá '\n' ở cuối chuỗi
	while (checkUsername(member.userName, list) == 1)	//nếu đã có username này thì thông báo và nhập lại
	{
		printf("Ten dang nhap da duoc su dung.\n");
		printf("Nhap lai ten dang nhap: ");
		fgets(member.userName, sizeof(member.userName), stdin);
		member.userName[strlen(member.userName) - 1] = '\0';	//xoá '\n' ở cuối chuỗi
	}
	printf("Mat khau: ");
	fgets(member.passWord, sizeof(member.passWord), stdin);
	member.passWord[strlen(member.passWord) - 1] = '\0';
	printf("Ho ten:	");
	fgets(member.fullName, sizeof(member.fullName), stdin);
	member.fullName[strlen(member.fullName) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("Ngay thang nam sinh: ");
	scanf("%d/%d/%d", &member.bDay.d, &member.bDay.m, &member.bDay.y);
	char temp[10];	//biến lưu trữ '\n' sau khi nhấn enter
	gets_s(temp);
	printf("Gioi tinh: ");
	fgets(member.sex, sizeof(member.sex), stdin);
	member.sex[strlen(member.sex) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("CMND: ");
	fgets(member.idCard, sizeof(member.idCard), stdin);
	member.idCard[strlen(member.idCard) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("Email: ");
	fgets(member.email, sizeof(member.email), stdin);
	member.email[strlen(member.email) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("Dia chi: ");
	fgets(member.address, sizeof(member.address), stdin);
	member.address[strlen(member.address) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	system("pause");
}

NODEMEMBER* createMember(MEMBER member)	//tạo node chứa dữ liệu của người dùng	//cần giải phóng bộ nhớ
{
	NODEMEMBER* p = new NODEMEMBER;
	p->data = member;
	p->next = NULL;
	return p;
}
void addMember(LISTMEMBERS& list, MEMBER member)	//thêm node chứa dữ liệu người dùng vào list
{
	NODEMEMBER* p = createMember(member);	//tạo node chứa member	//cần delete p = create
	if (list.first == NULL)
	{
		list.first = p;
		list.last = p;//nếu list rỗng thì đầu và cuối list đều là p
	}
	else
	{
		list.last->next = p;	//thêm node p vào cuối list
		list.last = p;
	}
}

void writeFileMembers(LISTMEMBERS list)	//cập nhật danh sách người dùng từ list vào file
{
	remove("members.bin");	//xoá file để cập nhật lại tất cả
	FILE* file;
	file = fopen("members.bin", "wb");
	NODEMEMBER* p = new NODEMEMBER;
	p = list.first;
	while (p != NULL)
	{
		fwrite(&p->data, sizeof(MEMBER), 1, file);
		p = p->next;
	}
	fclose(file);
	delete(p);
}
//HIỆN THÔNG TIN CÁ NHÂN
void memberInfor(MEMBER member)
{
	printf("1. Ho ten: %s \n", member.fullName);
	printf("2. Ngay sinh:  %d / %d / %d \n", member.bDay.d, member.bDay.m, member.bDay.y);
	printf("3. Gioi tinh:       %s \n", member.sex);
	printf("4. CMND/PASSPORT:   %s \n", member.idCard);
	printf("5. Dia chi:   %s \n", member.address);
	printf("6. Email: %s \n", member.email);
	printf("\n");
}

void editMember(LISTMEMBERS& list, MEMBER& member)	//cập nhật thông tin cá nhân
{
	memberInfor(member);
	NODEMEMBER* p;
	p = list.first;
	while (p!=NULL)
	{
		if (strcmp(p->data.userName, member.userName) == 0)	//so sánh chuỗi
		{
			int input;
			printf("Chon thong tin can chinh sua: ");
			scanf("%d", &input);
			char temp[5];	//biến lưu '\n'
			gets_s(temp);
			if (input == 1)
			{
				printf("Ho ten: ");
				fgets(p->data.fullName, sizeof(p->data.fullName), stdin);
				p->data.fullName[strlen(p->data.fullName) - 1] = '\0';
			}
			else if (input == 2)
			{
				printf("Ngay thang nam sinh: ");
				scanf("%d/%d/%d", &p->data.bDay.d, &p->data.bDay.m, &p->data.bDay.y);
				gets_s(temp);
			}
			else if (input == 3)
			{
				printf("Gioi tinh: ");
				fgets(p->data.sex, sizeof(p->data.sex), stdin);
				p->data.sex[strlen(p->data.sex) - 1] = '\0';
			}
			else if (input == 4)
			{
				printf("CMND: ");
				fgets(p->data.idCard, sizeof(p->data.idCard), stdin);
				p->data.idCard[strlen(p->data.idCard) - 1] = '\0';//xoá '\n' ở cuối chuỗi
			}
			else if (input == 5)
			{
				printf("Dia chi: ");
				fgets(p->data.address, sizeof(p->data.address), stdin);
				p->data.address[strlen(p->data.address) - 1] = '\0';

			}
			else if (input == 6)
			{
				printf("Email: ");
				fgets(p->data.email, sizeof(p->data.email), stdin);
				p->data.email[strlen(p->data.email) - 1] = '\0';
			}
			member = p->data;
			printf("Cap nhat thanh cong.\n");
			system("pause");
			break;
		}
		p = p->next;
	}
	
}
void changePassword(LISTMEMBERS& list, MEMBER& member)
{
	char password[20];	//mật khẩu người dùng nhập để kiểm tra
	bool passCheck = false;
	while (passCheck == false) //Nhập lại mật khẩu cũ nếu check không đúng lặp cho tới khi nhập đúng mk cũ
	{
		system("cls");
		printf("1.3. Thay doi mat khau.\n");
		printf("Neu quen mat khau, lien he admin, nhan 0 de thoat!\nNhan 1 de tiep tuc.\n");
		int choose;
		scanf("%d", &choose);
		char temp[2];	//biến lưu trữ '\n' sau khi nhấn enter
		gets_s(temp);
		if (choose == 0)
		{
			break;
		}
		printf("Mat khau cu: ");
		fgets(password, sizeof(password), stdin);
		password[strlen(password) - 1] = '\0';
		if (strcmp(password, member.passWord) == 0)
		{
			passCheck = true; //passCheck để ngưng vòng lặp
			printf("Mat khau moi: ");
			fgets(member.passWord, sizeof(member.passWord), stdin);
			member.passWord[strlen(member.passWord) - 1] = '\0';
			NODEMEMBER* p;
			p = list.first;
			while (p != NULL)
			{
				if (strcmp(p->data.userName, member.userName) == 0)	//so sánh chuỗi
				{
					strcpy(p->data.passWord, member.passWord);	//dùng hàm strcpy
					break;
				}
				p = p->next;
			}
			printf("Thay doi mat khau thanh cong\n");
			system("pause");
		}
	}
}
int setType(LISTMEMBERS& list)	//phân quyền người dùng
{
	system("cls");
	char idCard[11];	// CMND cần tìm
	printf("Nhap CMND cua nguoi dung:	");
	fgets(idCard, 11, stdin);
	idCard[strlen(idCard) - 1] = '\0';
	NODEMEMBER* p;
	p = list.first;	//gán đầu list vào p
	if (p == NULL)
	{
		printf("Chua co nguoi dung.\n");
		system("pause");
		return 0;
	}
	while (p != NULL)
	{
		if (strcmp(p->data.idCard, idCard) == 0)	//so sánh hai chuỗi
		{
			printf("Tim thay nguoi dung co CMND %s\n", p->data.idCard);
			memberInfor(p->data);
			printf("\nChon quyen cho nguoi dung (quan li: 1, chuyen vien: 0): ");
			scanf("%d", &p->data.type);
			return 1;
		}
		p = p->next;
	}
	printf("Khong tim thay nguoi dung.\n");
	system("pause");
	return 0;
}
void loginNotification()
{
	system("cls");
	printf("Ban da dang nhap.\n");
	system("pause");
}
void notLoginNotification()
{
	system("cls");
	printf("Ban chua dang nhap.\n");
	system("pause");
}
int checkType(MEMBER member)	//hàm kiểm tra quyền người dùng
{
	if (strcmp(member.userName, "admin")==0)
	{
		return -1;	//đây là admin
	}
	else if (member.type == 1)
	{
		return 1;	//đây là quản lí
	}
	else
	{
		return 0;
	}
}
void errorNotification()
{
	system("cls");
	printf("Ban khong co quyen thuc hien chuc nang nay. Hay lien he voi admin.\n");
	system("pause");
}
void clearListMembers(NODEMEMBER* p)	//hàm giải phóng bộ nhớ	//tham chiếu list.first vào
{
	NODEMEMBER* temp;	//khai báo biến tạm
	while (p != NULL) //vòng lặp này giải phóng từng node từ đầu đến khi gặp NULL
	{
		temp = p->next;	//gán giá trị tiếp theo trong list cho temp
		delete p;	//xoá giá trị hiện tại
		p = temp;	//giá trị hiện tại là temp
	}
}








