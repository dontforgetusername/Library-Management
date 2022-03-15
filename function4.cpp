#include "pch.h"
#include "Library.h"

int readFileBorrow(LISTBORROW& list)	//đọc danh sách thẻ mượn sách từ file vào list
{
	FILE* file;
	file = fopen("borrow.bin", "rb");
	if (file == NULL)
	{
		return 0;
	}
	fseek(file, 0, SEEK_END);	//chuyển vị trí con trỏ đến cuối của tập tin
	unsigned long fileSize = ftell(file);	//trả về số bytes từ đầu tập tin
	rewind(file);	//chuyển con trỏ lại đầu tập tin
	unsigned long count = fileSize / sizeof(BORROWCARD);	//đếm số thẻ

	BORROWCARD* temp = new BORROWCARD[count];	//biến tạm lưu 

	for (unsigned long i = 0; i < count; i++)
	{
		fread(&temp[i], sizeof(MEMBER), count, file);	//đọc từng card
		addBorrow(temp[i], list);	//thêm card vào list
	}
	fclose(file);
	return 1;
}
void writeFileBorrow(LISTBORROW list)	//cập nhật danh sách card từ list vào file
{
	remove("borrow.bin");	//xoá file để cập nhật lại tất cả
	FILE* file;
	file = fopen("borrow.bin", "wb");
	NODEBORROW* p = new NODEBORROW;
	p = list.first;
	while (p != NULL)
	{
		fwrite(&p->data, sizeof(BORROWCARD), 1, file);
		p = p->next;
	}
	fclose(file);
	delete(p);
}
void clearListBorrow(NODEBORROW* p)	//hàm giải phóng bộ nhớ	//tham chiếu list.first vào
{
	NODEBORROW* temp;	//khai báo biến tạm
	while (p != NULL) //vòng lặp này giải phóng từng node từ đầu đến khi gặp NULL
	{
		temp = p->next;	//gán giá trị tiếp theo trong list cho temp
		delete p;	//xoá giá trị hiện tại
		p = temp;	//giá trị hiện tại là temp
	}
}
int borrow(LISTREADERS& reader, LISTBOOKS& book, BORROWCARD& card)
{
	system("cls");
	printf("---LAP THE MUON SACH---\n");
	bool checkNumber = false;
	NODEREADER* r = new NODEREADER;	//node duyệt list reader
	r = reader.first;
	if (reader.first == NULL)
	{
		printf("Khong co doc gia.\n");
		system("pause");
		return 0;
	}
	NODEBOOK* B = new NODEBOOK;	//node duyệt list sách
	B = book.first;
	if (B == NULL)
	{
		printf("Khong co sach.\n");
		system("pause");
		return 0;
	}

	printf("Nhap ma doc gia (4 ky tu): ");
	fgets(card.readerNumber, sizeof(card.readerNumber), stdin);
	card.readerNumber[strlen(card.readerNumber) - 1] = '\0';	//xoá '\n' ở cuối chuỗi
	while (r != NULL)	//vòng lặp kiểm tra mã độc giả
	{
		if (strcmp(card.readerNumber, r->data.Number)==0)
		{
			printf("Nhap ISBN cua sach:");
			fgets(card.ISBN, sizeof(card.ISBN), stdin); //nhập ISBN sách 
			card.ISBN[strlen(card.ISBN) - 1] = '\0';
			while (B != NULL)
			{
				if (strcmp(B->data.ISBN, (card.ISBN)) == 0)
				{
					B->data.remaining--;
					printf("Nhap ngay muon: ");
					scanf("%d/%d/%d", &card.dateBorrow.d, &card.dateBorrow.m, &card.dateBorrow.y);
					printf("Ngay tra du kien: ");
					payEx(card);
					system("pause");
					return 1;
				}
				B = B->next;
			}
			printf("Nhap sai ISBN\n");
			return 0;
		}
		r = r->next;
	}
	printf("Khong tim thay ma doc gia nay\n");
	system("pause");
	return 0;

}
NODEBORROW* getBorrow(BORROWCARD& borrow)
{
	NODEBORROW* p = new NODEBORROW;
	p->data = borrow;
	p->next = NULL;
	return p;
}
void addBorrow(BORROWCARD& b, LISTBORROW& list)
{
	NODEBORROW* p = getBorrow(b);
	if (list.first == NULL)
		list.first = list.last = p;
	else
	{
		list.last->next = p;
		list.last = p;
	}
}
int payEx(BORROWCARD& b)
{
	int d = 0, m = 0, y = 0;
	int day = b.dateBorrow.d, month = b.dateBorrow.m, year = b.dateBorrow.y;
	switch (month)
	{
	case 12:
	{
		switch (day)
		{
		case 31:
		{
			d = 7;
			m = 1;
			y = year + 1;
			break;
		}
		case 30:
		{
			d = 6;
			m = 1;
			y = year + 1;
			break;
		}
		case 29:
		{
			d = 5;
			m = 1;
			y = year + 1;
			break;
		}
		case 28:
		{
			d = 4;
			m = 1;
			y = year + 1;
			break;
		}
		case 27:
		{
			d = 3;
			m = 1;
			y = year + 1;
			break;
		}
		case 26:
		{
			d = 2;
			m = 1;
			y = year + 1;
			break;
		}
		case 25:
		{
			d = 1;
			m = 1;
			y = year + 1;
			break;
		}
		default:
		{
			d = day + 7;
			m = month;
			y = year;
		}
		}
		break;
	}

	case 2:
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			switch (day)
			{
			case 29:
			{
				d = 7;
				m = 3;
				y = year;
				break;
			}
			case 28:
			{
				d = 6;
				m = 3;
				y = year;
				break;
			}
			case 27:
			{
				d = 5;
				m = 3;
				y = year;
				break;
			}
			case 26:
			{
				d = 4;
				m = 3;
				y = year;
				break;
			}
			case 25:
			{
				d = 3;
				m = 3;
				y = year;
				break;
			}
			case 24:
			{
				d = 2;
				m = 3;
				y = year;
				break;
			}
			case 23:
			{
				d = 1;
				m = 3;
				y = year;
				break;
			}
			default:
			{
				d = d + 7;
				m = month;
				y = year;
			}
			}
		}
		else
		{
			switch (day)
			{
			case 28:
			{
				d = 7;
				m = 3;
				y = year;
				break;
			}
			case 27:
			{
				d = 6;
				m = 3;
				y = year;
				break;
			}
			case 26:
			{
				d = 5;
				m = 3;
				y = year;
				break;
			}
			case 25:
			{
				d = 4;
				m = 3;
				y = year;
				break;
			}
			case 24:
			{
				d = 3;
				m = 3;
				y = year;
				break;
			}
			case 23:
			{
				d = 2;
				m = 3;
				y = year;
				break;
			}
			case 22:
			{
				d = 1;
				m = 3;
				y = year;
				break;
			}
			default:
			{
				d = d + 7;
				m = month;
				y = year;
			}
			}
		}
		break;
	}

	case 1: case 3: case 5: case 7: case 8: case 10:
	{
		switch (day)
		{
		case 31:
		{
			d = 7;
			m = month + 1;
			y = year;
			break;
		}
		case 30:
		{
			d = 6;
			m = month + 1;
			y = year;
			break;
		}
		case 29:
		{
			d = 5;
			m = month + 1;
			y = year;
			break;
		}
		case 28:
		{
			d = 4;
			m = month + 1;
			y = year;
			break;
		}
		case 27:
		{
			d = 3;
			m = month + 1;
			y = year;
			break;
		}
		case 26:
		{
			d = 2;
			m = month + 1;
			y = year;
			break;
		}
		case 25:
		{
			d = 1;
			m = month + 1;
			y = year;
			break;
		}
		default:
		{
			d = day + 7;
			m = month;
			y = year;
		}
		}
		break;
	}

	default:
	{
		switch (day)
		{
		case 30:
		{
			d = 7;
			m = month + 1;
			y = year;
			break;
		}
		case 29:
		{
			d = 6;
			m = month + 1;
			y = year;
			break;
		}
		case 28:
		{
			d = 5;
			m = month + 1;
			y = year;
			break;
		}
		case 27:
		{
			d = 4;
			m = month + 1;
			y = year;
			break;
		}
		case 26:
		{
			d = 3;
			m = month + 1;
			y = year;
			break;
		}
		case 25:
		{
			d = 2;
			m = month + 1;
			y = year;
			break;
		}
		case 24:
		{
			d = 1;
			m = month + 1;
			y = year;
			break;
		}
		default:
		{
			d = day + 7;
			m = month;
			y = year;
		}
		}
	}
	}
	b.datePayEx.d = d; //lưu giá trị date ở biến tạm vào biến date trong struct BORROWCARD
	b.datePayEx.m = m;
	b.datePayEx.y = y;
	printf("%d/%d/%d\n", d, m, y); //xuất date 
	return 0;
}