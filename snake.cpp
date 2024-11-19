#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include "windows.h"
using namespace std;
void gotoxy( int column, int line );
void SetColor(WORD color);
void ShowCur(bool CursorVisibility);


struct Point{
public:
    int x,y;
    boolean sosanhbang(Point a)
    {
        if ( x==a.x && y==a.y) return true;
        else return false;
    }
};

class CONRAN{
public:
    struct Point A[100];
    int DoDai;
    int effect;
    CONRAN(){
        DoDai = 3;
        A[0].x = 15; A[0].y = 10;
        A[1].x = 14; A[1].y = 10;
        A[2].x = 13; A[2].y = 10;
        A[DoDai].x = 12; A[DoDai].y = 10;
        effect=0;

    }

    void Ve()
    {   
        if (effect!=1)
        {
            for (int i = 0; i < DoDai; i++)
            {
                gotoxy(A[i].x,A[i].y);
                cout<<"X";
            }
        }
        else
        {
            for (int i = 0; i < DoDai; i++)
            {
                int c;
                srand(time(NULL));
                c=rand()%(15-1+1)+1;
                gotoxy(A[i].x,A[i].y);
                SetColor(c);
                cout<<"X";
            }
        }
        gotoxy(A[DoDai].x,A[DoDai].y);
        cout<<" ";

        
  
    }

    void xoa()
    {
        A[DoDai].x=A[DoDai-1].x;
        A[DoDai].y=A[DoDai-1].y;
    }

    void DiChuyen(int Huong)
    {
        
        for (int i = DoDai-1; i>0;i--)
            A[i] = A[i-1];
        if (Huong==0) A[0].x = A[0].x + 1;
        if (Huong==1) A[0].y = A[0].y + 1;
        if (Huong==2) A[0].x = A[0].x - 1;
        if (Huong==3) A[0].y = A[0].y - 1;

    }

    boolean gameover()
    {
        for(int i=1; i<DoDai; i++)
        {
            if ( A[0].sosanhbang(A[i]) ) 
            {
                return false;
            }
        }
        if(effect!=1)
        {
            if( A[0].x==99 ||  A[0].x==1 || A[0].y==1 || A[0].y==26  )
            {
                return false;
            }
        }
        else 
        {
            if (A[0].x==99) A[0].x=2;
            else if (A[0].x==1) A[0].x=98;
            else if (A[0].y==1) A[0].y=25;
            else if (A[0].y==26) A[0].y=2;
        }
        return true;
    }

    void qua(Point &a, int i, Point b)
    {
        if(i==0)
        {
            srand(time(NULL));
            a.x=rand()%(98-2+1)+2;
            a.y=rand()%(25-2+1)+2;
            for(int i=1; i<DoDai; i++)
            {
                if(a.sosanhbang(A[i]) || a.sosanhbang(b))
                {
                    qua(a,i,b);           
                }
            }
            gotoxy(a.x,a.y);
            cout<<"$";  
        }
        else 
        {
            srand(time(NULL)+3);
            a.x=rand()%(98-2+1)+2;
            a.y=rand()%(25-2+1)+2;
            for(int i=1; i<DoDai; i++)
            {
                if(a.sosanhbang(A[i]) || a.sosanhbang(b))
                {
                    qua(a,i,b);          
                }
            }
            gotoxy(a.x,a.y);
            SetColor(4);
            cout<<"+";
            SetColor(15);
        }
    }

    void hieuung(Point &a,int& b, int &s, Point c)
    {
        
        if(a.sosanhbang(A[0]))
        {
            effect=1;
            s=1;
        }



        if(s==1 && DoDai%10==0)
        {
            qua(a,1,c);
            DoDai++;
            b=0;
            s=0;
        }

        int z=DoDai%15;
        if (z==0) z++;
    }

    void anmoi(Point &a, Point b)
    {
        if(A[0].sosanhbang(a))
        {
            DoDai++;   
            qua(a,0, b);
        }
    }
    
    void tocdo()
    {
        if(effect!=1) Sleep(100);
        else Sleep(10);
    }

};


void vetuong();


int main()
{
    CONRAN r;
    int s=1,Huong = 0;
    char t;
    int Huong2;
    Point x, y;
    vetuong();
    r.qua(x,0,r.A[0]);
    int b=0;
    while (r.gameover())
    {
        if (kbhit()){
            Huong2=Huong;
            t = getch();
            if (t=='a' && Huong2!=0 ) Huong = 2;
            else if (t=='w' && Huong2!=1) Huong = 3;
            else if (t=='d' && Huong2!=2) Huong = 0;
            else if (t=='s'&& Huong2!=3) Huong = 1;
            else if (t==-32)
            {
                t=getch();
                if (t==75 && Huong2!=0) Huong = 2;
                else if (t==72 && Huong2!=1) Huong = 3;
                else if (t==77 && Huong2!=2) Huong = 0;
                else if (t==80 && Huong2!=3) Huong = 1;
            }
        }
        //system("cls");
        r.Ve();
        r.xoa();
        r.DiChuyen(Huong);
        r.anmoi(x,y);
        ShowCur(false);
        r.tocdo();
        r.hieuung(y,b,s,x);
        b++;
        if(b==1000) r.effect=0;
    }
    SetColor(15);
    gotoxy(1,30);
    cout<<"GAME OVER";
    return 0;
}


void gotoxy( int column, int line )
{
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
}

void vetuong()
{
    for (int i = 1; i < 100; i++)
    {
        gotoxy(i,1);
        cout<<"v";
    }
    for (int i = 1; i < 100; i++)
    {
        gotoxy(i,26);
        cout<<"^";
    }
    for (int i = 2; i < 27; i++)
    {
        gotoxy(1,i);
        cout<<">";
    }
    for (int i = 2; i < 27; i++)
    {
        gotoxy(99,i);
        cout<<"<";
    }
}

void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//============== làm ẩn trỏ chuột ===========
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}