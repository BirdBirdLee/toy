#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define MAX_MAP_ROW 16
#define MAX_MAP_COLUM 40
#define SLEEP_TIME 1000
#define UP    'w'
#define DOWN  's'
#define LEFT  'a'
#define RIGHT 'd'
 
/*

#define UP    (char)(0x4b)
#define DOWN  (char)(0x48)
#define LEFT  (char)(0x4d)
#define RIGHT (char)(0x50)

*/ 


/*****************
�������ƣ�̰ʳ�� 
�����ˣ�  ����� 
�汾��:   1.0 
******************/

/************************************
������־�� 1.0 ��������

************************************/ 

 

enum types{blank, body, food, wall_row, wall_colum};
enum types type;

char map[MAX_MAP_ROW][MAX_MAP_COLUM];
int snake_x[MAX_MAP_ROW*MAX_MAP_COLUM];
int snake_y[MAX_MAP_ROW*MAX_MAP_COLUM];
int length;
int food_x, food_y;
int sleep_time = SLEEP_TIME;
char direction; 
char cursor[6] = " *o$$";

void load_map();  //���ص�ͼ 
void gotoxy(int x,int y);//��������ƶ�
void print_snake(); //����� 
void move();        //�ƶ� 
int game_over();    //�ж��Ƿ�ײǽ��ײ���� 
void eat();         //����ʳ���һϵ�в��� 
 
int main()
{
	system("color f3");
	int i, j = 1;
	srand(time(NULL));
	length = 1;
	snake_x[0] = rand()%(MAX_MAP_COLUM-2)+1;
			//�������x�����Ҳ��ڵ�ͼ��Ե�� 
 	snake_y[0] = rand()%(MAX_MAP_ROW-2)+1;
	food_x  = rand()%(MAX_MAP_COLUM-2)+1;
	food_y  = rand()%(MAX_MAP_ROW-2)+1;
	i = rand()%4 + 1;            //��ʼ������
	if(i==1) 	  direction = UP;
	else if(i==2) direction = DOWN;
	else if(i==3) direction = LEFT;
	else if(i==4) direction = RIGHT;
	
	load_map();
	
 	while(1)
 	{
	 	print_snake();	
 		for(i=0; i<20; i++)
 		{
		 	if(kbhit())
		 	{
		 		direction = getch();
		 		if(direction==UP||direction==DOWN||direction==LEFT||direction==RIGHT)  //��λ 
		 		{
		 			j = 0;
		 			move();
		 			if(game_over()) //������� 
 					{
		 				gotoxy(MAX_MAP_COLUM/2-4,MAX_MAP_ROW/2);
		 				puts("game over!");//�������game over
		 				break;
	 				}
	 				eat();
	 				print_snake(); 
		 		}
 				 
 		 	} 
		 }
 		if(j) move();
 		j = 1;
 		print_snake();
 		if(game_over()) //������� 
 		{
 			gotoxy(MAX_MAP_COLUM/2-4,MAX_MAP_ROW/2);
		 	puts("game over!");   //�������game over
			system("pause"); 
		 	break;
	 	}
	 	eat();
	 	Sleep(sleep_time);  //ͣ�� 
	 }
	 return 0;
	  
}

void load_map()
{
	int i, j;
	for(i=0; i<MAX_MAP_ROW; i++)
	{
		for(j=0; j<MAX_MAP_COLUM; j++)
		{
			map[i][j] = cursor[(type=blank)];
		}
	}
	for(i=1; i<MAX_MAP_COLUM-1; i++)
		map[0][i] = cursor[(type=wall_row)];
	for(i=1; i<MAX_MAP_COLUM-1; i++)
		map[MAX_MAP_ROW-1][i] = cursor[(type=wall_row)];
	for(i=1; i<MAX_MAP_ROW-1; i++)
		map[i][0] = cursor[(type=wall_colum)];
	for(i=1; i<MAX_MAP_ROW-1; i++)
		map[i][MAX_MAP_COLUM-1] = cursor[(type=wall_colum)];
		
	for(i=0; i<MAX_MAP_ROW; i++)
	{
		for(j=0; j<MAX_MAP_COLUM; j++)
		{
			printf("%c",map[i][j]);
		}
		putchar('\n');
	}
}

void print_snake()
{
	int i;
	for(i=0; i<length; i++)
	{
		gotoxy(snake_x[i], snake_y[i]);
		printf("\b%c",cursor[(type=body)]); 
				//�˸������ �൱�ڰѵ�ͼ�Ŀո�ĳ����� 
	}
	gotoxy(snake_x[i], snake_y[i]);
	printf("\b%c",cursor[(type=blank)]);
	gotoxy(food_x, food_y);
	printf("\b%c",cursor[(type=food)]);
	gotoxy(0,MAX_MAP_ROW);
}
void gotoxy(int x,int y)
{
	COORD pos = {x, y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
}//�������ƶ������ٶȵ� x��y��

void eat()
{
	int i;
	if(snake_x[0]==food_x && snake_y[0]==food_y)
	{
	 	length ++;
	 	gotoxy(food_x, food_y);
		printf("\b%c",cursor[(type=body)]);
		gotoxy(0,MAX_MAP_ROW);
		food_x  = rand()%(MAX_MAP_COLUM-2)+1;
		food_y  = rand()%(MAX_MAP_ROW-2)+1;
		sleep_time = (int)(sleep_time*0.95);
	}
}

void move()
{
	int i;
	gotoxy(snake_x[length-1], snake_y[length-1]); 
	printf("\b%c",cursor[(type=blank)]);//��ȥβ�� 
	for(i=length-1; i>0; i--)
	{
		snake_x[i] = snake_x[i-1]; //����ǰ 
		snake_y[i] = snake_y[i-1]; 
	}
	switch(direction)
	{
		case UP:
		{
			snake_y[0] --; 
			break;
		}
		case DOWN:
		{
			snake_y[0] ++; 
			break;
		}
		case LEFT:
		{
			snake_x[0] --; 
			break;
		}
		case RIGHT:
		{
			snake_x[0] ++; 
			break;
		}
	}
	print_snake();
}

int game_over()
{
	int i, judge = 0;     //���judgeΪ 1 �ʹ���gameover 
	for(i=1; i<length; i++) //ȥ��ͷ 
	{
		if(snake_x[0]==snake_x[i] && snake_y[0]==snake_y[i])
							//�ж�ͷ�Ƿ�Ӵ����� 
		{
			judge = 1;
			break;
		}
	}
	if(snake_x[0]==0||snake_x[0]==MAX_MAP_COLUM-1||snake_y[0]==0||snake_y[0]==MAX_MAP_ROW-1)
	                       //�ж�ͷ�Ƿ�ײ��ͼ 
		judge = 1;
		
	return judge;
}
