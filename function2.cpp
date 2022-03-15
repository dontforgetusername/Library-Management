#include "pch.h"
#include "Library.h"

//chức năng 2: quản lí độc giả
void menuReaders(int &input)	//menu chức năng 2
{
	system("cls");
	printf("1. Xem danh sach doc gia trong thu vien.\n");
	printf("2. Them doc gia.\n");
	printf("3. Chinh sua thong tin mot doc gia.\n");
	printf("4. Xoa thong tin mot doc gia.\n");
	printf("5. Tim kiem doc gia theo CMND.\n");
	printf("6. Tim kiem sach theo ho ten.\n");
	printf("Chon chuc nang: ");
	scanf("%d", &input);
	char temp[2];	//biến lưu trữ '\n' sau khi nhấn enter
	gets_s(temp);
}
void readerInfor(READERCARD reader)
{
	printf("Ma doc gia: %s\n", reader.Number);
	printf("Ho ten: %s\n", reader.fullName);
	printf("CMND: %s\n", reader.idCard);
	printf("Ngay thang nam sinh: %d/%d/%d\n", reader.bDay.d, reader.bDay.m, reader.bDay.y);
	printf("Gioi tinh: %s\n", reader.sex);
	printf("Email: %s\n", reader.email);
	printf("Dia chi: %s\n", reader.address);
	printf("Ngay lap the: %d/%d/%d\n", reader.dateCre.d, reader.dateCre.m, reader.dateCre.y);
	printf("Ngay het han the: %d/%d/%d\n", reader.dateOut.d, reader.dateOut.m, reader.dateOut.y);
	printf("------------------------\n");
}

int readFileReaders(LISTREADERS &list)	//sau hàm nhớ delete list //đọc danh sách độc giả từ file vào list
{
	FILE *file;
	file = fopen("readers.bin", "rb");
	if (file == NULL)
	{
		return 0;
	}
	fseek(file, 0, SEEK_END);	//chuyển vị trí con trỏ đến cuối của tập tin
	unsigned long fileSize = ftell(file);	//trả về số bytes từ đầu tập tin
	rewind(file);	//chuyển con trỏ lại đầu tập tin
	unsigned long countReaders = fileSize / sizeof(READERCARD);	//đếm số độc giả
	
	READERCARD *temp = new READERCARD[countReaders];	//biến tạm lưu 
	
	for (unsigned long i = 0; i < countReaders; i++)
	{
		fread(&temp[i], sizeof(READERCARD), countReaders, file);	//đọc từng độc giả
		addReader(list, temp[i]);	//thêm độc giả vào list
	}
	
	fclose(file);
	return 1;
}
int checkReader(char number[], LISTREADERS list)	//kiểm tra đã có mã reader này chưa
{
	NODEREADER* p;
	p = list.first;
	while (p != NULL)
	{
		if (strcmp(number, p->data.Number) == 0)	//so sánh mã với từng phần tử trong list
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}
void inputReader(READERCARD &reader, LISTREADERS list)	//nhap nguoi dung
{
	
	system("cls");
	printf("2.2. Them doc gia.\n");
	
	printf("Nhap ma doc gia (co 4 ki tu): ");
	fgets(reader.Number, sizeof(reader.Number), stdin);
	reader.Number[strlen(reader.Number) - 1] = '\0';	//xoá '\n' ở cuối chuỗi
	while (checkReader(reader.Number, list) == 1)	//nếu đã có mã này thì thông báo và nhập lại
	{
		printf("Da co ma doc gia nay.\n");
		printf("Nhap lai ma doc gia: ");
		fgets(reader.Number, sizeof(reader.Number), stdin);
		reader.Number[strlen(reader.Number) - 1] = '\0';	//xoá '\n' ở cuối chuỗi
	}
	printf("Ho ten: ");
	fgets(reader.fullName, sizeof(reader.fullName), stdin);
	reader.fullName[strlen(reader.fullName) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("CMND: ");
	fgets(reader.idCard, sizeof(reader.idCard), stdin);
	reader.idCard[strlen(reader.idCard) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("Ngay thang nam sinh: ");
	scanf("%d/%d/%d", &reader.bDay.d, &reader.bDay.m, &reader.bDay.y);
	char temp[10];	//biến lưu trữ '\n' sau khi nhấn enter
	gets_s(temp);
	printf("Gioi tinh: ");
	fgets(reader.sex, sizeof(reader.sex), stdin);
	reader.sex[strlen(reader.sex) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("Email: ");
	fgets(reader.email, sizeof(reader.email), stdin);
	reader.email[strlen(reader.email) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("Dia chi: ");
	fgets(reader.address, sizeof(reader.address), stdin);
	reader.address[strlen(reader.address) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("Ngay lap the: ");
	scanf("%d/%d/%d", &reader.dateCre.d, &reader.dateCre.m, &reader.dateCre.y);
	gets_s(temp);
	reader.dateOut = reader.dateCre;
	reader.dateOut.y += 4;	//hết hạn sau 4 năm
	printf("Ngay het han the: %d/%d/%d\n", reader.dateOut.d, reader.dateOut.m, reader.dateOut.y);
	system("pause");
}
NODEREADER *createReader(READERCARD reader)	//tạo node chứa dữ liệu của độc giả	//cần giải phóng bộ nhớ
{
	NODEREADER *p = new NODEREADER;	
	p->data = reader;	
	p->next = NULL;
	return p;
}
void addReader(LISTREADERS &list, READERCARD reader)	//sau hàm nhớ delete list	//thêm node chứa dữ liệu độc giả vào list
{
	NODEREADER *p = createReader(reader);	//tạo node chứa readers	//cần delete p = create
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
void writeFileReaders(LISTREADERS list)	//cập nhật danh sách độc giả từ list vào file
{
	remove("readers.bin");	//xoá file để cập nhật lại tất cả
	FILE *file;
	file = fopen("readers.bin", "wb");
	NODEREADER *p;
	p = list.first;
	while (p != NULL)
	{
		fwrite(&p->data, sizeof(READERCARD), 1, file);
		p = p->next;
	}
	fclose(file);
	
}
void printReadersList(LISTREADERS list)	//in danh sách độc giả
{
	system("cls");
	NODEREADER *p;
	p = list.first;	//gán đầu list vào p
	if (p == NULL)
	{
		printf("Chua co doc gia.\n");
	}
	else
	{
		while (p != NULL)
		{
			readerInfor(p->data);
			p = p->next;
		}
	}
	system("pause");
}
int editReader(LISTREADERS &list)	//sửa thông tin độc giả
{
	system("cls");
	printf("2.3. Chinh sua thong tin mot doc gia.\n");
	char number[6];	// mã số độc giả cần chỉnh sửa
	printf("Nhap ma so doc gia:	");
	fgets(number, 6, stdin);
	number[strlen(number) - 1] = '\0';
	NODEREADER *p;
	p = list.first;	//gán đầu list vào p
	if (p == NULL)
	{
		printf("Chua co doc gia.\n");
		system("pause");
		return 0;
	}
	while (p != NULL)
	{
		if (strcmp(p->data.Number,number)==0)	//so sánh chuỗi
								
		{
			printf("Tim thay ma so doc gia: %s\n", p->data.Number);
			menuEditReader(p->data);	//mở menu chọn mục chỉnh sửa
			return 1;
		}
		p = p->next;	
	}
	printf("Khong tim thay doc gia.\n");
	system("pause");
	return 0;
}
void menuEditReader(READERCARD &reader)	//chọn thông tin cần chỉnh sửa
{
	printf("------------------------------\n");
	printf("1. Ho ten\n");
	printf("2. CMND\n");
	printf("3. Ngay thang nam sinh\n");
	printf("4. Gioi tinh\n");
	printf("5. Email\n");
	printf("6. Dia chi\n");
	int input;
	printf("Chon thong tin can chinh sua: ");
	scanf("%d", &input);
	char temp[5];	//biến lưu '\n'
	gets_s(temp);
	if (input == 1)
	{
		printf("Ho ten: ");
		fgets(reader.fullName, sizeof(reader.fullName), stdin);
		reader.fullName[strlen(reader.fullName) - 1] = '\0';
	}
	else if (input == 2)
	{
		printf("CMND: ");
		fgets(reader.idCard, sizeof(reader.idCard), stdin);
		reader.idCard[strlen(reader.idCard) - 1] = '\0';
	}
	else if (input == 3)
	{
		printf("Ngay sinh: ");
		scanf("%d/%d/%d", &reader.bDay.d, &reader.bDay.m, &reader.bDay.y);
		gets_s(temp);
	}
	else if (input == 4)
	{
		printf("Gioi tinh: ");
		fgets(reader.sex, sizeof(reader.sex), stdin);
		reader.sex[strlen(reader.sex) - 1] = '\0';
	}
	else if (input == 5)
	{
		printf("Email: ");
		fgets(reader.email, sizeof(reader.email), stdin);
		reader.email[strlen(reader.email) - 1] = '\0';
	}
	else if (input == 6)
	{
		printf("Dia chi: ");
		fgets(reader.address, sizeof(reader.address), stdin);
		reader.address[strlen(reader.address) - 1] = '\0';
	}
	printf("Chinh sua thanh cong.\n");
	system("pause");
}
void clearListReaders(NODEREADER *p)	//hàm giải phóng bộ nhớ	//tham chiếu list.first vào
{
	NODEREADER *temp;	//khai báo biến tạm
	while (p != NULL) //vòng lặp này giải phóng từng node từ đầu đến khi gặp NULL
	{
		temp = p->next;	//gán giá trị tiếp theo trong list cho temp
		delete p;	//xoá giá trị hiện tại
		p = temp;	//giá trị hiện tại là temp
	}
}
int menuDeleteReader(LISTREADERS &list)	//xoá 1 độc giả	trong list
{
	system("cls");
	printf("2.4. Xoa thong tin mot doc gia.\n");
	char number[6];	// mã số độc giả cần xoá
	printf("Nhap ma so doc gia:	");
	fgets(number, 6, stdin);
	number[strlen(number) - 1] = '\0';
	NODEREADER *p;
	p = list.first;	//gán đầu list vào p
	if (p == NULL)
	{
		printf("Chua co doc gia.\n");
		return 0;
	}
	else if (p->next == NULL)	//list chỉ có 1 node
	{
		if (strcmp(p->data.Number,number)==0)	//so sánh hai chuỗi
		{
			list.first = list.last = NULL;
			delete p;
			printf("Xoa doc gia thanh cong.\n");
			system("pause");
			return 1;
		}
	}
	while (p->next != NULL)
	{
		if (strcmp(p->next->data.Number,number)==0)	//so sánh hai chuỗi
		{
			NODEREADER *temp;	
			//cần giải phóng p->next
			temp = p->next;	//gán giá trị tiếp theo trong list cho temp
			p = p->next->next;
			delete temp;	//giải phóng temp
			printf("Xoa doc gia thanh cong.\n");
			system("pause");
			return 1;
		}
		p = p->next;	
	}
	//sau khi ra khỏi vòng lặp thì đã duyệt hết list và không tìm thấy mã số độc giả
	printf("Khong tim thay doc gia.\n");
	system("pause");
	return 0;
}
int searchByIdCard(LISTREADERS list)	//tìm kiếm độc giả theo cmnd
{
	system("cls");
	printf("2.5. Tim kiem doc gia theo CMND.\n");
	char idCard[11];	// mã số độc giả cần tìm
	printf("Nhap CMND cua doc gia: ");
	fgets(idCard, 11, stdin);
	idCard[strlen(idCard) - 1] = '\0';
	NODEREADER *p;
	p = list.first;	//gán đầu list vào p
	if (p == NULL)
	{
		printf("Chua co doc gia.\n");
		system("pause");
		return 0;
	}
	while (p != NULL)
	{
		if (strcmp(p->data.idCard,idCard)==0)	//so sánh hai chuỗi
		{
			printf("Tim thay doc gia co CMND %s\n", p->data.idCard);
			readerInfor(p->data);
			return 1;
		}
		p = p->next;	
	}
	printf("Khong tim thay doc gia.\n");
	system("pause");
	return 0;
}

int BooksByReaderName(LISTBORROW borrow, LISTREADERS readers, LISTBOOKS books)	//tìm kiếm sách đã mượn theo họ tên độc giả
{
	system("cls");
	printf("2.6. Tim kiem sach theo ho ten.\n");
	char name[30];	// họ tên độc giả cần tìm
	printf("Nhap ho ten cua doc gia: ");
	fgets(name, 30, stdin);
	name[strlen(name) - 1] = '\0';
	NODEREADER* p;
	p = readers.first;	//gán đầu list readers vào p
	if (p == NULL)
	{
		printf("Chua co doc gia.\n");
		system("pause");
		return 0;
	}
	while (p != NULL)
	{
		if (strcmp(p->data.fullName, name) == 0)	//so sánh hai chuỗi
		{
			NODEBORROW* pBorrow;
			pBorrow = borrow.first;	//gán đầu list borrow vào pBorrow
			if (pBorrow == NULL)
			{
				printf("Chua co the muon sach.\n");
				system("pause");
				return 0;
			}
			while (pBorrow!=NULL)
			{
				if (strcmp(p->data.Number, pBorrow->data.readerNumber) == 0)
				{
					printf("Tim thay sach ma doc gia da muon.\n");
					NODEBOOK* pBook;
					pBook = books.first;
					while (pBook!=NULL)
					{
						if (strcmp((pBorrow->data.ISBN), pBook->data.ISBN) == 0)
						{
							printf("Ma sach: %s\n", pBook->data.ISBN);
							printf("Ten sach: %s\n", pBook->data.name);
							printf("----------------\n");
						}
						pBook = pBook->next;
					}
				}
				pBorrow = pBorrow->next;
			}
			return 1;
		}
		p = p->next;
	}
	printf("Khong tim thay the muon sach.\n");
	system("pause");
	return 0;
}
