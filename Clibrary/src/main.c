/****************************************************
                ͼ�����Ϣ����ϵͳ 
         
���ܸ�����1.��ɾ�ҸĴ�    	      ��д�ˣ������ 
          2.�˵����ܣ��������� 			  ���ڴ� 
          3.�û���¼����Ĺ��� 			  ��Ҷ�� 
           
 ****************************************************/
 
 /**************************************************
 
 ���ִ���˵����1.������Ϣ��ͨ��txt���棬
		    	 �����û����뾭�����ܴ���
	           2.���ö��ļ������ٽ���ĩ
			     ���Բ��ֺ���������ͬһ���ļ��� 
			   3.�궨�������˴���Ŀɶ��� 
 ***************************************************/ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "book.h"
#include "user.h"
#include "borrow.h"
#include "code.h" 

#define NEW    1
#define LOOK   2
#define EDIT   3
#define DELETE 4
#define FIND   5 
#define BORROW 6
#define RETURN 7 
#define EXIT   0

#define BOOK_PATH   "Book.txt" 
#define USER_PATH   "User.txt"
#define BORROW_PATH "Borrow.txt" 

int main(int argc, char *argv[])
{ 
	 system("color f3");  //����������ɫ
	 
	 login_or_regist_window();
	 
	 printf("\t\t��ͼ�����Ϣ����ϵͳ��\n");
	 read_book(BOOK_PATH);    //��ȡ���ݣ����һ���鱾����
     while(1)
     {
        int instruction;     //����˵�ָ�� 
        main_menu();
        scanf("%d", &instruction);
        switch(instruction)
        {
            case NEW   :	  add_book()        ;       break;	
            case LOOK  :    look_book()       ;       break;	
            case EDIT  :    edit_book()       ;       break; 
			      case DELETE:    delete_book()     ;       break;
			      case FIND  :    find_book_window();       break;
	          case EXIT  :    save_book(BOOK_PATH);     exit(0) ;
	          case BORROW:	  borrow_book(user_name);   break;
	          case RETURN:    return_book(user_name);   break;
            default    :   	printf("��Чָ�\n");
        }
     }
}
