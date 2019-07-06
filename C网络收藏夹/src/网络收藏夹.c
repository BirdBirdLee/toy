#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#define PATH "Urls.txt"

/*****************************************
��д�ˣ������ 
����  ��������ַ���� 
�汾 ��1.0 
****************************************/

typedef struct Url
{
	char caption[50];   //���˵�� 
	char url[100];		//��ַ 
	char details[300];	//��ϸ˵�� 
}Url;

Url urls[500];

int url_n = 0;

void read_url(const char filename[]); //��ȡ��Ϣ 
char* delete_huiche(char *str);		//ɾ���ַ����س� 
void help_menu();
void save_url(const char filename[]);
void add_url();		//�����ַ
void open_url(int num);    //����ַ 
void edit_url(int num);	//�޸���ַ 
void move_url(int num1, int num2);//�ƶ���ַ 
void delete_url(int num); //ɾ����ַ 
void print_all_url();   //��ӡ������ַ 


int main()
{
	system("color f3"); 
	read_url(PATH);
	//printf("%s", urls[2].caption);
	char instruction;
	while(1)
	{
		int num = 0;
		print_all_url();
		puts("\n������ָ��(��Ҫ���������뷨),��h�鿴����: ");
		instruction = getch();
		//putchar(instruction);
		switch(instruction)
		{
			case 'A':
			case 'a':	add_url();	break;
			case 'E':
			case 'e':
			{
				scanf("%d", &num);
				edit_url(num);
				break;
			}
			case 'O':
			case 'o':
			{
				scanf("%d", &num);
				open_url(num);
				break;
			}
			case 'D':
			case 'd':
			{
				scanf("%d", &num);
				delete_url(num); 
				break;
			}
			case 'M':
			case 'm':
			{
				int num1, num2;
				scanf("%d%d", &num1, &num2);
				move_url(num1, num2);
				break;
			}
			case 'Q':
			case 'q': exit(0);	 break;
			case 'H':
			case 'h': help_menu(); Sleep(5000);	 break;
			default : puts("��Чָ��!"); break;
		}
		Sleep(1000);
		system("cls");
	}
	//system("explorer http://www.baidu.com"); 
	return 0;
}

void read_url(const char filename[])
{
	int i = 0, j;
	FILE *fp;
 	if(!(fp=fopen(filename,"r")))
  	{
     	printf("failed to open!\n");
     	exit(0);
   	} 
   	while(!feof(fp))
    {
     	i++;
     	fgets(urls[i].caption, 50, fp);
     	//printf("111%s\n", urls[i].caption);
	 	fgets(urls[i].url, 		100, fp);
	 	//printf("111%s\n", urls[i].url);
	 	fgets(urls[i].details,  300, fp);
	 	//printf("111%s\n", urls[i].details);
	 	strcpy(urls[i].caption , delete_huiche(urls[i].caption));
	 	strcpy(urls[i].url , delete_huiche(urls[i].url));
	 	//printf("222%s\n", urls[i].url);
	 	strcpy(urls[i].details , delete_huiche(urls[i].details));
	 	//printf("222%s\n", urls[i].details);
		  	
    }
    fclose(fp); 
    url_n = i - 1; //�����������Զ�и����У����Լ�ȥһ 
}

void add_url()
 {
 	url_n++;            //��ַ���������� 1 
	printf("��������ַ������:\n");
	gets(urls[url_n].caption);			
	printf("������������ַ(http��ͷ):\n");
	gets(urls[url_n].url);
	printf("��������ַ��ϸ��Ϣ:\n");
	gets(urls[url_n].details) ;
	printf("��ַ��ӳɹ�!\n");
	save_url(PATH);
 }
 
 void open_url(int num)
 {
 	char Original[] = "explorer ";
 	if(!(num>=1 && num<=url_n))
	{
		printf("�����ڸ������ַ!\n");
	 	return;
	}
	char str[60];
	strcpy(str, Original);
	strcat(str, urls[num].url);
	system(str); // ����ַ
 }
 
 void edit_url(int num)
 {
 		getchar();
 		if(!(num>=1 && num<=url_n))
 		{
	 		printf("�����ڸ������ַ!\n");
	 		return;
		 }
		printf("��������%s\n", urls[num].caption);
		printf("������ַ��%s\n", urls[num].url);
		printf("��ϸ��Ϣ��%s\n", urls[num].details);
		char caption_temp[50], url_temp[100], details_temp[300];
		puts("��Ҫ����������Ϊ(s����):");
		gets(caption_temp);
		if(strcmp(caption_temp, "s"))
			strcpy(urls[num].caption, caption_temp);
		puts("��Ҫ��������ַ��Ϊ(s����):");
		gets(url_temp);
		if(strcmp(url_temp, "s"))
			strcpy(urls[num].url, url_temp);
		puts("��Ҫ����ϸ��Ϣ��Ϊ(s����):");
		gets(details_temp);
		if(strcmp(details_temp, "s"))
			strcpy(urls[num].details, details_temp);
		puts("��ַ�޸ĳɹ�!");
		save_url(PATH);
 }
 
 void move_url(int num1, int num2)
 {
 	if((!(num1>=1 && num1<=url_n))||(!(num2>=1 && num2<=url_n)))
 	{
	 	printf("�����ڸ������ַ!\n");
	 	return;
	 }
 	Url url_temp = urls[num1];
	int i;
 	if(num1>=num2)
 	{
 		for(i=num1; i>= num2+1; i--)
	 		urls[i] = urls[i-1];
	 }
	 else
	 {
 		for(i=num1; i<=num2-1; i++)
 			urls[i] = urls[i+1];	
 	}
 	urls[num2] = url_temp;
 	printf("�ƶ��ɹ�!\n");
 	save_url(PATH);
 }
 
 void delete_url(int num)
 {
 	if(!(num>=1 && num<=url_n))
	{
	 	printf("�����ڸ������ַ!\n");
	 	return;
	 }
 	printf("��������%s\n", urls[num].caption);
	printf("������ַ��%s\n", urls[num].url);
	printf("��ϸ��Ϣ��%s\n", urls[num].details);
	puts("��yȷ��ɾ��, nȡ��");
	getchar();
	char instruction = getch();
	int i;
	if('y' == instruction)
	{
		for(i=num; i<url_n; i++)
			urls[i] = urls[i+1];
		url_n--;
		puts("ɾ���ɹ�!");
	}
	else if('n' == instruction)
		puts("ȡ��ɾ��");
	else
		puts("��Чָ��!");
	save_url(PATH);
 }

void save_url(const char filename[])
 {
 	int i;
 	FILE* fp=fopen(filename,"w");
	
 	if(fp == NULL)
  	{
     	printf("error\n");
     	exit(0);
   	} 
   	
    for(i=1; i<=url_n; i++)
    {
    	fprintf(fp, "%s\n", urls[i].caption);
    	fprintf(fp, "%s\n", urls[i].url);
    	fprintf(fp, "%s\n", urls[i].details);
   	}
    fclose(fp);
 }

char* delete_huiche(char *str)
{
	char  str2[50];
	char *p1 = str, *p2 = str2;
	while(*p1 != '\0')
	{
		if(*p1 != '\n')
			{
				*p2 = *p1;
				p2 ++;
			}
		p1 ++;
	}
	*p2 = '\0';
	return str2;
}

void print_all_url()
{
	int i;
	printf("���\t������\t\t\t��ϸ��Ϣ\n");
	for(i=1; i<=url_n; i++)
		printf("%d\t%s\t\t\t%s\n", 
				i, urls[i].caption, urls[i].details);
}

void help_menu()
 {
 	printf(" ------------------------------------------------ \n");
 	printf("|             ����                               |\n");
  	printf("|    a              ���(add)   ��ַ             |\n");
	printf("|    o ����         ��(open)  ��ַ(�ո��ʡ)   |\n");
	printf("|    e ����         �༭(edit)  ��ַ(�ո��ʡ)   |\n");
	printf("|    d ����         ɾ��(delete)��ַ(�ո��ʡ)   |\n");
	printf("|    m ����1 ����2  �ƶ�������1����ַ��������2�� |\n");
	printf("|    q              �˳�(quit)������             |\n");
	printf(" ------------------------------------------------ \n");
 } 
