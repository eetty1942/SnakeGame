#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define LENGTH 10
#define MAX_INPUT 10 

static char strFileName[100];		//�����ϴ� ���� �̸� �Է� ����

// �ҷ��� ���� ���� ������ ��� ���� ����
int save_score;
int save_len;
int save_speed;

typedef struct Data		//������� ����� �����͸� �����ϱ� ���� ����ü
{
	char name[LENGTH];
	int score;
}DATA;

//===============�Լ� �����==============================
void RankSort( DATA* pData, int nSize ); 
void Print( DATA* pDAta, int nSize ); 
void SwapData( DATA* pLeft , DATA* pRight); 
void snake();
void save_game(int score, int len, int speed);
int MainMenu();
void leaderboard();
void game_stage();
void menu_square();
void digit_print(int dim[]);
//===============�����Լ� �����==============================
int main(void)
{
	int nMainMenu;

	while(1)
	{
		system("cls");
		nMainMenu = MainMenu();

		switch(nMainMenu)
		{
		case 1:		//�����ϱ�
			system("cls");
			snake();
			break;
		case 2:		//��������
			system("cls");
			leaderboard();
			break;
		case 3:		//����
			return 0;
			break;
		}
	}
	return 0;
}
//===============================Ű�����Է��� �ޱ����� �Լ�===================================
void gotoxy(int x, int y, char  *s)		
{
COORD Pos={x*2,y};	
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
printf("%s",s);

}
//===============���� �Լ� �����==============================
void save_game(int score, int len, int speed)   
{
	FILE *fp;
	int i;
	system("cls");

	printf("================================\n");
	printf("           �� �� �� ��			\n");
	printf("       ������ ���� �մϴ�		\n");
	printf("================================\n");
	printf("\n");
	printf(" ���� ���ϸ��� �Է��ϼ���  (.txt) : ");
	gets(strFileName);
	fflush(stdin);
	fp = fopen(strFileName, "w");	//strFileName�� ����� ���ڿ��� ���ο� �����̸����� �ۼ�
	fprintf(fp, "%d\n%d\n%d\n", score, len, speed);		// ����, ������, �ӵ� �Է�
	fclose(fp);
	getch();		
	system("cls");		// ����ȭ�� �ҷ����� ������
	game_stage();
	gotoxy(1,21,"score : ");		
	printf("%d",score);		
}
void game_stage()		//���� �� Ʋ
{
	int i;
		gotoxy(0,0,"�ââââââââââââââââââââââââââââââ�");	//������
	for(i=1;i<20;i++)
    {
        gotoxy(0,i,"��");
        gotoxy(30,i,"��");
    }
    gotoxy(0,20,"�ââââââââââââââââââââââââââââââ�");
	gotoxy(20,21,"made by S. M. Lee.");
    gotoxy(20, 22, "���� : z  �ҷ����� : x");
}
void menu_square()		// �޴� Ʋ
{
	int i;
		gotoxy(0,0,"������������������������������������������������������������������������������");	//������
	for(i=1;i<22;i++)
    {
        gotoxy(0,i,"��");
        gotoxy(38,i,"��");
    }
    gotoxy(0,22,"������������������������������������������������������������������������������");
	
}
/*======================================================================================*/

int MainMenu()			//���� ���θ޴� ����
{
	int nMenu;
	menu_square();
	gotoxy(12, 5, "Snake Game. ");
	gotoxy(25, 20, "Made by SeungMoo. Lee.");
	gotoxy(12, 8, "1. �����ϱ�");
	gotoxy(12, 10, "2. ��������");
	gotoxy(12, 12, "3. ��    ��");
	gotoxy(14, 18, "�޴��� �����ϼ��� [   ] ");
	gotoxy(24, 18, "");
	scanf("%d", &nMenu);
	fflush(stdin);
	return nMenu;		
}

/*======================================================================================*/ 
void snake()		//�� ����
{
	//���� ���� �� �ʱ�ȭ
	int x[100],y[100],itemx,itemy;
    int len=5,score=0;
    int i=0,dir=-1;
	int last_dir=0;		//���� ���� ���� ���� ����ϴ� ����
    int speed = 150;	
    char name[10];		
    int jumsu;			
	int temp;

	FILE *fp=NULL;	

    system("cls");
    srand(time(NULL));			//���� ���� �ʱ�ȭ

	game_stage();
    for(i=0;i<len;i++)		//�� ����
    {
        x[i]=15+i;
        y[i]=10;
        gotoxy(x[i],y[i],"��");
    }
    itemx=rand()%28+1;	
    itemy=rand()%18+1;
	//������ ��ǥ ������ ����
    gotoxy(1,21,"score : 0");		
	
    while(1)
	{
		if(x[0]==0||x[0]==30||y[0]==0||y[0]==20)		//���� �� �浹
		{
			system("cls");
			printf("================================\n");
			printf("           GAME OVER			\n");
			printf("         �����ϼ̽��ϴ�		\n");
			printf("================================\n");
			printf("\n");
			printf("�̸�:");
			gets(name);
			fp=fopen("score.txt","a+");			//score.txt�� �߰��Ͽ� ���� ���
			fprintf(fp,"%d\t%s\n",score,name); 
			fclose(fp);
			
			break;
		}
		//-----------------------
		for(i=1;i<len;i++)		//���� �ڱ� ������ �浹������
		{
			if(x[0]==x[i]&&y[0]==y[i])
			{
				system("cls");
				printf("================================\n");
				printf("           GAME OVER			\n");
				printf("         �����ϼ̽��ϴ�		\n");
				printf("================================\n");
				printf("\n");
				printf("�̸�:");
				gets(name);
				fp=fopen("score.txt","a+");		//score.txt�� �߰��Ͽ� ���� ���
				fprintf(fp,"%d\t%s\n",score,name); 
				fclose(fp);

				return 0;
			}
		} 
		
		if(x[0]==itemx && y[0]==itemy)				//���� �Ӹ��� ���̿� �浹��
		{
			score=score+10;		//���� �߰� : 10��
			itemx=rand()%28+1;	
	        itemy=rand()%18+1;
			//���ο� ��������ǥ ������ ����
			gotoxy(1,21,"score : ");
			printf("%d",score);		//���� ȭ�� ǥ��
			if(speed >10)		//�ӵ� ����
				speed=speed-5;		
			if(len<100)		//���� ���� ����
			{
				x[len]=x[len-1]; 
				y[len]=y[len-1];   
				len++;    
			}
		}
		gotoxy(itemx,itemy,"��");		//�� ��ǥ�� ���� ǥ��
		if(kbhit())		
		{
			int key;
			do{
				key=getch();		// Ű �Է�
			}while(key==224);
			if(key==72){			//ȭ��ǥ �Ʒ� Ű
				if(last_dir!=1)
				{
					dir=0;
				}
			}
			if(key==80)				//ȭ��ǥ �� Ű
			{
				if(last_dir!=0)
				{
					dir=1;
				}
			}
			if(key==75)				//ȭ��ǥ ���� Ű
			{
				if(last_dir != 3)
				{
					dir=2;
				}
			}
			if(key==77)				//ȭ��ǥ ������ Ű
			{
				if(last_dir!=2)
				{
					dir=3;
				}
			}
			if(key==122) {		// �����ϱ� zŰ
				save_game(score, len, speed);
			}
			if(key==120) {		//�ҷ����� xŰ
				
				system("cls");
				printf("================================\n");
				printf("           �� �� �� ��			\n");
				printf("    ����� ������ �ҷ��ɴϴ�		\n");
				printf("================================\n");
				printf("\n");
				printf(" �ҷ��� ���� �̸� �Է��ϼ���~ (Ȯ���ڴ� .txt) : ");
				gets(strFileName);
				fp = fopen(strFileName, "r");		//strFileName�� ����� �����̸� ã�Ƽ� �б���� �ҷ�����
				fscanf(fp, "%d\n%d\n%d\n", &save_score, &save_len, &save_speed);		//�� ������ ������ ����

				score=save_score;	
				len=save_len;
				speed=save_speed;
				//�� ���ӵ����Ϳ� �ҷ��� ������ ����

				fclose(fp);
				getch();
				system("cls");		// ����ȭ�� �籸��
				gotoxy(1,21,"score : ");		
				printf("%d",score);		
				game_stage();
			}
		}
		if(dir!=-1)		//�̵��� ���� ������ ���� �κ� �����ֱ�
		{
			gotoxy(x[len-1],y[len-1],"  ");
			for(i=len-1;i>0;i--){
				x[i]=x[i-1]; y[i]=y[i-1];
			}
			gotoxy(x[1],y[1],"��");
		}
		if(dir==0) y[0]--;
		if(dir==1) y[0]++;
		if(dir==2) x[0]--;
		if(dir==3) x[0]++;
		//�Է¹��� Ű���� ������ �������� �̵�
		last_dir=dir;		//���� ���� ���� �� ����
		gotoxy(x[0],y[0],"��") ;		//�� �Ӹ�
		Sleep(speed);		//speed��ŭ�� �ʸ�ŭ ���� ������Ų��(speed ���� �������� ���� �����ð��� �������μ� �ӵ� �����ϴ� �� ó�� ���δ�.)
	}
}
/*======================================================================================*/
void leaderboard()		//�������� �Լ�
{
	DATA Input[LENGTH] = { 0 }; 
	FILE* fp = NULL; 
	int  i = 0; 
	fp = fopen("score.txt","r");		//score.txt �ҷ�����
	if( fp == NULL ) 
	{ 
		printf("���� ���� ����\n"); 
	} 
	while( fscanf( fp,"%d%s",&Input[i].score , Input[i].name ) != EOF )		//Data�� �� ���� ������ �Է�
	{ 
		i++; 
	} 
	RankSort( Input, i );	//������ ���� ����
    Print( Input, MAX_INPUT); //���ĵ� ��� ���
	fclose(fp); 
	getch();
}

void RankSort( DATA* pData, int nSize ) 
{ 
   int  i,j;  
   int  nFlag = 0; 

   for( i = 0 ; i < nSize -1 ; i++ ) 
   { 
      nFlag = 0;		// �÷��׸� �̿� �̹� ���� �Ϸ�� ������ �ǳʶٰ� Ž�� ������ �� �ִ�.
      for( j = 0 ; j < nSize - 1 - i ; j++ ) 
      { 
		  if(pData[j].score == pData[j+1].score)
		  {
		  }
		  else {
			  if( pData[j].score < pData[j+1].score ) 
			  { 
				  SwapData( &pData[j],&pData[j+1]); 
				  nFlag = 1; 
			  } 
			  else if( nFlag == 0 )		//���� ���� ����
			  {
				  break; 
			  } 
		  }
      }	      
   } 
} 

void Print( DATA* pData, int nSize )		//���� ���� ���
{ 
   int i = 0; 
   puts("==================================="); 
   puts("========== ���� ���� ============"); 
   puts("");
   puts("======����=====�̸�============"); 
   for( i = 0 ; i< nSize ; i++ )		//���������� �⏋ 
   { 
      printf("%d", i + 1 ); 
      if( pData[i].score != 0 )	//������ �ִ� ����ڿ� ���� ���
      { 
         printf("------%2d \t%s\n",pData[i].score,pData[i].name); 
      } 
      else 
      { 
         printf("\t����� ����\n"); 
      } 
   } 
   puts("==================================="); 
} 

void SwapData( DATA* pLeft , DATA* pRight)		//swap �Լ�
{ 

   DATA sTemp; 
   memmove( &sTemp, pLeft ,sizeof( DATA ) ); 
   memmove( pLeft , pRight ,sizeof( DATA )); 
   memmove( pRight, &sTemp ,sizeof( DATA )); 
}
