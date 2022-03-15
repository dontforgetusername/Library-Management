#include "pch.h"
#include "Library.h"

//chức năng 6: Các thống kê cơ bản
void menuFilter(int& input)	//cac thong ke co ban
{
	system("cls");
	printf("1. Thong ke so luong sach trong thu vien.\n");
	printf("2. Thong ke so luong sach theo the loai.\n");
	printf("3. Thong ke so luong doc gia.\n");
	printf("4. Thong ke so luong doc gia theo gioi tinh.\n");
	printf("5. Thong ke so sach dang duoc muon.\n");
	printf("6. Thong ke danh sach doc gia bi tre han.\n");
	printf("Chon chuc nang: ");
	scanf("%d", &input);
	char temp[2];	//biến lưu trữ '\n' sau khi nhấn enter
	gets_s(temp);
}

int booksQuantity(NODEBOOK* p)	//tính số lượng sách
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		return p->data.remaining + booksQuantity(p->next);
	}
}
void booksFilter()	//thống kê sách trong thư viện
{
	LISTBOOKS list;	//khởi tạo list
	list.first = NULL;
	list.last = NULL;
	readFileBooks(list);
	system("cls");
	printf("6.1. Thong ke so luong sach trong thu vien: %d sach.\n", booksQuantity(list.first));
	system("pause");
	clearListBooks(list.first);	//giải phóng bộ nhớ cho list
}
int booksQuantityByType(NODEBOOK* p, char type[])	//tính số lượng sách theo thể loại
{
	if (p == NULL)
	{
		return 0;
	}
	if (strcmp(p->data.type, type) == 0)
	{
		return p->data.remaining + booksQuantityByType(p->next, type);
	}
	return booksQuantityByType(p->next, type);
}
void booksTypeFilter()	//thống kê sách theo thể loại
{
	system("cls");
	LISTBOOKS list;	//khởi tạo list
	list.first = NULL;
	list.last = NULL;
	readFileBooks(list);	//đọc dữ liệu sách từ file ra list
	printf("6.2. Thong ke so luong sach theo the loai\n");
	char type[20];
	printf("Nhap the loai: ");
	fgets(type, 20, stdin);
	type[strlen(type) - 1] = '\0';
	printf("So luong sach cua the loai %s la %d sach.\n", type, booksQuantityByType(list.first, type));
	system("pause");
	clearListBooks(list.first);	//giải phóng bộ nhớ cho list
}
int readersQuantity()	//tính số lượng độc giả
{
	FILE* file;
	file = fopen("readers.bin", "rb");
	if (file == NULL)
	{
		return 0;
	}
	fseek(file, 0, SEEK_END);	//chuyển vị trí con trỏ đến cuối của tập tin
	unsigned long fileSize = ftell(file);	//trả về số bytes từ đầu tập tin
	rewind(file);	//chuyển con trỏ lại đầu tập tin
	unsigned long countReaders = fileSize / sizeof(READERCARD);	//đếm số độc giả
	fclose(file);
	return countReaders;
}
void readersFilter()	//thống kê độc giả trong thư viện
{
	LISTREADERS list;	//khởi tạo list
	list.first = NULL;
	list.last = NULL;
	readFileReaders(list);
	system("cls");
	printf("6.3. Thong ke so luong doc gia trong thu vien: %d doc gia.\n", readersQuantity());
	system("pause");
	clearListReaders(list.first);	//giải phóng bộ nhớ cho list
}
int readersQuantityBySex(NODEREADER* p, char sex[])	//tính số lượng độc giả theo giới tính
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		if (strcmp(p->data.sex, sex) == 0)
		{
			return 1 + readersQuantityBySex(p->next, sex);
		}
		return readersQuantityBySex(p->next, sex);
	}
}

void ReadersSexFilter()	//thống kê độc giả theo giới tính
{
	system("cls");
	LISTREADERS list;	//khởi tạo list
	list.first = NULL;
	list.last = NULL;
	readFileReaders(list);	//đọc dữ liệu độc giả từ file ra list
	printf("6.4. Thong ke so luong doc gia theo gioi tinh\n");
	char sex[5];
	printf("Nhap gioi tinh: ");
	fgets(sex, 5, stdin);
	sex[strlen(sex) - 1] = '\0';
	printf("So luong doc gia co gioi tinh %s la %d doc gia.\n", sex, readersQuantityBySex(list.first, sex));
	system("pause");
	clearListReaders(list.first);	//giải phóng bộ nhớ cho list
}

void booksBorrowed(LISTBORROW& list)
{

	int countBooks = 0; //đếm số sách đang được mượn
	NODEBORROW* b;
	b = list.first;
	if (list.first == NULL)
	{
		printf("Khong co sach duoc muon.\n");
		system("pause");
	}
	else
	{
		//chạy từ đầu tới cuối list, cộng vào countBooks số sách mà mỗi reader mượn
		while (b!=NULL)
		{
			countBooks++;
			b = b->next;
		}
		printf("Co %d sach dang duoc muon.\n", countBooks);
		system("pause");
	}
	

}

int disTanceCurrent(NODEBORROW* b, tm* TIMER) //hàm tính khoảng cách ngày trả dự kiến và ngày hiện tại
{

	int dayEx = b->data.datePayEx.d, monthEx = b->data.datePayEx.m, yearEx = b->data.datePayEx.y;
	int dayCurrent = TIMER->tm_mday, monthCurrent = TIMER->tm_mon, yearCurrent = TIMER->tm_year;
	int i = 0;

	int distanceOfDayEx = dayEx; /* bắt đầu từ ngày trả dự kiến và cộng số ngày của các tháng trước đó */
	for (i = 1; i < monthEx; i++)
		distanceOfDayEx += dayInMonth(i, yearEx);

	int distanceOfDayReal = dayCurrent; /* bắt đầu từ ngày hiện tại và cộng số ngày của các tháng trước đó */
	for (i = 1; i < monthCurrent; i++) dayCurrent += dayInMonth(i, yearCurrent);

	int distanceOfYear = 0; //cùng năm
	if (yearEx != yearCurrent) //khác năm
	{
		for (i = yearEx; i < yearCurrent; i++) distanceOfYear += 365 + (2, i) - 28; //cộng thêm 365 hoặc 366 nếu là năm nhuận
	}
	int distance = distanceOfDayReal - distanceOfDayEx + distanceOfYear; //khoảng cách giữa ngày trả dự kiến và ngày hiện tại
	return distance;
}

int lateReaders(LISTBORROW& list)
{
	system("cls");
	time_t timer;
	time(&timer); //lấy thời gian hệ thống
	tm* TIMER = localtime(&timer); //chuyển thành dạng struct tm 
	NODEBORROW* b = new NODEBORROW;
	if (list.first == NULL)
	{
		printf("Khong co doc gia muon sach.\n");
		system("pause");
		return 0;
	}
	else
	{
		
		for (b = list.first; b != NULL; b = b->next)
		{
			if ((TIMER->tm_mday - b->data.datePayEx.d > 0) && (TIMER->tm_mon - b->data.datePayEx.m == 0) && (TIMER->tm_year - b->data.datePayEx.y == 0))  //ngày hiện tại lớn hơn ngày tra dự kiến, đã loại bỏ trường hợp khác tháng, năm 
			{
				printf("%s tre han %d ngay.\n", b->data.readerNumber, disTanceCurrent(b, TIMER));
				system("pause");
				return 1;
			}
			else if ((TIMER->tm_mon - b->data.datePayEx.m > 0) && (TIMER->tm_year - b->data.datePayEx.y == 0))  //khác tháng => auto trễ hạn
			{
				printf("%s tre han %d ngay.\n", b->data.readerNumber, disTanceCurrent(b, TIMER));
				system("pause");
				return 1;
			}
			else if (TIMER->tm_year - b->data.datePayEx.y > 0) //khác năm => auto trễ hạn
			{
				printf("%s tre han %d ngay.\n", b->data.readerNumber, disTanceCurrent(b, TIMER));
				system("pause");
				return 1;
			}
			
		}
		
		printf("Khong co doc gia nao tre han.\n");
		system("pause");
		return 0;
	}
}