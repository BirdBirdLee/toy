#ifndef _ZZZ_USER_H___
#define _ZZZ_USER_H___

typedef struct User
{
	char id[30];        //�û�id 
	char password[30];  //�û����� 
}User;

extern User users[500];

extern int user_n;
extern char user_name[30];   //��ǰ�û����� 

void read_user(const char filename[]);  //��ȡ�û���¼
void save_user(const char filename[]);  //�����û���¼
int is_vaild_user(const char* user_id); //�Ƿ���ڸ��û�
void login_or_regist_window();          //��¼��ע�ᴰ��  
int login();                            //��¼ 
void regist();                          //ע��  

#endif //_ZZZ_USER_H___

