#include "book.h"
#include "user.h"
#include "borrow.h"
#include "code.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define BOOK_PATH   "Book.txt" 
#define USER_PATH   "User.txt"
#define BORROW_PATH "Borrow.txt" 

Book books[1000];
Borrow_record borrow_records[500];

int book_n = 0;

void read_book(const char filename[])
{
	char content[100];
	int i = 0;
	FILE *fp_book;
 	if(!(fp_book=fopen(BOOK_PATH,"r")))
  	{
     	printf("error to open book");
     	exit(0);
   	} 
   	fgets(content,100,fp_book);  //�ѵ�һ�ж��� 
   	while(!feof(fp_book))
    {
     	i++;
     	fscanf(fp_book,"%d%s%s%s%s%s%s%s%d",
 				 		&book_n, 
						books[i].id, 
						books[i].name,
						books[i].author,
						books[i].kind, 
						books[i].publisher, 
						books[i].time,
						books[i].price,
						&books[i].state );
    }
    fclose(fp_book); 
}

 void save_book(const char filename[])
 {
 	int i;
 	FILE* fp_book=fopen(filename,"w");
	
 	if(fp_book == NULL)
  	{
     	printf("error");
     	exit(0);
   	}
   	freopen(BOOK_PATH, "w", stdout);  //����ض������ļ� 
   	
   	printf("���\t��¼��\t\t����\t\t����\t\t�����\t\t") ;
   	printf("���浥λ\t\t����ʱ��\t\t�۸�\t\�Ƿ�ɽ�\n") ;
   	
    for(i=1; i<=book_n; i++)
    {
    	printf("%d\t", i);
		print_book(books + i);
   	}
   	freopen("CON", "w", stdout);  //����ض���������̨ 
    fclose(fp_book);
 }

 void print_book(const Book *book)
 {
 	printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%d\n", 
				book->id,
				book->name, 
				book->author,
				book->kind,
				book->publisher,
	 			book->time,	
			 	book->price,
			 	book->state);
 }
 
 void cpy_book(int i)
 {
 	while(i<book_n)
	{
		strcpy(books[i].id       , books[i+1].id);
		strcpy(books[i].name     , books[i+1].name);
		strcpy(books[i].author   , books[i+1].author);
		strcpy(books[i].kind     , books[i+1].kind);
		strcpy(books[i].publisher, books[i+1].publisher);
		strcpy(books[i].time     , books[i+1].time);
		strcpy(books[i].price    , books[i+1].price);
		books[i].state = books[i+1].state;
		i++;
	} 
 }
 
 void add_book()
 {
 	book_n++;            //����������� 1 
	printf("�������¼��:\n");
	scanf("%s",books[book_n].id);			
	printf("����������:\n");
	scanf("%s",books[book_n].name);
	printf("������������:\n");
	scanf("%s",books[book_n].author) ;
	printf("����������:\n");
	scanf("%s",books[book_n].kind);
	printf("��������浥λ:\n");
	scanf("%s",books[book_n].publisher);
	printf("���������ʱ��:\n");
	scanf("%s",books[book_n].time);
	printf("������۸�:\n");
	scanf("%s",books[book_n].price);
	books[book_n].state = 1; 
	save_book(BOOK_PATH);
 }
 
 void look_book()
 {
 	int i;
 	printf("���\t��¼��\t\t����\t\t����\t\t�����\t\t") ;
 	printf("���浥λ\t\t����ʱ��\t\t�۸�\t\t�Ƿ�ɽ�\n") ;
 	for(i=1; i<=book_n; i++)
	{
		printf("%d\t", i); 
		print_book(books+i);
	}
 }
 void edit_book()
 {
	int instruction, change;
	printf("������Ҫ�༭��ͼ�����:\n");
	scanf("%d",&change);
	print_book(books+change);
	printf("������Ҫ�޸ĵ����ݣ�1.��¼�� 2.���� 3.���� 4.����� 5.���浥λ\n");
	printf("6.����ʱ�� 7.�۸� 8.����ȫ�� ���ఴ��ȡ��\n");
	scanf("%d",&instruction);
	switch(instruction)
	{
		case 1:
		{
			printf("���������޸ĵ�ͼ���¼��:\n");
			scanf("%s", books[change].id);
			break;
		}
		case 2:
		{
			printf("���������޸ĵ�ͼ����:\n");
			scanf("%s", books[change].name);
			break;
		}
		case 3:
		{
			printf("���������޸ĵ�ͼ��������:\n");
			scanf("%s", books[change].author);
			break;
		}
		case 4:
		{
			printf("���������޸ĵ�ͼ������:\n");
			scanf("%s", books[change].kind);
			break;
		}
		case 5:
		{
			printf("���������޸ĵ�ͼ����浥λ:\n");
			scanf("%s", books[change].publisher);
			break;
		}
		case 6:
		{
			printf("���������޸ĵ�ͼ�����ʱ��:\n");
			scanf("%s", books[change].time);
			break;
		}
		case 7:
		{
			printf("���������޸ĵ�ͼ��۸�:\n");
			scanf("%s", books[change].price);
			break;
		}
		case 8:
		{
			printf("���������޸ĵ�ͼ���¼��:\n");
			scanf("%s", books[change].id);
			printf("���������޸ĵ�ͼ����:\n");
			scanf("%s", books[change].name);
			printf("���������޸ĵ�ͼ��������:\n");
			scanf("%s", books[change].author);
			printf("���������޸ĵ�ͼ������:\n");
			scanf("%s", books[change].kind);
			printf("���������޸ĵ�ͼ����浥λ:\n");
			scanf("%s", books[change].publisher);
			printf("���������޸ĵ�ͼ�����ʱ��:\n");
			scanf("%s", books[change].time);
			printf("���������޸ĵ�ͼ��۸�:\n");
			scanf("%s", books[change].price);
			break;
		}
	} 
	save_book(BOOK_PATH);			
 }
 
 
 void delete_book()
 {
 	int i, instruction;
 	for(i=1; i<=book_n; i++)
 	{
 		printf("%d\t", i);
 	 	print_book(books+i);
 	}
	 	
	printf("������Ҫɾ��ͼ����Ϣ�����:\n");
	scanf("%d", &i);
	if(i>=1 && i<=book_n) 
	{
		if(books[i].state == 1) //û�˽� 
		{
			print_book(books+i);
			printf("��1ȷ��ɾ��������ȡ��\n");
			scanf("%d", &instruction);
			if(instruction == 1)
			{
				cpy_book(i);         //�鱾ǰ�ƣ���ɾ������ 
				book_n--;
				save_book(BOOK_PATH);
			}
		}
		else
			printf("�����ѱ��裬����ɾ����\n");
	}
	else 
		printf("�������\n"); 
	
 }
 
 void find_book_window()
 {
 	int instruction;
 	printf("1.������ 2.������ ����ȡ����������һ��\n");
 	scanf("%d", &instruction);
 	if(instruction ==1)
 	{
	 	char name[30];
 		scanf("%s",name);
 		Book *book = find_book_by_name(name);
 		if(book != NULL)
	 		print_book(book);
 		else 
 			printf("��ѯ�޽����");
 	}
 	else if(instruction ==2)
 	{
	 	char author[30];
 		scanf("%s",author);
 		Book *book  = find_book_by_author(author);
 		if(book != NULL)
	 		print_book(book);
 		else 
 			printf("��ѯ�޽����");
 	}
 }
 
  Book *find_book_by_name(const char name[])
 {
 	int i;
 	for(i=1; i<=book_n; i++)
	{
		if(strcmp(name,books[i].name)==0)
		{ 
			return books+i;
 		}
 	}
 	return NULL;
 }
 
  Book *find_book_by_author(const char author[])
 {
 	int i;
 	for(i=1; i<=book_n; i++)
	{
		if(strcmp(author,books[i].author)==0)
		{ 
			return books+i;
 		}
 	}
 	return NULL;
 }
 
 void main_menu()
 {
 	printf(" -------------------------------------------------------- \n");
 	printf("|                  ������ָ��                            |\n");
  	printf("|    1.���ͼ����Ϣ  2.�鿴����ͼ��    3.�༭ͼ����Ϣ    |\n");
	printf("|    4.ɾ��ͼ��      5.����ͼ��        6.����            |\n");
	printf("|    7.����          0.�˳�������                        |\n");
	printf(" -------------------------------------------------------- \n");
 } 
 
 
