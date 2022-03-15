#include "pch.h"
#include "Library.h"


int main()
{
	//khai báo biến liên quan đến người dùng ở ngoài if
	//admin hệ thống
	//username: admin
	//password: admin
	int input;
	bool isLoggedIn = false;
	int type = 0;	//biến quản lí quyền người dùng
	do
	{
		menuFunction(input);
		if (input == 1)
		{
			int input1;
			LISTMEMBERS list;
			MEMBER user;
			list.first = list.last = NULL;	//khởi tạo list
			readFileMembers(list);	//đọc từ file người dùng vào list
			menuLogin(input1);
			if (input1 == 1)
			{
				if (isLoggedIn == false)
				{
					login(list, isLoggedIn, user);	//đăng nhập
					type = checkType(user);	//kiểm tra quyền người dùng lưu vào biến type
				}
				else
				{
					loginNotification();	//nếu đã đăng nhập rồi thì báo lỗi
				}
			}
			else if (input1 == 2)
			{
				if (isLoggedIn == true)
				{
					logout(isLoggedIn);	//đăng xuất
				}
				else
				{
					notLoginNotification();	//nếu chưa đăng nhập thì báo lỗi
				}
			}
			else if (input1 == 3)
			{
				if (isLoggedIn == true)
				{
					changePassword(list, user);	//thay đổi mật khẩu
					writeFileMembers(list);	//cập nhật list vào file
				}
				else
				{
					notLoginNotification();	//nếu chưa đăng nhập thì báo lỗi
				}
			}
			else if (input1 == 4)
			{
				if (isLoggedIn == true)
				{
					editMember(list, user);	//cập nhật thông tin cá nhân
					writeFileMembers(list);	//cập nhật list vào file
				}
				else
				{
					notLoginNotification();	//nếu chưa đăng nhập thì báo lỗi
				}
			}
			else if (input1 == 5)
			{
				if (isLoggedIn == true && type == -1)	//chỉ có admin mới có quyền thực hiện chức năng này (type=-1)
				{
					MEMBER member;
					inputMember(member, list);	//nhập người dùng
					addMember(list, member);	//thêm người dùng vào list
					writeFileMembers(list);	//cập nhật list vào file
				}
				else
				{
					errorNotification();	//báo lỗi
				}
			}
			else if (input1 == 6)
			{
				if (isLoggedIn == true && type == -1)	//chỉ có admin mới có quyền thực hiện chức năng này
				{
					setType(list);	//phân quyền cho người dùng
					writeFileMembers(list);	//cập nhật list vào lại file
				}
				else
				{
					errorNotification();	//báo lỗi
				}
			}
			clearListMembers(list.first);
		}
		else if (isLoggedIn == false && input != 7)
		{
			notLoginNotification();	//nếu chưa đăng nhập và chọn các chức năng từ 2-6 thì báo lỗi
		}
		else if (input == 2)
		{
			int input2;
			LISTREADERS list;	//khởi tạo list
			list.first = NULL;
			list.last = NULL;
			readFileReaders(list);	//hàm lấy dữ liệu từ file vào list
									//có cấp phát động trong hàm createReader nên phải giải phóng bộ nhớ							
			menuReaders(input2);
			if (input2 == 1)
			{
				printReadersList(list);	//xem danh sách độc giả
			}
			else if (input2 == 2)
			{
				READERCARD reader;
				inputReader(reader, list);	//nhập thông tin độc giả
				addReader(list, reader);	//thêm độc giả vào list
				writeFileReaders(list);	//cập nhật list vào lại file
			}
			else if (input2 == 3)
			{
				editReader(list);	//sửa thông tin
				writeFileReaders(list);	//cập nhật list vào file
			}
			else if (input2 == 4)	//chức năng này chỉ dành cho admin và quản lí
			{
				if (type == 0)	//đây là chuyên viên hoặc chưa được phân quyền
				{
					errorNotification();
				}
				else
				{
					menuDeleteReader(list);	//xoá độc giả
					writeFileReaders(list);	//cập nhật vào file
				}
			}
			else if (input2 == 5)
			{
				searchByIdCard(list);	//tìm kiếm độc giả theo CMND
			}
			else if (input2 == 6)
			{
				LISTBOOKS books;
				books.first = books.last = NULL;
				readFileBooks(books);
				LISTBORROW borrow;
				borrow.first = borrow.last = NULL;
				readFileBorrow(borrow);	//đọc file thẻ mượn sách
				BooksByReaderName(borrow, list, books);	//tìm sách mà độc giả mượn
				clearListBooks(books.first);	//giải phóng bộ nhớ
				clearListBorrow(borrow.first);	//giải phóng bộ nhớ
			}
			clearListReaders(list.first);	//giải phóng bộ nhớ cho list

		}
		else if (input == 3)
		{
			int input3;
			LISTBOOKS list;	//khởi tạo list
			list.first = NULL;
			list.last = NULL;
			readFileBooks(list);	//hàm lấy dữ liệu từ file vào list
									//có cấp phát động trong hàm createBook nên phải giải phóng bộ nhớ							
			menuBooks(input3);
			if (input3 == 1)	//chỉ admin hoặc quản lí mới thực hiện được chức năng này
			{
				if (type == 0)	//đây là chuyên viên hoặc chưa được phân quyền
				{
					errorNotification();
				}
				else
				{
					printBooksList(list);	//xem danh sách các sách

				}
			}
			else if (input3 == 2)
			{
				if (type == 0)	//đây là chuyên viên hoặc chưa được phân quyền
				{
					errorNotification();
				}
				else
				{
					BOOK book;
					inputBook(book, list);	//nhập thông tin sách
					addBook(list, book);	//thêm sách vào list
					writeFileBooks(list);	//cập nhật list vào lại file

				}
			}
			else if (input3 == 3)
			{
				if (type == 0)	//đây là chuyên viên hoặc chưa được phân quyền
				{
					errorNotification();
				}
				else
				{
					editBook(list);	//sửa thông tin
					writeFileBooks(list);	//cập nhật list vào file
				}
			}
			else if (input3 == 4)
			{
				if (type == 0)	//đây là chuyên viên hoặc chưa được phân quyền
				{
					errorNotification();
				}
				else
				{
					menuDeleteBook(list);	//xoá sách
					writeFileBooks(list);	//cập nhật list vào file
				}
			}
			else if (input3 == 5)
			{
				searchByISBN(list);	//tìm kiếm độc giả theo ISBN
			}
			else if (input3 == 6)
			{
				searchByBookName(list);
			}
			clearListBooks(list.first);	//giải phóng bộ nhớ cho list
		}
		else if (input == 4)	//tất cả user đều dùng được	//error
		{
			LISTBORROW list;
			list.first = list.last = NULL;
			readFileBorrow(list);
			LISTREADERS readers;
			readers.first = readers.last = NULL;
			readFileReaders(readers);
			LISTBOOKS books;
			books.first = books.last = NULL;
			readFileBooks(books);
			BORROWCARD card;
			borrow(readers, books, card);	//nhập thông tin thẻ mượn sách
			addBorrow(card, list);	//thêm thẻ mượn vào list
			writeFileBorrow(list);	//ghi list vào lại file
			//giải phóng bộ nhớ
			clearListReaders(readers.first);
			clearListBooks(books.first);
			clearListBorrow(list.first);
		}
		else if (input == 5)	//tất cả user đều dùng được
		{
			LISTBORROW borrow;
			borrow.first = borrow.last = NULL;
			readFileBorrow(borrow);
			LISTBOOKS book;
			book.first = book.last = NULL;
			readFileBooks(book);
			pay(borrow, book);
			writeFileBorrow(borrow);
			writeFileBooks(book);
			clearListBorrow(borrow.first);
			clearListBooks(book.first);
		}
		else if (input == 6)
		{
			int input6;
			menuFilter(input6);
			if (input6 == 1)
			{
				if (type == 0)	//đây là chuyên viên hoặc chưa được phân quyền
				{
					errorNotification();
				}
				else
				{
					booksFilter();	//thống kê sách trong thư viện
				}
			}
			else if (input6 == 2)
			{
				if (type == 0)	//đây là chuyên viên hoặc chưa được phân quyền
				{
					errorNotification();
				}
				else
				{
					booksTypeFilter(); //thống kê sách theo thể loại
				}
			}
			else if (input6 == 3)
			{
				if (type == 0)	//đây là chuyên viên hoặc chưa được phân quyền
				{
					errorNotification();
				}
				else
				{
					readersFilter();	//thống kê độc giả
				}
			}
			else if (input6 == 4)
			{
				if (type == 0)	//đây là chuyên viên hoặc chưa được phân quyền
				{
					errorNotification();
				}
				else
				{
					ReadersSexFilter();	//thống kê độc giả theo giới tính
				}

			}
			else if (input6 == 5)	//tất cả user đều dùng được
			{
				LISTBORROW list;
				list.first = list.last = NULL;
				readFileBorrow(list);
				booksBorrowed(list);
				clearListBorrow(list.first);
			}
			else if (input6 == 6)	//tất cả user đều dùng được
			{

				LISTBORROW list;
				list.first = list.last = NULL;
				readFileBorrow(list);
				lateReaders(list);
				clearListBorrow(list.first);
			}
		}
	} while (input != 7);

}



