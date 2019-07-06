#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "book.h"
#include "user.h"
#include "borrow.h"
#include "code.h" 

#define BOOK_PATH   "Book.txt" 
#define BORROW_PATH "Borrow.txt" 

int borrow_n = 0; 

Borrow_record borrow_records[500];

void read_borrow_record()
{
	char content[100];
	int i = 0;
	FILE *fp_borrow;
 	if(!(fp_borrow=fopen(BORROW_PATH,"r")))
  	{
     	printf("error");
     	exit(0);
   	} 
   	fgets(content,100,fp_borrow);  //�ѵ�һ�ж��� 
   	while(!feof(fp_borrow))
    {
     	i++;
     	fscanf(fp_borrow,"%d%s%s%s", 
     					&borrow_records[i].number,				
         				borrow_records[i].book_id,
				  		borrow_records[i].book_name,
		 			  	borrow_records[i].user_id ); 
    }
    borrow_n = i - 1;
    fclose(fp_borrow); 
}

void save_borrow_record(char filename[])
 {
 	int i;
 	FILE* fp_borrow=fopen(filename,"w");
	
 	if(fp_borrow == NULL)
  	{
     	printf("error to open borrow");
     	exit(0);
   	}
   	fprintf(fp_borrow,"���\t���¼��\t\t����\t\t������\t\t\n") ;
   	
    for(i=1; borrow_n !=0 && i<=borrow_n; i++)
    {
		fprintf(fp_borrow,"%d\t%s\t\t%s\t\t%s\n",
	 						i, 
	 						borrow_records[i].book_id, 
							borrow_records[i].book_name,
							borrow_records[i].user_id);
   	}
    fclose(fp_borrow);
 }
 
 Borrow_record *find_book_by_user_id(char user_id[])
 {
 	int i;
 	for(i=1; i<=borrow_n; i++)
	{
		if(strcmp(user_id,borrow_records[i].user_id)==0)
		{ 
			return borrow_records+i;
 		}
 	}
 	return NULL;
 }
 
  
 void borrow_book(const char user_id[])
 {
 	read_borrow_record(BORROW_PATH);
 	char name[30];
 	int instruction;
 	printf("������Ԥ���������\n");
 	scanf("%s",name);
 	Book *book = find_book_by_name(name);
 	if(book != NULL)
 	{
	 	print_book(book);
	 	if(book->state == 0)
	 		printf("�ѱ����ģ�\n");
	 	else
 		{
	 		printf("��1ȷ�����ģ�����ȡ��\n");
		 	scanf("%d", &instruction); 
			if(instruction == 1)	
 			{	
 				printf("����ɹ���\n");
	 			book->state = 0;
	 			borrow_n++;
	 			borrow_records[borrow_n].number = borrow_n; 
	 			strcpy(borrow_records[borrow_n].user_id, user_id);
	 			strcpy(borrow_records[borrow_n].book_id, book->id);
				strcpy(borrow_records[borrow_n].book_name, name);   
					  					//����������Ϣ 
	 			save_borrow_record(BORROW_PATH);
	 			save_book(BOOK_PATH);
 			}	
		}
 	}
	else 
 		printf("��ѯ�޽����\n");
 		
 }
 
 void return_book(const char user_id[])
 {
 	read_borrow_record(BORROW_PATH);
 	char name[30];
 	int i, instruction;
 	Borrow_record  *borrow = find_book_by_user_id(user_id);
 	if(borrow != NULL)
 	{
 		Book *book = find_book_by_name(borrow->book_name);
	 	print_book(book);
	 	printf("��1ȷ���黹������ȡ��\n");
	 	scanf("%d",&instruction); 
	 	if(instruction == 1)	
		{	
			book->state = 1;
			for(i=borrow->number; i<=borrow_n; i++,borrow++)
			{
				//borrow_records[i].number;
				strcpy(borrow_records[i].book_name,
						borrow_records[i+1].book_name);
				strcpy(borrow_records[i].book_id,
						borrow_records[i+1].book_id);
				strcpy(borrow_records[i].user_id,
						borrow_records[i+1].user_id);
				printf("����ɹ���\n");
				borrow_n--; //���������� 1 
			}
	 		save_borrow_record(BORROW_PATH);
			save_book(BOOK_PATH);
		}
 	}
	else 
 		printf("��δ�����κ��鼮��\n");
 		
 }
 