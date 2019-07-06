#include "user.h"
#include "borrow.h"
#include "book.h"
#include "code.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define USER_PATH   "User.txt"

int book_n ;
int user_n = 0;
char user_name[30];   //��ǰ�û����� 

User users[500];
Book books[1000];

void read_user(const char filename[])
{
	char content[100];
	int i = 0;
	FILE *fp_user;
 	if(!(fp_user=fopen(USER_PATH,"r")))
  	{
     	printf("error to open user");
     	exit(0);
   	} 
   	fgets(content,100,fp_user);  //�ѵ�һ�ж��� 
   	while(!feof(fp_user))
    {
     	i++;
     	fscanf(fp_user,"%d%s%s", &user_n, 
								 users[i].id, 
								 users[i].password );
     	strcpy(users[i].password, decode(users[i].password)); //���� 
    }
    fclose(fp_user); 
}

 
 void save_user(const char filename[])
 {
 	int i;
 	FILE* fp_user = fopen(filename,"w");
 	if(fp_user == NULL)
  	{
     	printf("error");
     	exit(0);
   	}
   	fprintf(fp_user,"���\t�û���(id)\t\t����\t\t\n") ;
   	
    for(i=1; i<=user_n; i++)
    {
		fprintf(fp_user,"%d\t%s\t\t%s\t\t\n",
	 					i, 
	 					users[i].id, 
	 					encode(users[i].password));
   	}
    fclose(fp_user);
 }
 
 int is_vaild_user(const char* user_id)
 {
 	int i;
  	for(i=1; i<=user_n; i++)
  	{
		if(strcmp(user_id, users[i].id)==0)
			return 1;  	
  	}
  	return 0;
 }
 
 User* get_user(const char* user_id)
 {
	int i;
  	for(i=1; i<=user_n; i++)
  	{
		if(strcmp(user_id, users[i].id)==0)
			return users+i;  	
  	}
  	return NULL;
 }
 
 
 void login_or_regist_window()
 {
 	read_user(USER_PATH);
	 while(1)
	 {
	 	int instruction;
	 	printf("1.��¼ 2.ע�� �����˳�������\n");
	 	scanf("%d", &instruction);
	 	if(instruction == 1)
	 	{
	 		if(login())   //�Ƿ��¼�ɹ�
		 	{
 				printf("��¼�ɹ�!\n");
 				Sleep(500);  //�ӳٰ���
 				system("cls");//���� 
 				return;
 			} 
 			else 
			{
				printf("��¼ʧ�ܣ��Զ������ϼ��˵�\n");
 				Sleep(500);  //�ӳٰ���
 				system("cls");//���� 
			}			
	 	}
	 	else if(instruction == 2)
	 	{
 			regist();
 			Sleep(500);  //�ӳٰ���
 			system("cls");//���� 
 		} 
 		else
 			exit(0);	 
 	 }
 }
 
 int login(char filename[])
 {
 	int i, login_state = 0;
 	char user_id[30], password[30]; 
 	User *user = NULL;
 	printf("���������id(�û���):\n");
 	scanf("%s", user_id);
 	
 	if(is_vaild_user(user_id)!=1)
 	{
		printf("���û�������\n"); 	
 	}
 	else
 	{
 		user = get_user(user_id);
 		for(i=0; i<3; i++)    //���λ����������� 
 		{
		 	printf("�������������:\n");
	 		scanf("%s", password);
	 		if(strcmp(password, user->password)==0)
	 		{
		 		login_state = 1; 
		 		strcpy(user_name, user_id);//���浱ǰ�û����� 
		 		return login_state;
		 	}	
	 	}
		 printf("�������������������!\n");	
 	}
 	return login_state;    //�����Ƿ��¼�ɹ� 
 }
 
 void regist()
 {
 	printf("��������ע����û���(id):\n");
 	char user_id[30], password1[30], password2[30];
 	scanf("%s", user_id);
 	User *user = NULL;
 	if(is_vaild_user(user_id)==1)
 	{
	 	printf("���û��Ѵ��ڣ�\n");
	 	return;
 	}
 	printf("����������:\n");
 	scanf("%s",password1);
 	printf("���ٴ���������:\n");
 	scanf("%s",password2);
 	if(strcmp(password1,password2)==0)
 	{
	 	user_n++;
	 	strcpy(users[user_n].id, user_id); 
	 	strcpy(users[user_n].password, password1);
	 	printf("ע��ɹ���\n");
	 	strcpy(user_name, user_id);
	 	save_user(USER_PATH);
 	}		
	else
 		printf("�������벻һ�£�ע��ʧ�ܣ�\n");
	Sleep(500);
	system("cls"); 
 }
