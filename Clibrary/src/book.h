#ifndef _ZZZ_BOOK_H___
#define _ZZZ_BOOK_H___

typedef struct Book 
{
	char id[30];        //��¼�� 
 	char name[50];      //���� 
 	char author[30];    //���� 
 	char kind[30];      //����� 
 	char publisher[50]; //���浥λ
	char time[30];      //����ʱ�� 
  	char price[15];     //�۸�
	int state;          //�Ƿ�ɽ� 
}Book;

extern Book books[1000];

void read_book(const char filename[]);   //��ȡ�鼮��¼ 
void save_book(const char filename[]);   //�����鼮��¼ 
void add_book();                         //�½� 
void look_book();                		 //�鿴���� 
void edit_book();               		 //�༭�鼮 
void delete_book();            			 //ɾ���鼮 
void find_book_window();   //�����鼮�������Լ�ȫ�����ܣ� 
Book *find_book_by_name(const char name[]); //���������� 
Book *find_book_by_author(const char author[]);//�����߲��� 
void main_menu();               		 //�˵� 
void print_book(const Book* book); 
									     //һ�δ�ӡ����ͼ�� 
void cpy_book(int i);          			 //�鼮ǰ�ƣ�ɾ���鼮ʱ�ã� 

extern int book_n;             			 //Ŀǰ�鼮���� 

#endif //_ZZZ_BOOK_H___
