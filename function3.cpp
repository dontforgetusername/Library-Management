#include "pch.h"
#include "Library.h"

//chức năng 3: quản lí sách
void menuBooks(int &input)
{
	system("cls");
	printf("1. Xem danh sach cac sach trong thu vien.\n");
	printf("2. Them sach.\n");
	printf("3. Chinh sua thong tin mot quyen sach.\n");
	printf("4. Xoa thong tin sach.\n");
	printf("5. Tim kiem sach theo ISBN.\n");
	printf("6. Tim kiem sach theo ten sach.\n");
	printf("Chon chuc nang: ");
	scanf("%d", &input);
	char temp[2];	//biến lưu trữ '\n' sau khi nhấn enter
	gets_s(temp);
}
int readFileBooks(LISTBOOKS &list)	//đọc danh sách sách từ file vào list	
{
	FILE *file;
	file = fopen("books.bin", "rb");
	if (file == NULL)
	{
		return 0;
	}
	fseek(file, 0, SEEK_END);	//chuyển vị trí con trỏ đến cuối của tập tin
	unsigned long fileSize = ftell(file);	//trả về số bytes từ đầu tập tin
	rewind(file);	//chuyển con trỏ lại đầu tập tin
	unsigned long countBooks = fileSize / sizeof(BOOK);	//đếm số sách

	BOOK *temp = new BOOK[countBooks];	//biến tạm lưu 

	for (unsigned long i = 0; i < countBooks; i++)
	{
		fread(&temp[i], sizeof(BOOK), countBooks, file);	//đọc từng sách
		addBook(list, temp[i]);	//thêm sách vào list
	}
	fclose(file);
	return 1;
}
void addBook(LISTBOOKS &list, BOOK book)	//thêm node chứa dữ liệu sách vào list
{
	NODEBOOK *p = createBook(book);	//tạo node chứa reader
	if (list.first == NULL)
	{
		list.first = p;
		list.last = p;	//nếu list rỗng thì đầu và cuối list đều là p
	}
	else
	{
		list.last->next = p;	//thêm node p vào cuối list
		list.last = p;
	}
}
NODEBOOK *createBook(BOOK book)	//tạo node chứa dữ liệu sách	//cần giải phóng bộ nhớ
{
	NODEBOOK *p = new NODEBOOK;
	p->data = book;
	p->next = NULL;
	return p;
}
int checkISBN(char ISBN[], LISTBOOKS list)	//kiểm tra đã có ISBN này chưa
{
	NODEBOOK* p;
	p = list.first;
	while (p != NULL)
	{
		if (strcmp(ISBN, p->data.ISBN) == 0)	//so sánh username với từng phần tử trong list
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

void inputBook(BOOK &book, LISTBOOKS list)	//nhập sách
{
	
	system("cls");
	printf("3.2. Them sach.\n");

	printf("Nhap ISBN (ma sach) (co 4 ki tu): ");
	fgets(book.ISBN, sizeof(book.ISBN), stdin);
	book.ISBN[strlen(book.ISBN) - 1] = '\0';	//xoá '\n' ở cuối chuỗi
	while (checkISBN(book.ISBN, list) == 1)	//nếu đã có ISBN này thì thông báo và nhập lại
	{
		printf("Da co ISBN nay.\n");
		printf("Nhap lai ISBN: ");
		fgets(book.ISBN, sizeof(book.ISBN), stdin);
		book.ISBN[strlen(book.ISBN) - 1] = '\0';	//xoá '\n' ở cuối chuỗi
	}

	printf("Ten sach: ");
	fgets(book.name, sizeof(book.name), stdin);
	book.name[strlen(book.name) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("Tac gia: ");
	fgets(book.author, sizeof(book.author), stdin);
	book.author[strlen(book.author) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("Nha xuat ban: ");
	fgets(book.pubCom, sizeof(book.pubCom), stdin);
	book.pubCom[strlen(book.pubCom) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("Nam xuat ban: ");
	scanf("%d", &book.pubYear);
	char temp[10];	//biến lưu \n sau khi nhấn enter
	gets_s(temp);
	printf("The loai: ");
	fgets(book.type, sizeof(book.type), stdin);
	book.type[strlen(book.type) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	printf("Gia sach: ");
	scanf("%ld", &book.price);
	printf("So quyen sach: ");
	scanf("%d", &book.remaining);
	system("pause");
}
void writeFileBooks(LISTBOOKS list)	//cập nhật sách từ list vào file
{
	remove("books.bin");	//xoá file để cập nhật lại tất cả
	FILE *file;
	file = fopen("books.bin", "wb");
	NODEBOOK *p;
	p = list.first;
	while (p != NULL)
	{
		fwrite(&p->data, sizeof(BOOK), 1, file);
		p = p->next;
	}
	fclose(file);
}
void printBooksList(LISTBOOKS list)	//in danh sách các sách
{
	system("cls");
	NODEBOOK *p;
	p = list.first;	//gán đầu list vào p
	if (p == NULL)
	{
		printf("Chua co sach.\n");
	}
	else
	{
		while (p != NULL)
		{
			printf("ISBN (ma sach): %s\n", p->data.ISBN);
			printf("\tTen sach: %s\n", p->data.name);
			printf("\tTac gia: %s\n", p->data.author);
			printf("\tNha xuat ban: %s\n", p->data.pubCom);
			printf("\tNam xuat ban: %d\n", p->data.pubYear);
			printf("\tThe loai: %s\n", p->data.type);
			printf("\tGia sach: %ld\n", p->data.price);
			printf("\tSo quyen sach: %d\n", p->data.remaining);
			printf("--------------------\n");
			p = p->next;
		}
	}
	system("pause");
}
int editBook(LISTBOOKS &list)	//sửa thông tin một quyển sách
{
	system("cls");
	printf("3.3. Chinh sua thong tin mot quyen sach.\n");
	char number[6];	// mã sách cần xoá
	printf("Nhap ma sach (ISBN): ");
	fgets(number, 6, stdin);
	number[strlen(number) - 1] = '\0';
	NODEBOOK *p;
	p = list.first;	//gán đầu list vào p
	if (p == NULL)
	{
		printf("Chua co sach.\n");
		system("pause");
		return 0;
	}
	while (p != NULL)
	{
		if (strcmp(number,p->data.ISBN)==0)	//so sanh hai chuoi
		{
			printf("Tim thay ma sach: %s\n", p->data.ISBN);
			menuEditBook(p->data);	//mở menu chọn mục chỉnh sửa
			return 1;
		}
		p = p->next;	//sau khi hết vòng lặp và i chưa đạt tới giá trị sizeof(number) trỏ đến node tiếp theo
	}
	printf("Khong tim thay sach.\n");
	system("pause");
	return 0;
}
void menuEditBook(BOOK &book)	//chọn thông tin cần chỉnh sửa
{
	printf("------------------------------\n");
	printf("1. Ten sach\n");
	printf("2. Tac gia\n");
	printf("3. Nha xuat ban\n");
	printf("4. Nam xuat ban\n");
	printf("5. The loai\n");
	printf("6. Gia sach\n");
	printf("7. So quyen sach\n");
	int input;
	printf("Chon thong tin can chinh sua: ");
	scanf("%d", &input);
	char temp[5];	//biến lưu '\n'
	gets_s(temp);
	if (input == 1)
	{
		printf("Ten sach: ");
		fgets(book.name, sizeof(book.name), stdin);
		book.name[strlen(book.name) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	}
	else if (input == 2)
	{
		printf("Tac gia: ");
		fgets(book.author, sizeof(book.author), stdin);
		book.author[strlen(book.author) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	}
	else if (input == 3)
	{
		printf("Nha xuat ban: ");
		fgets(book.pubCom, sizeof(book.pubCom), stdin);
		book.pubCom[strlen(book.pubCom) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	}
	else if (input == 4)
	{
		printf("Nam xuat ban: ");
		scanf("%d", &book.pubYear);
		gets_s(temp);
	}
	else if (input == 5)
	{
		printf("The loai: ");
		fgets(book.type, sizeof(book.type), stdin);
		book.type[strlen(book.type) - 1] = '\0';//xoá '\n' ở cuối chuỗi
	}
	else if (input == 6)
	{
		printf("Gia sach: ");
		scanf("%ld", &book.price);
	}
	else if (input == 7)
	{
		printf("So quyen sach: ");
		scanf("%d", &book.remaining);
	}
	printf("Chinh sua thanh cong.\n");
	system("pause");
}
void clearListBooks(NODEBOOK *p)	//hàm giải phóng bộ nhớ	//tham chiếu list.first vào
{
	NODEBOOK *temp;	//khai báo biến tạm
	while (p != NULL) //vòng lặp này giải phóng từng node từ đầu đến khi gặp NULL
	{
		temp = p->next;	//gán giá trị tiếp theo trong list cho temp
		delete p;	//xoá giá trị hiện tại
		p = temp;	//giá trị hiện tại là temp
	}
}
int menuDeleteBook(LISTBOOKS &list)	//xoá 1 sách	trong list	
{
	system("cls");
	printf("3.4. Xoa thong tin sach.\n");
	char number[6];	// mã sách cần xoá
	printf("Nhap ma sach (ISBN): ");
	fgets(number, 6, stdin);
	number[strlen(number) - 1] = '\0';
	NODEBOOK *p = new NODEBOOK;
	p = list.first;	//gán đầu list vào p
	if (p == NULL)
	{
		printf("Chua co sach.\n");
		return 0;
	}
	else if (p->next == NULL)	//list chỉ có 1 node	//nghĩa là nếu tìm thấy list không còn sách
	{
		if (strcmp(number,p->data.ISBN)==0)	//so sánh hai chuỗi
		{
			printf("Tim thay ma so doc gia: %s\n", p->data.ISBN);
			list.first = list.last = NULL;
			delete p;
			printf("Xoa sach thanh cong.\n");
			system("pause");
			return 1;
		}
		return 0;
	}
	while (p->next != NULL)
	{
		if (strcmp(number, p->data.ISBN) == 0)	//so sánh hai chuỗi
		{
			printf("Tim thay ma sach: %s\n", p->next->data.ISBN);
			NODEBOOK *temp;
			temp = p->next;	//gán giá trị tiếp theo trong list cho temp
			p = p->next->next;
			delete temp;	//giải phóng temp
			printf("Xoa sach thanh cong.\n");
			system("pause");
			return 1;
		}
		p = p->next;	//sau khi hết vòng lặp và i chưa đạt tới giá trị sizeof(number) trỏ đến node tiếp theo
	}
	//sau khi ra khỏi vòng lặp thì đã duyệt hết list và không tìm được mã sách
	printf("Khong tim thay sach.\n");
	system("pause");
	return 0;
}
int searchByISBN(LISTBOOKS &list)	//tìm kiếm sách theo ISBN
{
	system("cls");
	printf("3.5. Tim kiem sach theo ISBN.\n");
	char number[6];	// mã sách cần tìm
	printf("Nhap ISBN cua sach:	");
	fgets(number, 6, stdin);
	number[strlen(number) - 1] = '\0';
	NODEBOOK *p;
	p = list.first;	//gán đầu list vào p
	if (p == NULL)
	{
		printf("Chua co sach.\n");
		system("pause");
		return 0;
	}
	while (p != NULL)
	{
		if (strcmp(number, p->data.ISBN) == 0)	//so sánh hai chuỗi
		{
			printf("Tim thay sach co ISBN la %s\n", p->data.ISBN);
			printf("\tTen sach: %s\n", p->data.name);
			printf("\tTac gia: %s\n", p->data.author);
			printf("\tNha xuat ban: %s\n", p->data.pubCom);
			printf("\tNam xuat ban: %d\n", p->data.pubYear);
			printf("\tThe loai: %s\n", p->data.type);
			printf("\tGia sach: %ld\n", p->data.price);
			printf("\tSo quyen sach: %d\n", p->data.remaining);
			system("pause");
			return 1;
		}
		p = p->next;	//sau khi hết vòng lặp và i chưa đạt tới giá trị sizeof(number) trỏ đến node tiếp theo
	}
	printf("Khong tim thay sach.\n");
	system("pause");
	return 0;
}
int searchByBookName(LISTBOOKS &list)	//tìm kiếm sách theo tên sách
{
	system("cls");
	printf("3.6. Tim kiem sach theo ten sach.\n");
	char name[50];	// mã sách cần tìm
	printf("Nhap ten sach:	");
	fgets(name, 50, stdin);
	name[strlen(name) - 1] = '\0';
	NODEBOOK *p;
	p = list.first;	//gán đầu list vào p
	if (p == NULL)
	{
		printf("Chua co sach.\n");
		system("pause");
		return 0;
	}
	while (p != NULL)
	{
		if (strcmp(name, p->data.name) == 0)	//so sánh hai chuỗi
		{
			printf("Tim thay sach co tên la %s\n", p->data.name);
			printf("\tMa sach (ISBN): %s", p->data.ISBN);
			printf("\tTen sach: %s\n", p->data.name);
			printf("\tTac gia: %s\n", p->data.author);
			printf("\tNha xuat ban: %s\n", p->data.pubCom);
			printf("\tNam xuat ban: %d\n", p->data.pubYear);
			printf("\tThe loai: %s\n", p->data.type);
			printf("\tGia sach: %ld\n", p->data.price);
			printf("\tSo quyen sach: %d\n", p->data.remaining);
			system("pause");
			return 1;
		}
		p = p->next;	//sau khi hết vòng lặp và i chưa đạt tới giá trị sizeof(number) trỏ đến node tiếp theo
	}
	printf("Khong tim thay sach.\n");
	system("pause");
	return 0;
}


