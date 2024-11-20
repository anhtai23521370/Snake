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
void colorbg(int color); //hàm tô màu nền
void vetuong();
void tomau(int x, int y);
void G(int x, int y);
void A(int x, int y);
void M(int x, int y);
void E(int x, int y);
void O(int x, int y);
void V(int x, int y);
void R(int x, int y);
boolean dk();
void play();
boolean gover();


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





int main()
{
    int i=1;
    while(i)
    {
        system("cls");
        play();
        if (gover()) i=1;
        else i=0;
    }
    
    return 0;
}

boolean gover()
{
    system("cls");
    SetColor(15);
    G(22,5);
    A(31,5);
    M(40,5);
    E(49,5);
    O(61,5);
    V(70,5);
    E(79,5);
    R(88,5);
    gotoxy(54,16);
    colorbg(0);
    cout<<"PLAY AGAIN ?";
    gotoxy(50, 18);
    colorbg(3);
    cout<<"YES";
    gotoxy(67,18);
    colorbg(0);
    cout<<"NO";
    if (dk() ) return true;
    else return false;
}

void play()
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

void colorbg(int color) {
    // Lấy handle của cửa sổ console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Lấy thông tin hiện tại của console
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    // Thay đổi màu nền mà không thay đổi màu văn bản
    WORD colorAttributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(hConsole, (color << 4) | (colorAttributes & 0x0F));
}

void tomau(int x, int y)
{
    if (y==5)
    {
        gotoxy(x,y);
        colorbg(15);
        cout<<" "<<endl;
    }
    else if (y==6 )
    {
        gotoxy(x,y);
        colorbg(11);
        cout<<" "<<endl;
    }
    else if (y==7 )
    {
        gotoxy(x,y);
        colorbg(3);
        cout<<" "<<endl;
    }
    else if (y==8)
    {
        gotoxy(x,y);
        colorbg(9);
        cout<<" "<<endl;
    }
    else if (y==9)
    {
        gotoxy(x,y);
        colorbg(1);
        cout<<" "<<endl;
    }
    else if (y==10)
    {
        gotoxy(x,y);
        colorbg(1);
        cout<<" "<<endl;
    }
}

void G(int x, int y)
{
    for(int i=0; i<6; i++)
    {
         tomau(x+1+i, y);
         
         tomau(x+1+i, y+5);
         
    }
    for(int i=0; i<4; i++)
    {
         tomau(x,y+1+i);
         
         tomau(x+1,y+1+i);
         
    }
     tomau(x+7, y+1);
     
     tomau(x+6, y+1);
     

     tomau(x+5, y+3);
     
     tomau(x+6, y+3);
     

     tomau(x+7, y+4);
     
     tomau(x+6, y+4);
     

     tomau(x+1, y);
     
     tomau(x+7, y+3);
     
    
}

void A(int x, int y)
{
    for(int i=0; i<4; i++)
    {
         tomau(x+2+i,y);
         
         tomau(x+2+i, y+3);
         
    }

    for(int i=0; i<4; i++)
    {
         tomau(x,y+2+i);
         
         tomau(x+1,y+2+i);
         
         tomau(x+7,y+2+i);
         
         tomau(x+6,y+2+i);
         
    }

     tomau(x+1,y+1);
     
     tomau(x+2, y+1);
     
     tomau(x+5,y+1);
     
     tomau(x+6, y+1);
     
}

void M(int x, int y)
{
    for(int i=0; i<5; i++)
    {
         tomau(x,y+1+i);
         
         tomau(x+1,y+1+i);
         
         tomau(x+7,y+1+i);
         
         tomau(x+6,y+1+i);
         
    }
     tomau(x,y);
     
     tomau(x+7,y);
     
     tomau(x+2,y+1);
     
     tomau(x+5,y+1);
     
     tomau(x+4,y+2);
     
     tomau(x+3,y+2);
     

}

void E(int x, int y)
{
    for(int i=0; i<6; i++)
    {
         tomau(x,y+i);
         
         tomau(x+1,y+i);
             
    }
    for(int i=0; i<6; i++)
    {
         tomau(x+2+i,y);
         
         tomau(x+2+i,y+2);
         
         tomau(x+2+i,y+5);
         
    }
}

void O(int x, int y)
{
    for(int i=0; i<6; i++)
    {
         tomau(x+1+i, y);
         
         tomau(x+1+i, y+5);
         
    }
    for(int i=0; i<4; i++)
    {
         tomau(x, y+1+i);
         
         tomau(x+1, y+1+i);
         
         tomau(x+6, y+1+i);
         
         tomau(x+7, y+1+i);
         
    }
}

void V(int x, int y)
{
    for(int i=0; i<4; i++)
    {
         tomau(x,y+i);
         
         tomau(x+1,y+i);
         
         tomau(x+6,y+i);
         
         tomau(x+7,y+i);
         
    }
    for(int i=0; i<6; i++)
    {
         tomau(x+1+i, y+4);     
    }
     tomau(x+2, y+3);
     
     tomau(x+5, y+3);
     
     tomau(x+4, y+5);
     
     tomau(x+3, y+5);
     
}

void R(int x, int y)
{
    for(int i=0; i<6;i++)
    {
         tomau(x,y+i);
         
         tomau(x+1,y+i);
         
    }

    for(int i=0; i<5;i++)
    {
         tomau(x+2+i,y);
         
         tomau(x+2+i,y+2);
         
    }
     tomau(x+7,y+1);
     
     tomau(x+6,y+1);
     
     tomau(x+4,y+3);
     
     tomau(x+5,y+3);
     
     tomau(x+5,y+4);
     
     tomau(x+6,y+4);
     
     tomau(x+6,y+5);
     
     tomau(x+7,y+5);
     


}

boolean dk()
{
    char t;
    int i=1;
    while(1)
    {
        if (kbhit())
            {
                t = getch();
                if (t=='a')
                {
                    i=1;
                    gotoxy(50, 18);
                    colorbg(3);
                    cout<<"YES";
                    gotoxy(67,18);
                    colorbg(0);
                    cout<<"NO";
                }
                else if (t=='d')
                {
                    i=0;
                    gotoxy(50, 18);
                    colorbg(0);
                    cout<<"YES";
                    gotoxy(67,18);
                    colorbg(4);
                    cout<<"NO";
                }
                else if (t==-32)
                {
                    t=getch();
                    if (t==75)
                    {
                        i=1;
                        gotoxy(50, 18);
                        colorbg(3);
                        cout<<"YES";
                        gotoxy(67,18);
                        colorbg(0);
                        cout<<"NO";
                    }
                    else if (t==77 )
                    {
                        i=0;
                        gotoxy(50, 18);
                        colorbg(0);
                        cout<<"YES";
                        gotoxy(67,18);
                        colorbg(4);
                        cout<<"NO";
                    }
                }
                if(t==13)
                {
                    if(i==1) return true;
                    else if (i==0 ) return false;
                }
            }
    }
}