#ifndef _ZZZ_BORROW_H___
#define _ZZZ_BORROW_H___

 typedef struct Borrow_record
 {
 	int number ;          //��� 
 	char book_name[30]; 
 	char book_id[30]; 
 	char user_id[30];		
 }Borrow_record;
 
 extern Borrow_record borrow_records[500];
 
 extern int borrow_n; 

void read_borrow_record() ;		//��ȡ���ļ�¼ 
void save_borrow_record(char filename[]); //������ļ�¼
Borrow_record *find_book_by_user_id(char user_id[]); 
								//����ÿ����������� 
 
void borrow_book(const char user_id[]);	//���� 
void return_book(const char user_id[]); //���� 

extern int book_n;
extern int user_n;
extern int borrow_n; 
extern char user_name[30];   //��ǰ�û����� 

#endif //_ZZZ_BORROW_H___

