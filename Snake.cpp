#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;

// Kich thuoc khung game
const int GAME_WIDTH  = 50;  // Chieu rong (cot) ben trong
const int GAME_HEIGHT = 20;  // Chieu cao (hang) ben trong

void gotoxy( int column, int line );
void VeKhung();

struct Point{
    int x,y;
};

class CONRAN{
public:
    struct Point A[100];
    int DoDai;
    CONRAN(){
        DoDai = 3;
        A[0].x = 10; A[0].y = 10;
        A[1].x = 11; A[1].y = 10;
        A[2].x = 12; A[2].y = 10;
    }
    void Ve(){
        for (int i = 0; i < DoDai; i++){
            gotoxy(A[i].x,A[i].y);
            cout<<"X";
        }
    }
    void DiChuyen(int Huong){
        for (int i = DoDai-1; i>0;i--)
            A[i] = A[i-1];
        if (Huong==0) A[0].x = A[0].x + 1;
        if (Huong==1) A[0].y = A[0].y + 1;
        if (Huong==2) A[0].x = A[0].x - 1;
        if (Huong==3) A[0].y = A[0].y - 1;

    }
};

int main()
{
    // Bat che do Unicode de hien thi ky tu vien dam
    SetConsoleOutputCP(CP_UTF8);

    CONRAN r;
    int Huong = 0;
    char t;

    while (1){
        if (kbhit()){
            t = getch();
            if (t=='a') Huong = 2;
            if (t=='w') Huong = 3;
            if (t=='d') Huong = 0;
            if (t=='x') Huong = 1;
        }
        system("cls");
        VeKhung();      // Ve khung truoc, sau do ve ran len tren
        r.Ve();
        r.DiChuyen(Huong);
        Sleep(300);
    }

    return 0;
}


// Ham ve khung hinh chu nhat vien dam (double-line box)
void VeKhung()
{
    // -- Goc tren trai
    gotoxy(0, 0); cout << "\xC9";   // ╔
    // -- Goc tren phai
    gotoxy(GAME_WIDTH + 1, 0); cout << "\xBB"; // ╗
    // -- Goc duoi trai
    gotoxy(0, GAME_HEIGHT + 1); cout << "\xC8"; // ╚
    // -- Goc duoi phai
    gotoxy(GAME_WIDTH + 1, GAME_HEIGHT + 1); cout << "\xBC"; // ╝

    // -- Vien ngang tren va duoi
    for (int i = 1; i <= GAME_WIDTH; i++) {
        gotoxy(i, 0);              cout << "\xCD"; // ═
        gotoxy(i, GAME_HEIGHT + 1); cout << "\xCD"; // ═
    }

    // -- Vien doc trai va phai
    for (int i = 1; i <= GAME_HEIGHT; i++) {
        gotoxy(0, i);              cout << "\xBA"; // ║
        gotoxy(GAME_WIDTH + 1, i); cout << "\xBA"; // ║
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
