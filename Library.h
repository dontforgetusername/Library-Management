#include "pch.h"


struct date
{
	int d; //day
	int m; //month
	int y; //year
};
struct MEMBER
{
	char userName[20], passWord[20], idCard[11], email[50]; //idCard: chứng minh nhân dân
	date bDay; //birthday
	int status, type; //status: 1 active 0 block, type: 1 quản lý 0 chuyên viên
	char address[100], fullName[30], sex[5];
};
struct READERCARD
{
	char Number[6], idCard[11], email[50], fullName[30], address[100], sex[5];
	date dateCre, dateOut, bDay; //dayCre: ngày lập thẻ, dayOUt: ngày hết hạn
};
struct BOOK
{
	char ISBN[6], name[50], author[30], pubCom[100], type[20]; //ISBN: mã sách (trong đề ghi vậy :v ), pubCom: nhà xuất bản, type thể loại
	int remaining, pubYear; //SỐ sách còn lại  pubYear: năm xuất bản
	long price;
};
struct BORROWCARD
{
	char readerNumber[6];
	date dateBorrow, datePayEx, datePayReal; //dayPayEx : ngày trả dự kiến. dayPayReal: ngày trả thực tế
	char ISBN[6];
};


//struct function 1
struct NODEMEMBER {
	MEMBER data;
	NODEMEMBER* next;
};
struct LISTMEMBERS
{
	NODEMEMBER* first;
	NODEMEMBER* last;
};

//struct function 2
struct NODEREADER
{

	READERCARD data;
	NODEREADER* next;
};
struct LISTREADERS
{
	NODEREADER* first;
	NODEREADER* last;
};

//struct function 3
struct NODEBOOK
{
	BOOK data;
	NODEBOOK* next;
};
struct LISTBOOKS
{
	NODEBOOK* first;
	NODEBOOK* last;
};

//struct function 4

struct NODEBORROW
{
	BORROWCARD data;
	NODEBORROW* next;
};
struct LISTBORROW
{
	NODEBORROW* first;
	NODEBORROW* last;
};



//MENU CHUNG CỦA CHƯƠNG TRÌNH
void menuFunction(int& input);


//chức năng 1:
void menuLogin(int& input);
int readFileMembers(LISTMEMBERS& list);
void login(LISTMEMBERS& list, bool& isLoggedIn, MEMBER& member);
void logout(bool& isLoggedIn);
int checkUsername(char username[], LISTMEMBERS list);
void inputMember(MEMBER& member, LISTMEMBERS list);
NODEMEMBER* createMember(MEMBER member);
void addMember(LISTMEMBERS& list, MEMBER member);
void writeFileMembers(LISTMEMBERS list);
void memberInfor(MEMBER member);
void editMember(LISTMEMBERS& list, MEMBER& member);
void changePassword(LISTMEMBERS& list, MEMBER& member);
int setType(LISTMEMBERS& list);
void loginNotification();
void notLoginNotification();
int checkType(MEMBER member);
void errorNotification();
void clearListMembers(NODEMEMBER* p);


//chuc nang 2

void menuReaders(int& input);
int readFileReaders(LISTREADERS& list);
int checkReader(char number[], LISTREADERS list);
void inputReader(READERCARD& reader, LISTREADERS list);	
void readerInfor(READERCARD reader);
NODEREADER* createReader(READERCARD reader);
void addReader(LISTREADERS& list, READERCARD reader);
void writeFileReaders(LISTREADERS list);
void printReadersList(LISTREADERS list);
int editReader(LISTREADERS& list);
void menuEditReader(READERCARD& reader);
void clearListReaders(NODEREADER* p);
int menuDeleteReader(LISTREADERS& list);
int searchByIdCard(LISTREADERS list);
int BooksByReaderName(LISTBORROW borrow, LISTREADERS readers, LISTBOOKS books);


//chức năng 3: quản lí sách
void menuBooks(int& input);
int readFileBooks(LISTBOOKS& list);
void addBook(LISTBOOKS& list, BOOK book);
NODEBOOK* createBook(BOOK book);
int checkISBN(char ISBN[], LISTBOOKS list);
void inputBook(BOOK& book, LISTBOOKS list);
void writeFileBooks(LISTBOOKS list);
void printBooksList(LISTBOOKS list);
int editBook(LISTBOOKS& list);
void menuEditBook(BOOK& book);
void clearListBooks(NODEBOOK* p);
int menuDeleteBook(LISTBOOKS& list);
int searchByISBN(LISTBOOKS& list);
int searchByBookName(LISTBOOKS& list);

//chức năng 4: lập thẻ mượn sách
int readFileBorrow(LISTBORROW& list);
void writeFileBorrow(LISTBORROW list);
void clearListBorrow(NODEBORROW* p);
int borrow(LISTREADERS& reader, LISTBOOKS& book, BORROWCARD& b);
NODEBORROW* getBorrow(BORROWCARD& borrow);
void addBorrow(BORROWCARD& b, LISTBORROW& list);
int payEx(BORROWCARD& b);


//chức năng 5: lập thẻ trả sách
int pay(LISTBORROW& list, LISTBOOKS& LIST);
int dayInMonth(int month, int year);
int disTance(BORROWCARD b);

//chức năng 6: các thống kê cơ bản
void menuFilter(int& input);
int booksQuantity(NODEBOOK* p);
void booksFilter();
int booksQuantityByType(NODEBOOK* p, char type[]);
void booksTypeFilter();
int readersQuantity();
void readersFilter();
int readersQuantityBySex(NODEREADER* p, char sex[]);
void ReadersSexFilter();
void booksBorrowed(LISTBORROW& list);
int disTanceCurrent(NODEBORROW* b, tm* TIMER);
int lateReaders(LISTBORROW& list);



