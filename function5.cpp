#include "pch.h"
#include "Library.h"


int pay(LISTBORROW& listBorrow, LISTBOOKS& listBook)
{
	system("cls");
	NODEBORROW* borrow;
	borrow = listBorrow.first;
	if (borrow == NULL)
	{
		printf("Chua co the muon sach!\n");
		system("pause");
		return 0;
	}
	NODEBOOK* book = new NODEBOOK;
	book = listBook.first;
	char  number[20];
	printf("Nhap ma doc gia: ");
	fgets(number, sizeof(number), stdin);
	number[strlen(number) - 1] = '\0';
	bool checkNumber = false;
	while (borrow != NULL)
	{
		if (strcmp(borrow->data.readerNumber, number) == 0)
		{
			checkNumber = true;
			printf("--THONG TIN THE MUON---\n");
			printf("Ma doc gia: %s\n", borrow->data.readerNumber);
			printf("Sach da muon: ");
			printf("%s\n", borrow->data.ISBN);
			printf("Ngay muon: %d/%d/%d\n", borrow->data.dateBorrow.d, borrow->data.dateBorrow.m, borrow->data.dateBorrow.y);
			printf("Ngay tra du kien: %d/%d/%d\n", borrow->data.datePayEx.d, borrow->data.datePayEx.m, borrow->data.datePayEx.y);
			printf("Ngay tra thuc te: ");
			scanf("%d/%d/%d", &borrow->data.datePayReal.d, &borrow->data.datePayReal.m, &borrow->data.datePayReal.y);
			int missed = 0;
			printf("Co bi mat sach khong (nhap 1 neu co, 0 neu khong): ");
			scanf("%d", &missed);
			long punishPrice = 0; //tổng tiền phạt mất sách

								   //nhập, kiểm tra và giảm đi lượng sách đã mượn để trả sách lại vào thư viện
			if (missed == 1)	//nếu mất sách
			{
				for (book = listBook.first; book != NULL; book = book->next) //tra giá sách và cộng 200% giá sách vào tiền phạt
				{

					if (strcmp(borrow->data.ISBN, book->data.ISBN) == 0)	//cần xoá node
					{
						punishPrice += book->data.price * 2;
						printf("Tien phat mat sach: %ld", punishPrice);
						//xoá node
						NODEBORROW* temp;
						temp = listBorrow.first;
						if (temp->next == NULL)	//list card chỉ có 1 phần tử
						{
							listBorrow.first = listBorrow.last = NULL;
							delete(temp);
							return 1;
						}
						else
						{
							while (temp->next != NULL)
							{
								if (strcmp(borrow->next->data.readerNumber, number) == 0)	//so sánh hai chuỗi
								{
									
									temp = temp->next->next;
									delete borrow;	//giải phóng borrow
									return 1;
								}
								temp = temp->next;
							}
						}	//kết thúc xoá node
						
					}
				}
			}	//kết thúc trường hợp mất sách
			//nếu không mất sách thì thực hiện trả sách
			book = listBook.first;
			while (book != NULL)
			{
				//book bị NULL
				if (strcmp(borrow->data.ISBN, book->data.ISBN) == 0) //nếu trùng thì cộng thêm 1 sách vào remaining ( đã trả sách) 
				{
					book->data.remaining++;
					break; //ngừng vòng lặp
				}
				book = book->next;
			}
			//tính tiền phạt nếu trễ ngày, nếu không thì báo trả sách thành công
			int distance = disTance(borrow->data); //gọi hàm tính khoảng cách
			if (distance <= 0) //không vượt quá hạn dự kiến
			{
				printf("Tra sach thanh cong.\n");
				system("pause");
			}
			else
			{ //vượt quá hạn dự kiến, tiền phạt bằng 5k x số ngày bị trễ
				long int punish = 5000 * (distance);
				printf("Qua han du kien tra sach %d ngay. Phi phat: %ld.\n", distance, punish);
				system("pause");
			}
			//error			//xoá node (xoá phiếu mượn sách)

						//xoá node
			NODEBORROW* temp;
			temp = listBorrow.first;
			if (temp->next == NULL)	//list card chỉ có 1 phần tử
			{
				listBorrow.first = listBorrow.last = NULL;
				delete(temp);
				return 1;
			}
			else if (strcmp(borrow->data.readerNumber, temp->data.readerNumber) == 0)
			{
				listBorrow.first = listBorrow.first->next;
				delete(temp);
				return 1;
			}
			else
			{
				while (temp->next != NULL)
				{
					if (strcmp(borrow->next->data.readerNumber, number) == 0)	//so sánh hai chuỗi
					{

						temp = temp->next->next;
						delete borrow;	//giải phóng borrow
						return 1;
					}
					temp = temp->next;
				}
			}	//kết thúc xoá node
		}
		borrow = borrow->next;
	}

	if (checkNumber == false)
	{
		printf("khong tim thay doc gia.\n");
		system("pause");
	}
	
	return 0;
}

int dayInMonth(int month, int year) //hàm tính số ngày trong tháng
{
	switch (month)
	{
	case 2:
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 != 0))
			return 29;
		else return 28;
		break;
	}
	case 4: case 6: case 9: case 11:
	{
		return 30;
		break;
	}
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
	{
		return 31;
		break; 
	}
	default:
		return 0;
	}

}

int disTance(BORROWCARD b) //hàm tính khoảng cách ngày mượn và ngày trả
{

	int dayEx = b.datePayEx.d, monthEx = b.datePayEx.m, yearEx = b.datePayEx.y;
	int dayReal = b.datePayReal.d, monthReal = b.datePayReal.m, yearReal = b.datePayReal.y;
	int i = 0;

	int distanceOfDayEx = dayEx; /* bắt đầu từ ngày mượn và cộng số ngày của các tháng trước đó */
	for (i = 1; i < monthEx; i++)
		distanceOfDayEx += dayInMonth(i, yearEx);

	int distanceOfDayReal = dayReal; /* bắt đầu từ ngày trả và cộng số ngày của các tháng trước đó */
	for (i = 1; i < monthReal; i++) distanceOfDayReal += dayInMonth(i, yearReal);

	/*int distanceOfYear = 0; //cùng năm
	if (yearEx != yearReal) //khác năm
	{
		for (i = yearEx; i < yearReal; i++) distanceOfYear += 365 + (2, i) - 28; //cộng thêm 365 hoặc 366 nếu là năm nhuận
	}*/
	int distance = distanceOfDayReal - distanceOfDayEx /*+ distanceOfYear*/; //khoảng cách giữa ngày mượn và ngày trả
	return distance;
}

//source function delay(), dayInMonth() : http://diendan.congdongcviet.com/threads/t10009::tinh-khoang-cach-giua-2-ngay-trong-lap-trinh-c.cpp


