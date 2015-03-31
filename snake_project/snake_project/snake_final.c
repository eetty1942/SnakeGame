#include <stdio.h>
#include <windows.h>
#include <malloc.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define LENGTH 10
#define MAX_INPUT 10 

static char strFileName[100];		//저장하는 파일 이름 입력 변수

// 불러온 게임 진행 데이터 담기 위한 변수
int save_score;
int save_len;
int save_speed;

typedef struct Data		//점수기록 저장된 데이터를 저장하기 위한 구조체
{
	char name[LENGTH];
	int score;
}DATA;

//===============함수 선언부==============================
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
//===============메인함수 선언부==============================
int main(void)
{
	int nMainMenu;

	while(1)
	{
		system("cls");
		nMainMenu = MainMenu();

		switch(nMainMenu)
		{
		case 1:		//게임하기
			system("cls");
			snake();
			break;
		case 2:		//순위보기
			system("cls");
			leaderboard();
			break;
		case 3:		//종료
			return 0;
			break;
		}
	}
	return 0;
}
//===============================키보드입력을 받기위한 함수===================================
void gotoxy(int x, int y, char  *s)		
{
COORD Pos={x*2,y};	
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
printf("%s",s);

}
//===============저장 함수 선언부==============================
void save_game(int score, int len, int speed)   
{
	FILE *fp;
	int i;
	system("cls");

	printf("================================\n");
	printf("           저 장 하 기			\n");
	printf("       게임을 저장 합니다		\n");
	printf("================================\n");
	printf("\n");
	printf(" 저장 파일명을 입력하세요  (.txt) : ");
	gets(strFileName);
	fflush(stdin);
	fp = fopen(strFileName, "w");	//strFileName에 저장된 문자열을 새로운 파일이름으로 작성
	fprintf(fp, "%d\n%d\n%d\n", score, len, speed);		// 점수, 몸길이, 속도 입력
	fclose(fp);
	getch();		
	system("cls");		// 게임화면 불러오는 시작점
	game_stage();
	gotoxy(1,21,"score : ");		
	printf("%d",score);		
}
void game_stage()		//게임 벽 틀
{
	int i;
		gotoxy(0,0,"▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣");	//벽생성
	for(i=1;i<20;i++)
    {
        gotoxy(0,i,"▣");
        gotoxy(30,i,"▣");
    }
    gotoxy(0,20,"▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣▣");
	gotoxy(20,21,"made by S. M. Lee.");
    gotoxy(20, 22, "저장 : z  불러오기 : x");
}
void menu_square()		// 메뉴 틀
{
	int i;
		gotoxy(0,0,"┌─────────────────────────────────────┐");	//벽생성
	for(i=1;i<22;i++)
    {
        gotoxy(0,i,"│");
        gotoxy(38,i,"│");
    }
    gotoxy(0,22,"└─────────────────────────────────────┘");
	
}
/*======================================================================================*/

int MainMenu()			//게임 메인메뉴 구성
{
	int nMenu;
	menu_square();
	gotoxy(12, 5, "Snake Game. ");
	gotoxy(25, 20, "Made by SeungMoo. Lee.");
	gotoxy(12, 8, "1. 게임하기");
	gotoxy(12, 10, "2. 순위보기");
	gotoxy(12, 12, "3. 종    료");
	gotoxy(14, 18, "메뉴를 선택하세요 [   ] ");
	gotoxy(24, 18, "");
	scanf("%d", &nMenu);
	fflush(stdin);
	return nMenu;		
}

/*======================================================================================*/ 
void snake()		//뱀 게임
{
	//변수 선언 및 초기화
	int x[100],y[100],itemx,itemy;
    int len=5,score=0;
    int i=0,dir=-1;
	int last_dir=0;		//방향 역행 막기 위해 사용하는 변수
    int speed = 150;	
    char name[10];		
    int jumsu;			
	int temp;

	FILE *fp=NULL;	

    system("cls");
    srand(time(NULL));			//난수 생성 초기화

	game_stage();
    for(i=0;i<len;i++)		//몸 생성
    {
        x[i]=15+i;
        y[i]=10;
        gotoxy(x[i],y[i],"○");
    }
    itemx=rand()%28+1;	
    itemy=rand()%18+1;
	//먹이의 좌표 무작위 생성
    gotoxy(1,21,"score : 0");		
	
    while(1)
	{
		if(x[0]==0||x[0]==30||y[0]==0||y[0]==20)		//뱀이 벽 충돌
		{
			system("cls");
			printf("================================\n");
			printf("           GAME OVER			\n");
			printf("         수고하셨습니다		\n");
			printf("================================\n");
			printf("\n");
			printf("이름:");
			gets(name);
			fp=fopen("score.txt","a+");			//score.txt에 추가하여 점수 기록
			fprintf(fp,"%d\t%s\n",score,name); 
			fclose(fp);
			
			break;
		}
		//-----------------------
		for(i=1;i<len;i++)		//뱀이 자기 꼬리에 충돌했을때
		{
			if(x[0]==x[i]&&y[0]==y[i])
			{
				system("cls");
				printf("================================\n");
				printf("           GAME OVER			\n");
				printf("         수고하셨습니다		\n");
				printf("================================\n");
				printf("\n");
				printf("이름:");
				gets(name);
				fp=fopen("score.txt","a+");		//score.txt에 추가하여 점수 기록
				fprintf(fp,"%d\t%s\n",score,name); 
				fclose(fp);

				return 0;
			}
		} 
		
		if(x[0]==itemx && y[0]==itemy)				//뱀의 머리가 먹이와 충돌시
		{
			score=score+10;		//점수 추가 : 10점
			itemx=rand()%28+1;	
	        itemy=rand()%18+1;
			//새로운 먹이의좌표 무작위 생성
			gotoxy(1,21,"score : ");
			printf("%d",score);		//점수 화면 표시
			if(speed >10)		//속도 증가
				speed=speed-5;		
			if(len<100)		//몸의 길이 증가
			{
				x[len]=x[len-1]; 
				y[len]=y[len-1];   
				len++;    
			}
		}
		gotoxy(itemx,itemy,"♤");		//새 좌표에 먹이 표시
		if(kbhit())		
		{
			int key;
			do{
				key=getch();		// 키 입력
			}while(key==224);
			if(key==72){			//화살표 아래 키
				if(last_dir!=1)
				{
					dir=0;
				}
			}
			if(key==80)				//화살표 위 키
			{
				if(last_dir!=0)
				{
					dir=1;
				}
			}
			if(key==75)				//화살표 왼쪽 키
			{
				if(last_dir != 3)
				{
					dir=2;
				}
			}
			if(key==77)				//화살표 오른쪽 키
			{
				if(last_dir!=2)
				{
					dir=3;
				}
			}
			if(key==122) {		// 저장하기 z키
				save_game(score, len, speed);
			}
			if(key==120) {		//불러오기 x키
				
				system("cls");
				printf("================================\n");
				printf("           불 러 오 기			\n");
				printf("    저장된 게임을 불러옵니다		\n");
				printf("================================\n");
				printf("\n");
				printf(" 불러올 파일 이름 입력하세요~ (확장자는 .txt) : ");
				gets(strFileName);
				fp = fopen(strFileName, "r");		//strFileName에 저장된 파일이름 찾아서 읽기모드로 불러오기
				fscanf(fp, "%d\n%d\n%d\n", &save_score, &save_len, &save_speed);		//각 변수에 데이터 저장

				score=save_score;	
				len=save_len;
				speed=save_speed;
				//각 게임데이터에 불러온 데이터 저장

				fclose(fp);
				getch();
				system("cls");		// 게임화면 재구성
				gotoxy(1,21,"score : ");		
				printf("%d",score);		
				game_stage();
			}
		}
		if(dir!=-1)		//이동한 뱀의 마지막 꼬리 부분 지워주기
		{
			gotoxy(x[len-1],y[len-1],"  ");
			for(i=len-1;i>0;i--){
				x[i]=x[i-1]; y[i]=y[i-1];
			}
			gotoxy(x[1],y[1],"○");
		}
		if(dir==0) y[0]--;
		if(dir==1) y[0]++;
		if(dir==2) x[0]--;
		if(dir==3) x[0]++;
		//입력받은 키값을 지정된 방향으로 이동
		last_dir=dir;		//역행 방지 조건 값 저장
		gotoxy(x[0],y[0],"■") ;		//뱀 머리
		Sleep(speed);		//speed만큼의 초만큼 실행 지연시킨다(speed 값이 줄음으로 인해 지연시간이 줄음으로서 속도 증가하는 것 처럼 보인다.)
	}
}
/*======================================================================================*/
void leaderboard()		//순위보기 함수
{
	DATA Input[LENGTH] = { 0 }; 
	FILE* fp = NULL; 
	int  i = 0; 
	fp = fopen("score.txt","r");		//score.txt 불러오기
	if( fp == NULL ) 
	{ 
		printf("파일 열기 실패\n"); 
	} 
	while( fscanf( fp,"%d%s",&Input[i].score , Input[i].name ) != EOF )		//Data에 각 정보 데이터 입력
	{ 
		i++; 
	} 
	RankSort( Input, i );	//개선된 버블 정렬
    Print( Input, MAX_INPUT); //정렬된 결과 출력
	fclose(fp); 
	getch();
}

void RankSort( DATA* pData, int nSize ) 
{ 
   int  i,j;  
   int  nFlag = 0; 

   for( i = 0 ; i < nSize -1 ; i++ ) 
   { 
      nFlag = 0;		// 플래그를 이용 이미 정렬 완료된 내용은 건너뛰고 탐색 정렬할 수 있다.
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
			  else if( nFlag == 0 )		//정렬 종료 조건
			  {
				  break; 
			  } 
		  }
      }	      
   } 
} 

void Print( DATA* pData, int nSize )		//점수 순위 출력
{ 
   int i = 0; 
   puts("==================================="); 
   puts("========== 명예의 전당 ============"); 
   puts("");
   puts("======점수=====이름============"); 
   for( i = 0 ; i< nSize ; i++ )		//순차적으로 출룍 
   { 
      printf("%d", i + 1 ); 
      if( pData[i].score != 0 )	//점수가 있는 기록자에 한해 출력
      { 
         printf("------%2d \t%s\n",pData[i].score,pData[i].name); 
      } 
      else 
      { 
         printf("\t기록자 없음\n"); 
      } 
   } 
   puts("==================================="); 
} 

void SwapData( DATA* pLeft , DATA* pRight)		//swap 함수
{ 

   DATA sTemp; 
   memmove( &sTemp, pLeft ,sizeof( DATA ) ); 
   memmove( pLeft , pRight ,sizeof( DATA )); 
   memmove( pRight, &sTemp ,sizeof( DATA )); 
}
